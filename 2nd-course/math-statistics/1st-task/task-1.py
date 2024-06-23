import random
import math
import matplotlib.pyplot as plt
import numpy as np


a = []
max_possible_random = int(input("Enter maximum possible number: "))
min_possible_random = int(input("Enter minimum possible number: "))
random_number_length = int(input("Enter length: "))

for i in range(random_number_length):
    a.append(random.randint(min_possible_random, max_possible_random))


# Дискретний розподіл:

# Варіаційний ряд:

print("Дискретний розподіл:")
print("Варіаційний ряд:")
a.sort()
print(a)

# Частотна таблиця:

def convert_to_set(lst):
    to_return = []
    for i in lst:
        if i not in to_return:
            to_return.append(i)
    return to_return

def number_of_times_occurs(element, lst):
    counter = 0
    for i in lst:
        if element == i:
            counter += 1
    return counter

def print_frequency_table(distinct_values_list, counts):
    print("\nЧастотна таблиця:")
    print("  xi   |   ni   ")
    for i in range(len(distinct_values_list)):
        print(f"{str(distinct_values_list[i]):^6} | {str(counts[i]):^6}")

a_sorted = convert_to_set(a)
a_sorted.sort()
distinct_values = a_sorted
counts = []
for i in distinct_values:
    counts.append(number_of_times_occurs(i, a))

print()
print_frequency_table(distinct_values, counts)


# Діаграма частот:

value = convert_to_set(a)

fig = plt.figure()
ax = fig.add_axes([0,0,1,1])
ax.bar(value, counts)

ax.axhline(y=0, color='red', linewidth=1)
ax.axvline(x=0, color='red', linewidth=1)

ax.set_title('Діаграма частот')
ax.set_ylabel('Частота значень')
ax.set_xlabel('Значення')

plt.show()

# Полігон частот:

plt.plot(distinct_values, counts, marker='o', color='g')
plt.show()

print("\nДіаграма, полігон частот та емпірична ф-я розподілу зображені в інших вікнах.")


# Емпірична ф-ція розподілу Fn(x):

def find_probabilities(a, counts):
    probabilities = []
    start = 0
    for i in counts:
        probabilities.append(start)
        start += i/len(a)
    probabilities.append(start)
    
    return probabilities

def show_plot(distinct_v, probs):
    p1, p2 = [distinct_v[0], distinct_v[0]], [probs[0], probs[0]]
    plt.plot(p1, p2)

    for i in range(1, len(distinct_v)):
        p3, p4 = [distinct_v[i-1], distinct_v[i]], [probs[i], probs[i]]
        plt.plot(p3, p4)

    p5, p6 = [distinct_v[-1]+5, distinct_v[-1]], [probs[-1], probs[-1]]
    plt.plot(p5, p6)

    for i in range(1, len(distinct_v)+1):
        p7, p8 = [distinct_v[i-1], distinct_v[i-1]], [probs[i], 0]
        plt.plot(p7, p8, linestyle = 'dashed')

    p9, p10 = [0, distinct_v[-1]+5], [0, 0]
    plt.plot(p9, p10)

    plt.show()

probabilities = find_probabilities(a, counts)
show_plot(distinct_values, probabilities)


# Числові характеристики:

