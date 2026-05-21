/**
 * @file sorting.h
 * @brief Реализации алгоритмов сортировки
 */

#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include "Teacher.h"

/**
 * @brief Пузырьковая сортировка
 * @param arr Ссылка на сортируемый массив
 * @complexity O(n²)
 */
void bubbleSort(std::vector<Teacher>& arr);

/**
 * @brief Быстрая сортировка (рекурсивная версия)
 * @param arr Ссылка на сортируемый массив
 * @param left Левый индекс диапазона
 * @param right Правый индекс диапазона
 */
void quickSort(std::vector<Teacher>& arr, int left, int right);
void quickSort(std::vector<Teacher>& arr);

/**
 * @brief Быстрая сортировка (удобная обёртка)
 * @param arr Ссылка на сортируемый массив
 */
void mergeSort(std::vector<Teacher>& arr, int left, int right);
void mergeSort(std::vector<Teacher>& arr);

#endif // SORTING_H
