import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

plt.rcParams['font.family'] = 'Arial'
plt.rcParams['axes.unicode_minus'] = False

possible_paths = [
    'results/times.csv',
    '../results/times.csv',
    '/Users/nnikich/Desktop/lab1/results/times.csv',
    '/Users/nnikich/Desktop/lab1/lab1/results/times.csv',
]

csv_path = None
for path in possible_paths:
    if os.path.exists(path):
        csv_path = path
        print(f"Найден файл: {path}")
        break

if csv_path is None:
    print("Ошибка: файл times.csv не найден!")
    print("Проверьте, что программа C++ была запущена и создала файл.")
    exit(1)

df = pd.read_csv(csv_path)
print("\nДанные загружены:")
print(df.to_string())
print()

# Создаём папку для графиков
os.makedirs('results', exist_ok=True)

#Пузырьковая сортировка (Bubble Sort)
plt.figure(figsize=(10, 6))
bubble_data = df[df['BubbleSort'] > 0]
plt.plot(bubble_data['Size'], bubble_data['BubbleSort'], 'o-', color='red', linewidth=2, markersize=8, label='Bubble Sort')

if len(bubble_data) > 0:
    n = bubble_data['Size'].values
    ref_time = bubble_data['BubbleSort'].iloc[0] / (n[0]**2)
    o_n2 = ref_time * n**2
    plt.plot(n, o_n2, 'r--', linewidth=1.5, alpha=0.7, label='Теоретическая O(n²)')

plt.xscale('log')
plt.yscale('log')
plt.xlabel('Размер массива (n)', fontsize=12)
plt.ylabel('Время сортировки (секунды)', fontsize=12)
plt.title('Пузырьковая сортировка (Bubble Sort)\nСложность O(n²)', fontsize=14)
plt.legend(fontsize=11)
plt.grid(True, alpha=0.3, linestyle='--')
plt.tight_layout()
plt.savefig('results/graph_1_bubble.png', dpi=150, bbox_inches='tight')
plt.show()
print("График 1 сохранён: results/graph_1_bubble.png")

# Быстрая сортировка (Quick Sort)
plt.figure(figsize=(10, 6))
plt.plot(df['Size'], df['QuickSort'], 's-', color='blue', linewidth=2, markersize=8, label='Quick Sort')

n = df['Size'].values
ref_time = df['QuickSort'].iloc[0] / (n[0] * np.log2(n[0]))
o_nlogn = ref_time * n * np.log2(n)
plt.plot(n, o_nlogn, 'b--', linewidth=1.5, alpha=0.7, label='Теоретическая O(n log n)')

plt.xscale('log')
plt.yscale('log')
plt.xlabel('Размер массива (n)', fontsize=12)
plt.ylabel('Время сортировки (секунды)', fontsize=12)
plt.title('Быстрая сортировка (Quick Sort)\nСложность O(n log n) в среднем', fontsize=14)
plt.legend(fontsize=11)
plt.grid(True, alpha=0.3, linestyle='--')
plt.tight_layout()
plt.savefig('results/graph_2_quick.png', dpi=150, bbox_inches='tight')
plt.show()
print("График 2 сохранён: results/graph_2_quick.png")

# Сортировка слиянием (Merge Sort)
plt.figure(figsize=(10, 6))
plt.plot(df['Size'], df['MergeSort'], '^-', color='green', linewidth=2, markersize=8, label='Merge Sort')

ref_time_merge = df['MergeSort'].iloc[0] / (n[0] * np.log2(n[0]))
o_nlogn_merge = ref_time_merge * n * np.log2(n)
plt.plot(n, o_nlogn_merge, 'g--', linewidth=1.5, alpha=0.7, label='Теоретическая O(n log n)')

plt.xscale('log')
plt.yscale('log')
plt.xlabel('Размер массива (n)', fontsize=12)
plt.ylabel('Время сортировки (секунды)', fontsize=12)
plt.title('Сортировка слиянием (Merge Sort)\nСложность O(n log n) всегда', fontsize=14)
plt.legend(fontsize=11)
plt.grid(True, alpha=0.3, linestyle='--')
plt.tight_layout()
plt.savefig('results/graph_3_merge.png', dpi=150, bbox_inches='tight')
plt.show()
print("График 3 сохранён: results/graph_3_merge.png")

# std::sort (Introsort)
plt.figure(figsize=(10, 6))
plt.plot(df['Size'], df['StdSort'], 'd-', color='purple', linewidth=2, markersize=8, label='std::sort (Introsort)')

ref_time_std = df['StdSort'].iloc[0] / (n[0] * np.log2(n[0]))
o_nlogn_std = ref_time_std * n * np.log2(n)
plt.plot(n, o_nlogn_std, 'purple', '--', linewidth=1.5, alpha=0.7, label='Теоретическая O(n log n)')

plt.xscale('log')
plt.yscale('log')
plt.xlabel('Размер массива (n)', fontsize=12)
plt.ylabel('Время сортировки (секунды)', fontsize=12)
plt.title('std::sort (Introsort)\nГибридный алгоритм (быстрая + пирамидальная + вставками)', fontsize=14)
plt.legend(fontsize=11)
plt.grid(True, alpha=0.3, linestyle='--')
plt.tight_layout()
plt.savefig('results/graph_4_stdsort.png', dpi=150, bbox_inches='tight')
plt.show()
print("График 4 сохранён: results/graph_4_stdsort.png")

# Сравнительный график
plt.figure(figsize=(12, 8))

plt.plot(df['Size'], df['QuickSort'], 's-', color='blue', linewidth=2, markersize=8, label='Quick Sort')
plt.plot(df['Size'], df['MergeSort'], '^-', color='green', linewidth=2, markersize=8, label='Merge Sort')
plt.plot(df['Size'], df['StdSort'], 'd-', color='purple', linewidth=2, markersize=8, label='std::sort')

# Пузырьковая (только где есть данные)
bubble = df[df['BubbleSort'] > 0]
if len(bubble) > 0:
    plt.plot(bubble['Size'], bubble['BubbleSort'], 'o-', color='red', linewidth=2, markersize=8, label='Bubble Sort')

plt.xscale('log')
plt.yscale('log')
plt.xlabel('Размер массива (n)', fontsize=12)
plt.ylabel('Время сортировки (секунды)', fontsize=12)
plt.title('Сравнение всех алгоритмов сортировки\nСтруктура "Преподаватели" (Вариант 5)', fontsize=14)
plt.legend(fontsize=11)
plt.grid(True, alpha=0.3, linestyle='--')
plt.tight_layout()
plt.savefig('results/graph_all_comparison.png', dpi=150, bbox_inches='tight')
plt.show()
print("Сравнительный график сохранён: results/graph_all_comparison.png")