#медіана
def find_median(a):
    a_len = len(a)
    return (a[a_len//2-1] + a[a_len//2]) / 2 if a_len % 2 == 0 else a[a_len//2]

#мода
def find_moda(counts, distinct_v):
    to_return = []
    for i in range(len(counts)):
        if counts[i] == np.max(counts):
            to_return.append(distinct_v[i])
    return to_return

#вибіркове середнє
def average_(distinct_v, counts):
    to_return = 0
    for i in range(len(distinct_v)):
        to_return += (distinct_v[i] * counts[i])
    return to_return/sum_(counts)

#розмах
def scope(distinct_v):
    return np.max(distinct_v) - np.min(distinct_v)

# об'єм
def sum_(lst):
    to_return = 0
    for i in lst:
        to_return += i
    return to_return

#девіація
def deviation(distinct_v, counts):
    to_return = 0
    avg = average_(distinct_v, counts)
    for i in range(len(distinct_v)):
        to_return += (((distinct_v[i] - avg) ** 2) * counts[i])
    return to_return

#варіанса
def variance(distinct_v, counts):
    return deviation(distinct_v, counts)/(sum_(counts)-1)

#стандарт
def standart(distinct_v, counts):
    return math.sqrt(variance(distinct_v, counts))

#варіація
def variation(distinct_v, counts):
    return standart(distinct_v, counts) / average_(distinct_v, counts)

#вибіркова дисперсія
def selective_dispersion(distinct_v, counts):
    return deviation(distinct_v, counts)/sum_(counts)

#вибіркове середнє квадратичне відхилення
def selective_average_quadratic_deviation(distinct_v, counts):
    return math.sqrt(selective_dispersion(distinct_v, counts))

#центральний момент k-того порядку
def m_k(k, distinct_v, counts):
    to_return = 0
    _avg = average_(distinct_v, counts)
    for i in range(len(distinct_v)):
        to_return += ((distinct_v[i] - _avg) ** k) * counts[i]
    return to_return/sum_(counts)

# асиметрія
def asymetry(distinct_v, counts):
    return m_k(3, distinct_v, counts) / (m_k(2, distinct_v, counts) ** (3/2))

# ексцес
def excess(distinct_v, counts):
    return m_k(4, distinct_v, counts) / (m_k(2, distinct_v, counts) ** (2)) - 3

# квантилі
def get_quantiles(a):
    data = {(4, "Квартил"): [], (8, "Октил"): [], (10, "Децил"): [],
            (100, "Центил"): [], (1000, "Міліл"): []}

    for k in data.keys():
        if len(a) % k[0] == 0:
            data[k] = [a[int(len(a) / k[0] * (i + 1))] for i in range(k[0] - 1)]

    for k, v in data.items():
        if v:
            print(f"{k[1]}і: {v}")
            print(f"Інтер{k[1].lower()}ьна широта: {v[len(v) - 1] - v[0]}\n")

print("\nЧислові характеристики:")
print("Медіана: " + str(find_median(a)))
print("Мода: " + str(find_moda(counts, distinct_values)))
print("Вибіркове середнє значення: " + str(average_(distinct_values, counts)))
print("Розмах: " + str(scope(distinct_values)))
print("Девіація: " + str(deviation(distinct_values, counts)))
print("Варіанса: " + str(variance(distinct_values, counts)))
print("Стандарт: " + str(standart(distinct_values, counts)))
print("Варіація: " + str(variation(distinct_values, counts)))
print("Вибіркова дисперсія: " + str(selective_dispersion(distinct_values, counts)))
print("Вибіркове середнє квадратичне відхилення: " + str(selective_average_quadratic_deviation(distinct_values, counts)))
print("Центральний момент другого порядку: " + str(m_k(2, distinct_values, counts)))
print("Центральний момент третього порядку: " + str(m_k(3, distinct_values, counts)))
print("Центральний момент четвертого порядку: " + str(m_k(4, distinct_values, counts)))
print("Асиметрія: " + str(asymetry(distinct_values, counts)))
print("Ексцес: " + str(excess(distinct_values, counts)))
print()
get_quantiles(a)


#-------------------------------------------------------------------------------------------------------------------------------

# Неперервний розподіл:

def find_intervals(lst):
    sorted_lst = convert_to_set(lst)
    sorted_lst.sort()
    
    r = math.floor(math.log2(len(sorted_lst)))
    interval_length = (np.max(lst) - np.min(lst))/r

    intervals = []
    min_value = np.min(lst)

    while round(min_value) < np.max(lst):
        intervals.append((min_value, min_value+interval_length))
        min_value += interval_length
    
    return intervals

def is_in_tuple(element, tpl):
    if element >= tpl[0] and element < tpl[1]:
        return True
    return False

def is_in_final_tuple(element, tpl):
    if element >= tpl[0] and element <= tpl[1]:
        return True
    return False

def find_counts_of_elements(lst):
    intervals = find_intervals(a)
    counts_of_elements_in_interval = []

    for i in intervals:
        counter = 0
        for j in range(len(lst)):
            if j != len(lst)-1:
                if is_in_tuple(lst[j], i):
                    counter += 1
            else:
                if is_in_final_tuple(lst[j], i):
                    counter += 1
                    
        counts_of_elements_in_interval.append(counter)
    return counts_of_elements_in_interval

print("\nНеперервний розподіл:")
print_frequency_table(find_intervals(a), find_counts_of_elements(a))


# Гістограма:

def find_probabilities_interval(a):
    probabilities = []
    
    c = find_counts_of_elements(a)
    start = 0
    
    for i in c:
        probabilities.append(start)
        start += i/sum_(c)
    probabilities.append(start)
    
    return probabilities

def find_wi(a):
    c = find_counts_of_elements(a)
    
    to_return = []
    for i in c:
        to_return.append(i/sum_(c))
    return to_return

def show_histogram_intervals(a):
    intervals = find_intervals(a)
    c = find_counts_of_elements(a)
    probs = find_probabilities_interval(a)
    
    p1, p2 = [intervals[0][0], intervals[0][0]], [probs[0], probs[0]]
    plt.plot(p1, p2)
    
    for i in range(len(intervals)):
        p3, p4 = [intervals[i][0], intervals[i][0]], [0, c[i]]
        p5, p6 = [intervals[i][1], intervals[i][1]], [c[i], c[i]]
        
        p7, p8 = [intervals[i][0], intervals[i][1]], [c[i], c[i]]
        
        p9, p10 = [intervals[i][1], intervals[i][1]], [0, c[i]]
        p11, p12 = [intervals[i][1], intervals[i][1]], [c[i], c[i]]

        #left line
        plt.plot(p3, p4)
        
        #right line
        plt.plot(p5, p6)
        
        #upper line
        plt.plot(p7, p8)
        
        plt.plot(p9, p10)
        plt.plot(p11, p12)
    
    pf1, pf2 = [intervals[0][0], intervals[-1][1]], [0, 0]
    plt.plot(pf1, pf2)
    plt.show()

show_histogram_intervals(a)


# Емпірична ф-ція розподілу:

def empirical_function_intervals(a):
    wi = find_wi(a)
    probs = find_probabilities_interval(a)
    intervals = find_intervals(a)
    
    y_prev = 0.0
    j_prev = 0.0
    for i in range(len(intervals)):
        j = intervals[i][0]
        while round(j, 2) <= round(intervals[i][1], 2):
            y = wi[i]/(intervals[i][1]-intervals[i][0])*(j-intervals[i][0])+probs[i]
            x1, y1 = [[j_prev, j], [y_prev, y]]
            plt.plot(x1, y1)
            y_prev, j_prev = y, j
            j += 0.01
    
    plt.show()

empirical_function_intervals(a)
print("\nГістограма розподілу та емпірична ф-я зображені в інших вікнах.")


# Числові характеристики:

def find_right_interval(lst):
    counter = 0
    interval_index = 0
    counts_of_elements_in_interval = find_counts_of_elements(lst)
    
    index_of_middle_element = len(lst)//2 if len(lst) % 2 == 1 else len(lst)/2-1
    
    for i in counts_of_elements_in_interval:
        if counter < index_of_middle_element:
            counter += i
            interval_index += 1
        
    return interval_index

def sum_el(arr, n):
    result = 0
    for i in range(n):
        result += arr[i]
    return result

def find_mediana_intervals(lst):
    intervals = find_intervals(lst)
    counts_of_elements_in_interval = find_counts_of_elements(lst)

    index = find_right_interval(lst)
    (x, y) = intervals[index]
    n_m = counts_of_elements_in_interval[index]
    return x + (y-x)/n_m * (len(lst)/2 - sum_el(counts_of_elements_in_interval, index))

def index_of_max(lst):
    to_return = 0
    index = 0
    max_v = 0
    for i in lst:
        if i > max_v:
            max_v = i
            to_return = index
        index += 1
    return to_return

def return_indexes_of_max(lst):
    max_value = lst[index_of_max(lst)]
    to_return = []
    for i in range(len(lst)):
        if max_value == lst[i]:
            to_return.append(i)
    return to_return

def most_modnyi(lst):
    intervals = find_intervals(lst)
    c = find_counts_of_elements(lst)
    indexes_of_most_modnyi = return_indexes_of_max(c)
    return indexes_of_most_modnyi

def find_moda_intervals(data):
    intervals = find_intervals(data)
    counts = find_counts_of_elements(data)

    max_indexes = return_indexes_of_max(counts)
    modas = []
    for i in max_indexes:
        (x, y) = intervals[i]
        if i == 0:
            modas.append(x + ((counts[i] - 0) / ((counts[i] - 0) + (counts[i] - counts[i + 1])) * (y - x)))
        elif i == len(intervals) - 1:
            modas.append(x + ((counts[i] - counts[i - 1]) / ((counts[i] - counts[i - 1]) + (counts[i] - 0)) * (y - x)))
        else:
            modas.append(x + ((counts[i] - counts[i - 1]) / ((counts[i] - counts[i - 1]) + (counts[i] - counts[i + 1])) * (y - x)))

    return modas

def get_midpoint(tpl):
    return (tpl[0]+tpl[1])/2

#вибіркове середнє
def average_intervals(lst):
    to_return = 0
    intervals = find_intervals(lst)
    c = find_counts_of_elements(lst)
    for i in range(len(intervals)):
        to_return += (get_midpoint(intervals[i]) * c[i])
    return to_return/sum_(c)

#девіація
def deviation_intervals(lst):
    to_return = 0
    intervals = find_intervals(lst)
    c = find_counts_of_elements(lst)
    avg = average_intervals(lst)
    
    for i in range(len(intervals)):
        to_return += (((get_midpoint(intervals[i]) - avg) ** 2) * c[i])
    
    return to_return

#варіанса
def variance_intervals(lst):
    c = find_counts_of_elements(lst)
    return deviation_intervals(a)/(sum_(c)-1)

#стандарт
def standart_intervals(lst):
    return math.sqrt(variance_intervals(lst))

#варіація
def variation_intervals(lst):
    return standart_intervals(lst) / average_intervals(lst)
def selective_dispersion_intervals(lst):
    c = find_counts_of_elements(lst)
    return deviation_intervals(lst)/sum_(c)

#центральний момент k-того порядку
def m_k_intervals(k, lst):
    to_return = 0
    
    intervals = find_intervals(lst)
    c = find_counts_of_elements(lst)
    avg = average_intervals(lst)
    
    for i in range(len(intervals)):
        to_return += ((get_midpoint(intervals[i]) - avg) ** k) * c[i]
    return to_return/sum_(c)

#вибіркова дисперсія
def selective_dispersion_intervals(lst):
    c = find_counts_of_elements(lst)
    return deviation_intervals(lst)/sum_(lst)

#вибіркове середнє квадратичне відхилення
def selective_average_quadratic_deviation_intervals(a):
    return math.sqrt(selective_dispersion_intervals(a))

#асиметрія
def asymetry_intervals(a):
    return m_k_intervals(3, a) / (m_k_intervals(2, a) ** (3/2))

#ексцес
def excess_intervals(a):
    return m_k_intervals(4, a) / (m_k_intervals(2, a) ** (2)) - 3

print("\nЧислові характеристики:")
print("Медіана: " + str(find_mediana_intervals(a)))
print("Мода: " + str(find_moda_intervals(a)))
print("Вибіркове середнє значення: " + str(average_intervals(a)))
print("Девіація: " + str(deviation_intervals(a)))
print("Варіанса: " + str(variance_intervals(a)))
print("Стандарт: " + str(standart_intervals(a)))
print("Варіація: " + str(variation_intervals(a)))
print("Вибіркова дисперсія: " + str(selective_dispersion_intervals(a)))
print("Вибіркове середнє квадратичне відхилення: " + str(selective_average_quadratic_deviation_intervals(a)))
print("Центральний момент другого порядку: " + str(m_k_intervals(2, a)))
print("Центральний момент третього порядку: " + str(m_k_intervals(3, a)))
print("Центральний момент четвертого порядку: " + str(m_k_intervals(4, a)))
print("Асиметрія: " + str(asymetry_intervals(a)))
print("Ексцес: " + str(excess_intervals(a)))