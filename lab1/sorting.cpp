#include "sorting.h"
#include <algorithm>

// Пузырьковая
void bubbleSort(std::vector<Teacher>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Быстрая
static int partition(std::vector<Teacher>& arr, int left, int right) {
    Teacher pivot = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < pivot) ++i;
        while (arr[j] > pivot) --j;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            ++i; --j;
        }
    }
    return i;
}

void quickSort(std::vector<Teacher>& arr, int left, int right) {
    if (left < right) {
        int idx = partition(arr, left, right);
        quickSort(arr, left, idx - 1);
        quickSort(arr, idx, right);
    }
}

void quickSort(std::vector<Teacher>& arr) {
    if (!arr.empty())
        quickSort(arr, 0, (int)arr.size() - 1);
}

// Слияние
static void merge(std::vector<Teacher>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<Teacher> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(std::vector<Teacher>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(std::vector<Teacher>& arr) {
    if (!arr.empty())
        mergeSort(arr, 0, (int)arr.size() - 1);
}
