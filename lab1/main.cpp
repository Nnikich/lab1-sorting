#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <random>
#include <filesystem>
#include <algorithm>
#include "Teacher.h"
#include "sorting.h"

using namespace std;
using namespace chrono;

// ГСП
static random_device rd;
static mt19937 gen(rd());
static const vector<string> faculties = {"ФИиВТ", "ИЭиУ", "ЕМФ", "ГФ", "ЮФ"};
static const vector<string> titles = {"ассистент", "старший преподаватель", "доцент", "профессор"};
static const vector<string> degrees = {"без степени", "кандидат наук", "доктор наук"};
static const vector<string> names = {
    "Иванов И.И.", "Петров П.П.", "Сидоров С.С.", "Кузнецов К.К.", "Смирнова А.А.",
    "Васильева В.В.", "Михайлов М.М.", "Федорова Ф.Ф.", "Морозов М.М.", "Волков В.В."
};

Teacher generateRandomTeacher() {
    uniform_int_distribution<size_t> facDist(0, faculties.size() - 1);
    uniform_int_distribution<size_t> titleDist(0, titles.size() - 1);
    uniform_int_distribution<size_t> degDist(0, degrees.size() - 1);
    uniform_int_distribution<size_t> nameDist(0, names.size() - 1);
    
    return Teacher(
        names[nameDist(gen)],
        faculties[facDist(gen)],
        titles[titleDist(gen)],
        degrees[degDist(gen)]
    );
}

void saveToCSV(const vector<Teacher>& data, const string& filename) {
    ofstream file(filename);
    file << "ФИО,Факультет,Ученое звание,Ученая степень\n";
    for (const auto& t : data) {
        file << t.fullName << ","
             << t.faculty << ","
             << t.academicTitle << ","
             << t.academicDegree << "\n";
    }
}

vector<Teacher> loadFromCSV(const string& filename) {
    vector<Teacher> result;
    ifstream file(filename);
    string line;
    getline(file, line); // пропустить заголовок
    while (getline(file, line)) {
        stringstream ss(line);
        string name, faculty, title, degree;
        getline(ss, name, ',');
        getline(ss, faculty, ',');
        getline(ss, title, ',');
        getline(ss, degree, ',');
        result.emplace_back(name, faculty, title, degree);
    }
    return result;
}

// Генерация файлов разных размеров
void generateTestFiles(const string& dir, const vector<size_t>& sizes) {
    filesystem::create_directories(dir);
    for (size_t n : sizes) {
        vector<Teacher> data;
        data.reserve(n);
        for (size_t i = 0; i < n; ++i)
            data.push_back(generateRandomTeacher());
        string filename = dir + "/data_" + to_string(n) + ".csv";
        saveToCSV(data, filename);
        cout << "Generated " << filename << " with " << n << " records\n";
    }
}

// Измерение времени сортировки
template<typename SortFunc>
double measureTime(vector<Teacher> data, SortFunc sortFunc) {
    auto start = high_resolution_clock::now();
    sortFunc(data);
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}

// Сохранение отсортированных дынных
void saveSortedArrayToFile(const vector<Teacher>& data, const string& filename, const string& algorithmName) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return;
    }
    
    file << "ФИО,Факультет,Ученое звание,Ученая степень\n";
    
    for (const auto& t : data) {
        file << t.fullName << ","
             << t.faculty << ","
             << t.academicTitle << ","
             << t.academicDegree << "\n";
    }
    file.close();
    cout << "Сохранён: " << filename << " (" << algorithmName << ")\n";
}

int main() {
    vector<size_t> sizes = {100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000};
    string dataDir = "data";
    string resultsFile = "results/times.csv";

    // 1.Генерируем или проверяем наличие файлов
    bool needGenerate = false;
    if (!filesystem::exists(dataDir)) {
        needGenerate = true;
    }
    if (needGenerate) {
        generateTestFiles(dataDir, sizes);
    }

    // 2.Открываем файл для записи результатов
    filesystem::create_directories("results");
    ofstream out(resultsFile);
    out << "Size,BubbleSort,QuickSort,MergeSort,StdSort\n";

    // 3.Для каждого размера загружаем данные и измеряем
    for (size_t n : sizes) {
        string filename = dataDir + "/data_" + to_string(n) + ".csv";
        if (!filesystem::exists(filename)) {
            cerr << "File not found: " << filename << endl;
            continue;
        }
        vector<Teacher> original = loadFromCSV(filename);
        cout << "Testing size: " << n << endl;

        // Копируем для каждого
        double tBubble = 0.0, tQuick = 0.0, tMerge = 0.0, tStd = 0.0;
        // Для больших массивов пузырёк может быть слишком долгим – пропускаем при n > 20000?
        if (n <= 20000) {
            tBubble = measureTime(original, [](vector<Teacher>& v) { bubbleSort(v); });
        } else {
            tBubble = -1.0; // не замеряем
        }
        tQuick = measureTime(original, [](vector<Teacher>& v) { quickSort(v); });
        tMerge = measureTime(original, [](vector<Teacher>& v) { mergeSort(v); });
        tStd   = measureTime(original, [](vector<Teacher>& v) { sort(v.begin(), v.end()); });

        out << n << "," << tBubble << "," << tQuick << "," << tMerge << "," << tStd << "\n";
        out.flush();
    }
    out.close();

    cout << "\nЗамеры завершены. Результаты в " << resultsFile << endl;
    
    // Загружаем массив для сохранения (размер 1000)
    string sortedDataFile = dataDir + "/data_1000.csv";
    if (filesystem::exists(sortedDataFile)) {
        vector<Teacher> dataForSaving = loadFromCSV(sortedDataFile);
        
        // Пузырьковая сортировка
        vector<Teacher> bubbleSorted = dataForSaving;
        bubbleSort(bubbleSorted);
        saveSortedArrayToFile(bubbleSorted, "results/sorted_bubble_1000.csv", "Пузырьковая сортировка");
        
        // Быстрая сортировка
        vector<Teacher> quickSorted = dataForSaving;
        quickSort(quickSorted);
        saveSortedArrayToFile(quickSorted, "results/sorted_quick_1000.csv", "Быстрая сортировка");
        
        // Сортировка слиянием
        vector<Teacher> mergeSorted = dataForSaving;
        mergeSort(mergeSorted);
        saveSortedArrayToFile(mergeSorted, "results/sorted_merge_1000.csv", "Сортировка слиянием");
        
        // std::sort
        vector<Teacher> stdSorted = dataForSaving;
        sort(stdSorted.begin(), stdSorted.end());
        saveSortedArrayToFile(stdSorted, "results/sorted_std_1000.csv", "std::sort");
        
        cout << "Отсортированные массивы (1000 элементов) сохранены в папку results/\n";
    } else {
        cout << "Файл data/data_1000.csv не найден, пропускаем сохранение\n";
    }
    
    // Дополнительно сохраняем для размера 500000
    string sortedDataFile2 = dataDir + "/data_500000.csv";
    if (filesystem::exists(sortedDataFile2)) {
        vector<Teacher> dataForSaving2 = loadFromCSV(sortedDataFile2);
        vector<Teacher> quickSorted2 = dataForSaving2;
        quickSort(quickSorted2);
        saveSortedArrayToFile(quickSorted2, "results/sorted_quick_500000.csv", "Быстрая сортировка (500000 элементов)");
    }
    
    cout << "\nВсе результаты сохранены:\n";
    cout << "Время сортировки: results/times.csv\n";
    cout << "Отсортированные данные: results/sorted_*.csv\n";
    
    return 0;
}
