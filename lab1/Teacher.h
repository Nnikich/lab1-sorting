/**
 * @file Teacher.h
 * @brief Определение структуры данных "Преподаватель"
 * @version 1.0
 * @date 2026-05-14
 *
 * @details Данный файл содержит определение структуры Teacher,
 *          которая представляет преподавателя с четырьмя полями:
 *          ФИО, факультет, учёное звание и учёная степень.
 *          Также определены операторы сравнения для сортировки
 *          по правилам из варианта 5 лабораторной работы.
 */

#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <tuple>

/**
 * @struct Teacher
 * @brief Структура, представляющая преподавателя
 *
 * @details Содержит полную информацию о преподавателе:
 * - ФИО (fullName)
 * - Факультет (faculty)
 * - Учёное звание (academicTitle)
 * - Учёная степень (academicDegree)
 *
 * Сравнение преподавателей выполняется по полям в следующем порядке:
 * 1. Факультет (faculty) — первичный ключ
 * 2. ФИО (fullName) — вторичный ключ
 * 3. Учёная степень (academicDegree) — третичный ключ
 * 4. Учёное звание (academicTitle) — четвертичный ключ
 */
struct Teacher {
    /**
     * @brief ФИО преподавателя
     *
     * Формат: "Фамилия И.О." (например, "Иванов И.И.")
     */
    std::string fullName;
    
    /**
     * @brief Факультет, на котором работает преподаватель
     *
     * Примеры: "ФИиВТ", "ИЭиУ", "ЕМФ", "ГФ", "ЮФ"
     */
    std::string faculty;
    
    /**
     * @brief Учёное звание преподавателя
     *
     * Примеры: "ассистент", "старший преподаватель", "доцент", "профессор"
     */
    std::string academicTitle;
    
    /**
     * @brief Учёная степень преподавателя
     *
     * Примеры: "без степени", "кандидат наук", "доктор наук"
     */
    std::string academicDegree;
    
    
    /**
     * @brief Конструктор по умолчанию
     *
     * Создаёт пустой объект Teacher (все поля пустые строки)
     */
    Teacher() = default;
    
    /**
     * @brief Конструктор с параметрами
     *
     * @param name ФИО преподавателя
     * @param fac Факультет
     * @param title Учёное звание
     * @param degree Учёная степень
     *
     * @example Teacher("Иванов И.И.", "ФИиВТ", "доцент", "кандидат");
     */
    Teacher(const std::string& name, const std::string& fac,
            const std::string& title, const std::string& degree)
        : fullName(name), faculty(fac), academicTitle(title), academicDegree(degree) {}
    // Порядок сравнения: faculty -> fullName -> academicDegree -> academicTitle
    
    /**
     * @brief Оператор "меньше" (<)
     *
     * @details Сравнивает двух преподавателей лексикографически
     *          в порядке: факультет → ФИО → учёная степень → учёное звание
     *
     * @param other Другой преподаватель для сравнения
     * @return true если текущий преподаватель меньше другого
     * @return false если текущий преподаватель не меньше другого
     */
    bool operator<(const Teacher& other) const {
        return std::tie(faculty, fullName, academicDegree, academicTitle) <
               std::tie(other.faculty, other.fullName, other.academicDegree, other.academicTitle);
    }
    
    /**
     * @brief Оператор "больше" (>)
     *
     * @param other Другой преподаватель для сравнения
     * @return true если текущий преподаватель больше другого
     * @return false если текущий преподаватель не больше другого
     */
    bool operator>(const Teacher& other) const { return other < *this; }
    
    /**
     * @brief Оператор "меньше или равно" (<=)
     *
     * @param other Другой преподаватель для сравнения
     * @return true если текущий преподаватель меньше или равен другому
     * @return false если текущий преподаватель больше другого
     */
    bool operator<=(const Teacher& other) const { return !(*this > other); }
    
    /**
     * @brief Оператор "больше или равно" (>=)
     *
     * @param other Другой преподаватель для сравнения
     * @return true если текущий преподаватель больше или равен другому
     * @return false если текущий преподаватель меньше другого
     */
    bool operator>=(const Teacher& other) const { return !(*this < other); }
    
    /**
     * @brief Оператор "равно" (==)
     *
     * @param other Другой преподаватель для сравнения
     * @return true если все поля преподавателей совпадают
     * @return false если хотя бы одно поле отличается
     */
    bool operator==(const Teacher& other) const {
        return std::tie(faculty, fullName, academicDegree, academicTitle) ==
               std::tie(other.faculty, other.fullName, other.academicDegree, other.academicTitle);
    }
    
    /**
     * @brief Оператор "не равно" (!=)
     *
     * @param other Другой преподаватель для сравнения
     * @return true если поля преподавателей отличаются
     * @return false если все поля совпадают
     */
    bool operator!=(const Teacher& other) const { return !(*this == other); }
};

#endif // TEACHER_H
