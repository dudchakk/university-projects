import random
from timeit import default_timer as timer
import matplotlib.pyplot as plt

# bubble sort

def bubble_sort(input_arr):
    arr = input_arr[:]
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr


# smooth sort

def smoothsort(input_lst):

    lst = input_lst[:]
    leo_nums = leonardo_numbers(len(lst))

    heap = []

    for i in range(len(lst)):
        if len(heap) >= 2 and heap[-2] == heap[-1] + 1:
            heap.pop()
            heap[-1] += 1
        else:
            if len(heap) >= 1 and heap[-1] == 1:
                heap.append(0)
            else:
                heap.append(1)
        restore_heap(lst, i, heap, leo_nums)

    for i in reversed(range(len(lst))):
        if heap[-1] < 2:
            heap.pop()
        else:
            k = heap.pop()
            t_r, k_r, t_l, k_l = get_child_trees(i, k, leo_nums)
            heap.append(k_l)
            restore_heap(lst, t_l, heap, leo_nums)
            heap.append(k_r)
            restore_heap(lst, t_r, heap, leo_nums)


def leonardo_numbers(hi):

    a, b = 1, 1
    numbers = []
    while a <= hi:
        numbers.append(a)
        a, b = b, a + b + 1
    return numbers


def restore_heap(lst, i, heap, leo_nums):
    
    current = len(heap) - 1
    k = heap[current]

    while current > 0:
        j = i - leo_nums[k]
        if (lst[j] > lst[i] and
            (k < 2 or lst[j] > lst[i-1] and lst[j] > lst[i-2])):
            lst[i], lst[j] = lst[j], lst[i]
            i = j
            current -= 1
            k = heap[current]
        else:
            break
    
    while k >= 2:
        t_r, k_r, t_l, k_l = get_child_trees(i, k, leo_nums)
        if lst[i] < lst[t_r] or lst[i] < lst[t_l]:
            if lst[t_r] > lst[t_l]:
                lst[i], lst[t_r] = lst[t_r], lst[i]
                i, k = t_r, k_r
            else:
                lst[i], lst[t_l] = lst[t_l], lst[i]
                i, k = t_l, k_l
        else:
            break


def get_child_trees(i, k, leo_nums):

    t_r, k_r = i - 1, k - 2
    t_l, k_l = t_r - leo_nums[k_r], k - 1
    return t_r, k_r, t_l, k_l


def partly_sort(arr):
    for k in range(int(len(arr) * 0.1)):
        i = random.randint(1, len(arr) - 1)
        j = random.randint(1, len(arr) - 1)
        arr[i], arr[j] = arr[j], arr[i]
    return arr


# testing

# Small array
arr_small = [random.randint(1, 1000) for _ in range(20)]
print("Small array:")

start = timer()
arr_small_b = bubble_sort(arr_small)
end = timer()
bubble_sort_time_small = (end - start) * 1000 # переводимо в мілісекунди
print(f"Bubble sort - {bubble_sort_time_small} ms")

start = timer()
arr_small_s = smoothsort(arr_small)
end = timer()
smooth_sort_time_small = (end - start) * 1000 # переводимо в мілісекунди
print(f"Smooth sort - {smooth_sort_time_small} ms")

# Big array
arr_big = [random.randint(1, 1000) for _ in range(30000)]
print("\nBig array:")

start = timer()
arr_big_b = bubble_sort(arr_big)
end = timer()
bubble_sort_time_big = (end - start) * 1000 # переводимо в мілісекунди
print(f"Bubble sort - {bubble_sort_time_big} ms")

start = timer()
arr_big_s = smoothsort(arr_big)
end = timer()
smooth_sort_time_big = (end - start) * 1000 # переводимо в мілісекунди
print(f"Smooth sort - {smooth_sort_time_big} ms")

# Random data
arr_random = [random.randint(1, 1000) for _ in range(5000)]
print("\nRandom array:")

start = timer()
arr_random_b = bubble_sort(arr_random)
end = timer()
bubble_sort_time_random = (end - start) * 1000 # переводимо в мілісекунди
print(f"Bubble sort - {bubble_sort_time_random} ms")

start = timer()
arr_random_s = smoothsort(arr_random)
end = timer()
smooth_sort_time_random = (end - start) * 1000 # переводимо в мілісекунди
print(f"Smooth sort - {smooth_sort_time_random} ms")

# Sorted array
arr_sorted = [random.randint(1, 1000) for _ in range(5000)]
arr_sorted.sort()
print("\nSorted array:")

start = timer()
arr_sorted_b = bubble_sort(arr_sorted)
end = timer()
bubble_sort_time_sorted = (end - start) * 1000 # переводимо в мілісекунди
print(f"Bubble sort - {bubble_sort_time_sorted} ms")

start = timer()
arr_sorted_s = smoothsort(arr_sorted)
end = timer()
smooth_sort_time_sorted = (end - start) * 1000 # переводимо в мілісекунди
print(f"Smooth sort - {smooth_sort_time_sorted} ms")

# Reverse sorted array
arr_reversed_sorted = [random.randint(1, 1000) for _ in range(5000)]
arr_reversed_sorted.sort(reverse=True)
print("\nReversed sorted array:")

start = timer()
arr_reversed_sorted_b = bubble_sort(arr_reversed_sorted)
end = timer()
bubble_sort_time_reversed_sorted = (end - start) * 1000 # переводимо в мілісекунди
print(f"Bubble sort - {bubble_sort_time_reversed_sorted} ms")

start = timer()
arr_reversed_sorted_s = smoothsort(arr_reversed_sorted)
end = timer()
smooth_sort_time_reversed_sorted = (end - start) * 1000 # переводимо в мілісекунди
print(f"Smooth sort - {smooth_sort_time_reversed_sorted} ms")

# Partly sorted array
arr_partly_sorted = [random.randint(1, 1000) for _ in range(5000)]
arr_partly_sorted.sort()
partly_sort(arr_partly_sorted)
print("\nPartly sorted array:")

start = timer()
arr_partly_sorted_b = bubble_sort(arr_partly_sorted)
end = timer()
bubble_sort_time_partly_sorted = (end - start) * 1000 # переводимо в мілісекунди
print(f"Bubble sort - {bubble_sort_time_partly_sorted} ms")

start = timer()
arr_partly_sorted_s = smoothsort(arr_partly_sorted)
end = timer()
smooth_sort_time_partly_sorted = (end - start) * 1000 # переводимо в мілісекунди
print(f"Smooth sort - {smooth_sort_time_partly_sorted} ms")


# Графік
labels = ['small', 'big', 'random', 'sorted', 'reversed', 'partly']
bubble_sort_times = [bubble_sort_time_small, bubble_sort_time_big, bubble_sort_time_random, bubble_sort_time_sorted, bubble_sort_time_reversed_sorted, bubble_sort_time_partly_sorted]
smooth_sort_times = [smooth_sort_time_small, smooth_sort_time_big, smooth_sort_time_random, smooth_sort_time_sorted, smooth_sort_time_reversed_sorted, smooth_sort_time_partly_sorted]

x = list(range(len(labels)))
width = 0.35

fig, ax = plt.subplots()
rects1 = ax.bar([i - width/2 for i in x], bubble_sort_times, width, label='Bubble')
rects2 = ax.bar([i + width/2 for i in x], smooth_sort_times, width, label='Smooth')

ax.set_ylabel('Час виконання (ms)')
ax.set_title('Час виконання алгоритмів сортування')
ax.set_xticks(x)
ax.set_xticklabels(labels, rotation=45, ha='right')
ax.legend()

def autolabel(rects):
    for rect in rects:
        height = rect.get_height()
        ax.annotate('{}'.format(round(height, 2)),
                    xy=(rect.get_x() + rect.get_width() / 2, height),
                    xytext=(0, 3),  
                    textcoords="offset points",
                    ha='center', va='bottom')

autolabel(rects1)
autolabel(rects2)

plt.yscale('log')  # використовуємо логарифмічний масштаб для великих значень
plt.tight_layout() # автоматично налаштує простір між підписами та колонками
plt.show()
