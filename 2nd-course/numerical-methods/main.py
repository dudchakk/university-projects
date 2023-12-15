import tkinter as tk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import sympy as sp
import numpy as np

entries = []
const_entries = []
secant_method_points = []
size_entry = None
result_label = None
result_label_least_squares = None
size_entry_least_squares = None
size_entry_least_squares_for_system = []
entries_least_squares = []
frame_newton_method = None
entries_newton_method = []
fx_entry_newton_method = None
entrie_function_newton_method = ""
fun_graph_newton_method = ""
result_newton_method = None
entrie_function_secant_method = ""
fun_graph_secant_method = ""
result_secant_method = None
a_secant_method = None
b_secant_method = None
entries_least_squares_for_system = []
const_entries_least_squares_for_system = []
size_entry_iteration_method = []
entries_iteration_method = []
const_entries_iteration_method = []
size_entry_lagrange = None
entries_lagrange_polinomial = []
frame_labrange_polinomial = None
size_entry_newton_interpolation = None
entries_newton_interpolation = []
frame_newton_interpolation = None


# метод Гауса, СЛАР:

def gaussian_elimination(A, b):
    n = len(A)
    for i in range(n):
        max_row = i
        for k in range(i + 1, n):
            if abs(A[k][i]) > abs(A[max_row][i]):
                max_row = k
        A[i], A[max_row] = A[max_row], A[i]
        b[i], b[max_row] = b[max_row], b[i]

        pivot = A[i][i]
        for k in range(i, n):
            A[i][k] /= pivot
        b[i] /= pivot

        for k in range(n):
            if k != i:
                factor = A[k][i]
                for j in range(i, n):
                    A[k][j] -= factor * A[i][j]
                b[k] -= factor * b[i]

        for i in range(n):
            for j in range(n):
                A[i][j] = round(A[i][j], 3)
            b[i] = round(b[i], 3)

    return b

def solve_gauss():
    size = int(size_entry.get())
    matrix = [[float(entries[i][j].get() if entries[i][j].get() else 0) for j in range(size)] for i in range(size)]
    constants = [float(const_entries[i].get() if const_entries[i].get() else 0) for i in range(size)]

    result = gaussian_elimination(matrix, constants)

    result_label.config(text=f"Result: {result}")

def create_entries():
    global entries
    global const_entries

    size = int(size_entry.get())

    for widget in frame.winfo_children():
        widget.destroy()

    entries = [[tk.Entry(frame, width=5) for _ in range(size)] for _ in range(size)]
    for i in range(size):
        for j in range(size):
            entries[i][j].grid(row=i, column=j)

    const_entries = [tk.Entry(frame, width=5) for _ in range(size)]
    for i in range(size):
        const_entries[i].grid(row=i, column=size)

def gauss_gui():
    global size_entry
    global result_label
    global frame

    # Create the GUI
    root = tk.Tk()
    root.title("Метод Гауса для СЛАР")

    root.geometry("700x500")

    custom_font = ("Arial", 11)
    root.option_add("*Font", custom_font)

    root.configure(bg='white')

    size_label = tk.Label(root, text="Введіть розмір матриці:", bg='white')
    size_label.grid(row=0, column=0, padx=5, pady=5)

    size_entry = tk.Entry(root, width=5)
    size_entry.grid(row=0, column=1, padx=5, pady=5)

    size_button = tk.Button(root, text="Створити поле для введення", command=create_entries, bd=1, highlightthickness=0)
    size_button.grid(row=0, column=2, padx=5, pady=5)

    frame = tk.Frame(root)
    frame.grid(row=1, column=0, columnspan=3, pady=10)

    solve_button = tk.Button(root, text="Розв'язати систему", command=solve_gauss, bd=1, highlightthickness=0)
    solve_button.grid(row=2, column=0, columnspan=3, pady=10)

    result_label = tk.Label(root, text="Результат: ", bg='white')
    result_label.grid(row=3, column=0, columnspan=3, pady=5)

    root.mainloop()


# -------------------------------------------------------------------------------------------------------------------------------------------------------

# метод найменших квадратів, СЛАР:

def invertible_matrix(A):
    n = len(A)
    E = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        E[i][i] = 1

    for i in range(n):
        max_row = i
        for k in range(i + 1, n):
            if abs(A[k][i]) > abs(A[max_row][i]):
                max_row = k
        A[i], A[max_row] = A[max_row], A[i]
        E[i], E[max_row] = E[max_row], E[i]

        pivot = A[i][i]
        for k in range(i, n):
            A[i][k] /= pivot
        for k in range(n):
            E[i][k] /= pivot

        for k in range(n):
            if k != i:
                factor = A[k][i]
                for j in range(i, n):
                    A[k][j] -= factor * A[i][j]
                for j in range(n):
                    E[k][j] -= factor * E[i][j]

    return E

def solve_least_squares_for_system():
    global entries_least_squares_for_system
    global result_label_least_squares
    global const_entries_least_squares_for_system

    size = int(size_entry_least_squares_for_system[0].get())
    size2 = int(size_entry_least_squares_for_system[1].get())
    matrix = [[float(entries_least_squares_for_system[i][j].get() if entries_least_squares_for_system[i][j].get() else 0) for j in range(size-1)] for i in range(size2)]
    constants = [float(const_entries_least_squares_for_system[i].get() if const_entries_least_squares_for_system[i].get() else 0) for i in range(size2)]

    matrix_transpose = [[matrix[j][i] for j in range(size2)] for i in range(size-1)]

    matrix_transpose_by_matrix = [[0 for _ in range(size-1)] for _ in range(size-1)]
    for i in range(size-1):
        for j in range(size-1):
            for k in range(size2):
                matrix_transpose_by_matrix[i][j] += matrix_transpose[i][k]*matrix[k][j]

    matrix_transpose_by_matrix_invertible = invertible_matrix(matrix_transpose_by_matrix)

    matrix_transpose_by_constants = [0 for _ in range(size-1)]
    for i in range(size-1):
        for j in range(size2):
            matrix_transpose_by_constants[i] += matrix_transpose[i][j]*constants[j]

    result = [0 for _ in range(size-1)]
    for i in range(size-1):
        for j in range(size-1):
            result[i] += matrix_transpose_by_matrix_invertible[i][j]*matrix_transpose_by_constants[j]

    result = [round(result[i], 7) for i in range(size-1)]

    result_label_least_squares.config(text=f"Result: {result}")

def create_entries_least_squares_for_system():
    global size_entry_least_squares_for_system
    global entries_least_squares_for_system
    global const_entries_least_squares_for_system

    size = int(size_entry_least_squares_for_system[0].get())
    size2 = int(size_entry_least_squares_for_system[1].get())

    for widget in frame_least_squares.winfo_children():
        widget.destroy()

    entries_least_squares_for_system = [[tk.Entry(frame_least_squares, width=5) for _ in range(size-1)] for _ in range(size2)]
    for i in range(size2):
        for j in range(size-1):
            entries_least_squares_for_system[i][j].grid(row=i, column=j)

    const_entries_least_squares_for_system = [tk.Entry(frame_least_squares, width=5) for _ in range(size2)]
    for i in range(size2):
        const_entries_least_squares_for_system[i].grid(row=i, column=size)

def least_squares_for_system_gui():
    global size_entry_least_squares_for_system
    global frame_least_squares
    global result_label_least_squares

    root = tk.Tk()
    root.title("Метод найменших квадратів для СЛАР")

    root.geometry("700x500")

    custom_font = ("Arial", 11)
    root.option_add("*Font", custom_font)

    root.configure(bg='white')

    size_label = tk.Label(root, text="Введіть к-ть колонок:", bg='white')
    size_label.grid(row=0, column=0, padx=5, pady=5)

    columns = tk.Entry(root, width=5)
    columns.grid(row=0, column=1, padx=5, pady=5)

    size_label2 = tk.Label(root, text="Введіть к-ть рядків:", bg='white')
    size_label2.grid(row=1, column=0, padx=5, pady=5)

    rows = tk.Entry(root, width=5)
    rows.grid(row=1, column=1, padx=5, pady=5)

    size_entry_least_squares_for_system.append(columns)
    size_entry_least_squares_for_system.append(rows)

    size_button = tk.Button(root, text="Створити поле для введення", command=create_entries_least_squares_for_system, bd=1, highlightthickness=0)
    size_button.grid(row=3, column=1, padx=5, pady=5)

    frame_least_squares = tk.Frame(root)
    frame_least_squares.grid(row=2, column=0, columnspan=3, pady=10)

    solve_button = tk.Button(root, text="Розв'язати систему", command=solve_least_squares_for_system, bd=1, highlightthickness=0)
    solve_button.grid(row=4, column=1, columnspan=3, pady=10)

    result_label_least_squares = tk.Label(root, text="Розв'язок: ", bg='white')
    result_label_least_squares.grid(row=5, column=1, columnspan=3, pady=5)

    root.mainloop()

# -------------------------------------------------------------------------------------------------------------------------------------------------------

# проста ітерація, СЛАР:

def solve_iteration_method():
    global size_entry_iteration_method
    global entries_iteration_method
    global const_entries_iteration_method

    #get the matrix and constants from the gui
    size = int(size_entry_iteration_method[0].get())
    size2 = int(size_entry_iteration_method[1].get())
    matrix = [[float(entries_iteration_method[i][j].get() if entries_iteration_method[i][j].get() else 0) for j in range(size-1)] for i in range(size2)]
    constants = [float(const_entries_iteration_method[i].get() if const_entries_iteration_method[i].get() else 0) for i in range(size2)]

    x = []
    n = len(matrix)
    for j in range(n):
        k = matrix[j][j]
        for i in range(n):
            matrix[j][i] /= -k
        matrix[j][j] = 0
        constants[j] /= k

    r=0
    x=constants.copy()
    tmp=sum(x)+2*0.00001
    while abs(sum(x)-tmp)>0.00001:
        tmp=sum(x)
        t=[0]*n
        for i in range(n):
            t[i]=sum(x[j]*matrix[i][j] for j in range(n))+constants[i]
        r+=1
        x=t.copy()

    x = [round(x[i], 4) for i in range(size2)]

    result_label_iteration_method.config(text=f"Result: {x}")

def create_entries_iteration_method():
    global size_entry_iteration_method
    global entries_iteration_method
    global const_entries_iteration_method

    size = int(size_entry_iteration_method[0].get())
    size2 = int(size_entry_iteration_method[1].get())

    for widget in frame_iteration_method.winfo_children():
        widget.destroy()

    entries_iteration_method = [[tk.Entry(frame_iteration_method, width=5) for _ in range(size-1)] for _ in range(size2)]
    for i in range(size2):
        for j in range(size-1):
            entries_iteration_method[i][j].grid(row=i, column=j)

    const_entries_iteration_method = [tk.Entry(frame_iteration_method, width=5) for _ in range(size2)]
    for i in range(size2):
        const_entries_iteration_method[i].grid(row=i, column=size)

def iteration_method_gui():
    global frame_iteration_method
    global result_label_iteration_method
    global entrie_function_iteration_method
    global size_entry_iteration_method

    root = tk.Tk()
    root.title("Метод простої ітерації для СЛАР")

    root.geometry("700x500")

    custom_font = ("Arial", 11)
    root.option_add("*Font", custom_font)

    root.configure(bg='white')

    size_label = tk.Label(root, text="Введіть к-ть стовпців:", bg='white')
    size_label.grid(row=0, column=0, padx=5, pady=5)

    columns = tk.Entry(root, width=5)
    columns.grid(row=0, column=1, padx=5, pady=5)

    size_label2 = tk.Label(root, text="Введіть к-ть рядків:", bg='white')
    size_label2.grid(row=1, column=0, padx=5, pady=5)

    rows = tk.Entry(root, width=5)
    rows.grid(row=1, column=1, padx=5, pady=5)

    size_entry_iteration_method.append(columns)
    size_entry_iteration_method.append(rows)

    size_button = tk.Button(root, text="Створити поле для введення", command=create_entries_iteration_method, bd=1, highlightthickness=0)
    size_button.grid(row=3, column=1, padx=5, pady=5)

    frame_iteration_method = tk.Frame(root)
    frame_iteration_method.grid(row=2, column=0, columnspan=3, pady=10)

    solve_button = tk.Button(root, text="Розв'язати систему", command=solve_iteration_method, bd=1, highlightthickness=0)
    solve_button.grid(row=4, column=1, columnspan=3, pady=10)

    result_label_iteration_method = tk.Label(root, text="Результат: ", bg='white')
    result_label_iteration_method.grid(row=5, column=1, columnspan=3, pady=5)

    root.mainloop()


# -------------------------------------------------------------------------------------------------------------------------------------------------------

# метод Ньютона, лінійні:

def solve_newton_method():
    global entries_newton_method
    global entrie_function_newton_method
    global fun_graph_newton_method
    global fx_entry_newton_method
    global result_newton_method
    ans=0

#  ліва_частина_рння - права_частина_рня
    temp = ""
    sd = 1
    flag = False
    fun = str(entrie_function_newton_method.get())
    for it in fun:
        if flag == True:
            sd += 1
            temp = temp + it
        if it == '=':
            flag = True

    fun_len = len(fun)
    fun = fun[0:fun_len - sd]
    fun = fun + "-" + temp

    x=sp.symbols('x')
    fx = sp.sympify(fun)
    fun_graph_newton_method = fx
    f_prime = sp.diff(fx, x)
    f_prime_simplified = sp.simplify(f_prime)

    ans = fx.subs(x, 0)
    if ans>=0:
        flag=True
    else:
        flag=False

# поч значення
    i=1
    while True:
        ans = fx.subs(x, i)
        if ans>=0 and flag==False:
            break
        if ans<0 and flag==True:
            break
        if ans>=0:
            flag=True
        if ans<0:
            flag=False
        i=i+1

# х1 = x0 - f(x0)/f'(x0)
    temp=round(i,1)
    ee=1
    x1=temp - (float(fx.subs(x, temp))/float(f_prime_simplified.subs(x, temp)))
    x1=round(x1,5)
    while ee>0.0001:
        x0=x1
        x1=x0 - (fx.subs(x, x0)/f_prime_simplified.subs(x, x0))
        ee=abs(x1-x0)
        x1=round(x1,5)

    result_newton_method = x1

    result_label_newton_method.config(text=f"Result: {x1}")

def newton_method_gui():
    #global size_entry_newton_method
    global frame_newton_method
    global entrie_function_newton_method
    global result_label_newton_method

    root = tk.Tk()
    root.title("Метод Ньютона для нелінійних р-нь")

    root.geometry("700x500")

    custom_font = ("Arial", 11)
    root.option_add("*Font", custom_font)

    root.configure(bg='white')

    size_Label = tk.Label(root, text="Введіть р-ня у вигляді f(x)=a: ", bg='white')
    size_Label.grid(row=0, column=0, padx=5, pady=5)

    entrie_function_newton_method = tk.Entry(root, width=40)
    entrie_function_newton_method.grid(row=0, column=1, padx=5, pady=5)

    solve_button = tk.Button(root, text="Розв'язати рівняння", command=solve_newton_method, bd=1, highlightthickness=0)
    solve_button.grid(row=2, column=0, columnspan=3, pady=10)

    result_label_newton_method = tk.Label(root, text="Розв'язок: ", bg='white')
    result_label_newton_method.grid(row=3, column=0, columnspan=3, pady=5)

    frame_graph = tk.Frame(root)
    frame_graph.grid(row=4, column=0, columnspan=3, pady=10)

    def create_graph():
        plt.clf()
        global fun_graph_newton_method
        global result_newton_method
        x = sp.symbols('x')
        x_axis = []
        y_axis = []

        for i in np.linspace(float(result_newton_method)-1,float(result_newton_method)+1, 1000):
            x_axis.append(i)
            y_axis.append(fun_graph_newton_method.subs(x, i))
        plt.plot(x_axis, y_axis)

        x_axis = []
        y_axis = []
        for i in np.linspace(float(result_newton_method)-1,float(result_newton_method)+1, 1000):
            x_axis.append(i)
            y_axis.append((float(sp.diff(fun_graph_newton_method,x).subs(x, result_newton_method)))*(i-result_newton_method)+float(fun_graph_newton_method.subs(x, result_newton_method)))
        plt.plot(x_axis, y_axis)

        plt.axhline(y=0, color='k')
        plt.axvline(x=0, color='k')

        plt.plot(result_newton_method, fun_graph_newton_method.subs(x, result_newton_method), 'o')

        canvas = FigureCanvasTkAgg(plt.gcf(), master=frame_graph)
        canvas.draw()
        canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        root.geometry("800x800")

    graph_button = tk.Button(root, text="Показати графік", command=create_graph, bd=1, highlightthickness=0)
    graph_button.grid(row=5, column=0, columnspan=3, pady=10)

    root.mainloop()


# -------------------------------------------------------------------------------------------------------------------------------------------------------

# метод хорд, нелінійні:

def solve_secant_method():
    global entries_secant_method
    global fx_entry_secant_method
    global entrie_function_secant_method
    global fun_graph_secant_method
    global secant_method_points
    global result_secant_method
    global a_secant_method
    global b_secant_method
    
    temp = ""
    sd = 1
    flag = False
    fun = str(entrie_function_secant_method.get())
    for it in fun:
        if flag == True:
            sd += 1
            temp = temp + it
        if it == '=':
            flag = True

    fun_len = len(fun)
    fun = fun[0:fun_len - sd]
    fun = fun + "-" + temp

    x = sp.symbols('x')
    fx = sp.sympify(fun)
    fun_graph_secant_method = fx
    secant_method_points.append(float(a_secant_method.get()))

    def find_root(fx, a, b, eps):
        c = (a*float(fx.subs(x,b)) - b*float(fx.subs(x,a)))/float((float(fx.subs(x,b)) - float(fx.subs(x,a))))
        c1 = (a*float(fx.subs(x,b)) - b*float(fx.subs(x,a)))/float((float(fx.subs(x,b)) - float(fx.subs(x,a))))+1
        while abs(float(c1) - float(c)) > eps:
            secant_method_points.append(c)
            if fx.subs(x,a) * fx.subs(x,c) > 0:
                a = c
            else:
                b = c
            c1 = c
            c = (a*float(fx.subs(x,b)) - b*float(fx.subs(x,a)))/float((float(fx.subs(x,b)) - float(fx.subs(x,a))))
        return c

    root = find_root(fx, float(a_secant_method.get()), float(b_secant_method.get()), 0.0001)
    result_label_secant_method.config(text=f"Result: x = {round(root,5)}")

def secant_method_gui():
    global size_entry_secant_method
    global frame_secant_method
    global result_label_secant_method
    global entrie_function_secant_method
    global a_secant_method
    global b_secant_method

    root = tk.Tk()
    root.title("Метод хорд для нелінійних р-нь")

    root.geometry("700x500")

    custom_font = ("Arial", 11)
    root.option_add("*Font", custom_font)

    root.configure(bg='white')

    size_Label = tk.Label(root, text="Введіть р-ня у вигляді f(x)=a: ", bg='white')
    size_Label.grid(row=0, column=0, padx=5, pady=5)

    entrie_function_secant_method = tk.Entry(root, width=40)
    entrie_function_secant_method.grid(row=0, column=1, padx=5, pady=5)

    a_label = tk.Label(root, text="Введіть точку а: ", bg='white')
    a_label.grid(row=1, column=0, padx=5, pady=5)

    a_secant_method = tk.Entry(root, width=5)
    a_secant_method.grid(row=1, column=1, padx=5, pady=5)

    b_label = tk.Label(root, text="Введіть точку b: ", bg='white')
    b_label.grid(row=2, column=0, padx=5, pady=5)

    b_secant_method = tk.Entry(root, width=5)
    b_secant_method.grid(row=2, column=1, padx=5, pady=5)

    solve_button = tk.Button(root, text="Розв'язати рівняння", command=solve_secant_method, bd=1, highlightthickness=0)
    solve_button.grid(row=3, column=0, columnspan=3, pady=10)

    result_label_secant_method = tk.Label(root, text="Розв'язок: ", bg='white')
    result_label_secant_method.grid(row=4, column=0, columnspan=3, pady=5)

    frame_graph = tk.Frame(root)
    frame_graph.grid(row=5, column=0, columnspan=3, pady=10)


    def create_graph():
        plt.clf()
        global fun_graph_secant_method
        global secant_method_points
        global result_secant_method
        global b_secant_method
        x = sp.symbols('x')
        x_axis = []
        y_axis = []
        for i in np.linspace(float(secant_method_points[0])-1, max(float(b_secant_method.get()),secant_method_points[-1]+1), 1000):
            x_axis.append(i)
            y_axis.append(fun_graph_secant_method.subs(x, i))

        plt.plot(x_axis, y_axis)

        x_axis = []
        y_axis = []
        for i in secant_method_points:
            x_axis.append(i)
            y_axis.append(fun_graph_secant_method.subs(x, i))
        plt.plot(x_axis, y_axis, 'o')

        for i in secant_method_points:
            x_axis = []
            y_axis = []
            x_axis.append(float(b_secant_method.get()))
            x_axis.append(i)
            y_axis.append(fun_graph_secant_method.subs(x, float(b_secant_method.get())))
            y_axis.append(fun_graph_secant_method.subs(x, i))
            plt.plot(x_axis, y_axis)

        #add x and y axis to graph and set limits to fit graph in window
        plt.axhline(y=0, color='k')
        plt.axvline(x=0, color='k')

        canvas = FigureCanvasTkAgg(plt.gcf(), master=frame_graph)
        canvas.draw()
        canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        #set new size of window to fit graph
        root.geometry("800x800")

    graph_button = tk.Button(root, text="Показати графік", command=create_graph, bd=1, highlightthickness=0)
    graph_button.grid(row=6, column=0, columnspan=3, pady=10)

    root.mainloop()


# -------------------------------------------------------------------------------------------------------------------------------------------------------

# лагранж, інтерполяція:

def create_entries_lagrange_polinomial():
    global entries_lagrange_polinomial
    global size_entry_lagrange
    global frame_labrange_polinomial

    size = int(size_entry_lagrange.get())

    for widget in frame_labrange_polinomial.winfo_children():
        widget.destroy()

    entries_lagrange_polinomial = [[tk.Entry(frame_labrange_polinomial, width=5) for _ in range(2)] for _ in range(size)]
    for i in range(size):
        for j in range(2):
            entries_lagrange_polinomial[i][j].grid(row=i+1, column=j)
    x_label = tk.Label(frame_labrange_polinomial, text="x")
    x_label.grid(row=0, column=0, padx=5, pady=5)
    y_label = tk.Label(frame_labrange_polinomial, text="y")
    y_label.grid(row=0, column=1, padx=5, pady=5)

def lagrange_polinomial(x):
    global entries_lagrange_polinomial
    global size_entry_lagrange
    global frame_labrange_polinomial

    size = int(size_entry_lagrange.get())
    result = 0
    for i in range(size):
        temp = 1
        for j in range(size):
            if i!=j:
                temp *= (x - float(entries_lagrange_polinomial[j][0].get()))/(float(entries_lagrange_polinomial[i][0].get()) - float(entries_lagrange_polinomial[j][0].get()))
        result += temp*float(entries_lagrange_polinomial[i][1].get())
    return result

def lagrange_polinomial_gui():
    global size_entry_lagrange
    global frame_labrange_polinomial
    global a_lagrange_entry
    global b_lagrange_entry
    global h_lagrange_entry

    root = tk.Tk()
    root.title("Поліном Лагранжа для інтерполяції")

    root.geometry("700x500")

    custom_font = ("Arial", 11)
    root.option_add("*Font", custom_font)

    root.configure(bg='white')

    size_label = tk.Label(root, text="Введіть к-ть вузлів:", bg='white')
    size_label.grid(row=0, column=0, padx=5, pady=5)

    size_entry_lagrange = tk.Entry(root, width=5)
    size_entry_lagrange.grid(row=0, column=1, padx=5, pady=5)

    size_button = tk.Button(root, text="Створити поле для введення", command=create_entries_lagrange_polinomial, bd=1, highlightthickness=0)
    size_button.grid(row=0, column=2, padx=5, pady=5)

    frame_labrange_polinomial = tk.Frame(root)
    frame_labrange_polinomial.grid(row=1, column=0, columnspan=3, pady=10)

    a_lagrange_label = tk.Label(root, text="Значення а: ", bg='white')
    a_lagrange_label.grid(row=2, column=0, padx=5, pady=5)

    a_lagrange_entry = tk.Entry(root, width=5)
    a_lagrange_entry.grid(row=2, column=1, padx=5, pady=5)

    b_lagrange_label = tk.Label(root, text="Значення b: ", bg='white')
    b_lagrange_label.grid(row=2, column=2, padx=5, pady=5)

    b_lagrange_entry = tk.Entry(root, width=5)
    b_lagrange_entry.grid(row=2, column=3, padx=5, pady=5)

    x_lagrange_label = tk.Label(root, text="Значення x: ", bg='white')
    x_lagrange_label.grid(row=3, column=0, padx=5, pady=5)

    x_lagrange_entry = tk.Entry(root, width=5)
    x_lagrange_entry.grid(row=3, column=1, padx=5, pady=5)

    h_lagrange_label = tk.Label(root, text="К-ть кроків h: ", bg='white')
    h_lagrange_label.grid(row=2, column=4, padx=5, pady=5)

    h_lagrange_entry = tk.Entry(root, width=5)
    h_lagrange_entry.grid(row=2, column=5, padx=5, pady=5)

    def solve_lagrange():
        x = float(x_lagrange_entry.get())
        result = lagrange_polinomial(x)
        method_result.config(text=f'Y = {result}')
    
    solve_button = tk.Button(root, text="Розвʼязати", command=solve_lagrange, bd=1, highlightthickness=0)
    solve_button.grid(row=4, column=0, columnspan=3, pady=10)

    method_result = tk.Label(root, text="Результат: ", bg='white')
    method_result.grid(row=5, column=1, columnspan=3, pady=5)

    #create graph by points geted from lagrange_polinomial function in range from a to b with step h
    def create_graph_lagrange():
        plt.clf()
        a = float(a_lagrange_entry.get())
        b = float(b_lagrange_entry.get())
        h = float(h_lagrange_entry.get())
        hh = (b-a)/h
        x = np.arange(a, b+hh, hh)
        y = [lagrange_polinomial(x[i]) for i in range(len(x))]
        plt.plot(x, y)
        canvas = FigureCanvasTkAgg(plt.gcf(), master=frame_graph_lagrange)
        canvas.draw()
        canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        for i in range(int(size_entry_lagrange.get())):
            plt.plot(float(entries_lagrange_polinomial[i][0].get()), float(entries_lagrange_polinomial[i][1].get()), 'o')

        #set new size of window to fit graph
        root.geometry("800x800")

    frame_graph_lagrange = tk.Frame(root)
    frame_graph_lagrange.grid(row=4, column=0, columnspan=3, pady=10)

    solve_button2 = tk.Button(root, text="Показати графік", command=create_graph_lagrange, bd=1, highlightthickness=0)
    solve_button2.grid(row=6, column=0, columnspan=3, pady=10)

    root.mainloop()


# -------------------------------------------------------------------------------------------------------------------------------------------------------

# ньютон, інтерполяція:

def create_entries_newton_interpolation():
    global entries_newton_interpolation
    global size_entry_newton_interpolation
    global frame_newton_interpolation

    size = int(size_entry_newton_interpolation.get())

    for widget in frame_newton_interpolation.winfo_children():
        widget.destroy()

    entries_newton_interpolation = [[tk.Entry(frame_newton_interpolation, width=5) for _ in range(2)] for _ in range(size)]
    for i in range(size):
        for j in range(2):
            entries_newton_interpolation[i][j].grid(row=i+1, column=j)
    x_label = tk.Label(frame_newton_interpolation, text="x")
    x_label.grid(row=0, column=0, padx=5, pady=5)
    y_label = tk.Label(frame_newton_interpolation, text="y")
    y_label.grid(row=0, column=1, padx=5, pady=5)

def create_D_matrix_newton_interpolation():
    global entries_newton_interpolation
    global size_entry_newton_interpolation
    global frame_newton_interpolation

    size = int(size_entry_newton_interpolation.get())
    D_matrix = [[0 for _ in range(size)] for _ in range(size)]
    for i in range(size):
        D_matrix[i][0] = float(entries_newton_interpolation[i][1].get())
    for j in range(1, size):
        for i in range(size-j):
            D_matrix[i][j] = (D_matrix[i+1][j-1] - D_matrix[i][j-1])/(float(entries_newton_interpolation[i+j][0].get()) - float(entries_newton_interpolation[i][0].get()))
    return D_matrix

def newton_interpolation(x, D_matrix):
    global entries_newton_interpolation
    global size_entry_newton_interpolation
    global frame_newton_interpolation

    size = int(size_entry_newton_interpolation.get())
    result = 0
    for i in range(size):
        temp = 1
        for j in range(i):
            temp *= (x - float(entries_newton_interpolation[j][0].get()))
        result += temp*D_matrix[0][i]
    return result

def newton_interpolation_gui():
    global size_entry_newton_interpolation
    global frame_newton_interpolation
    global a_newton_interpolation_entry
    global b_newton_interpolation_entry
    global h_newton_interpolation_entry

    root = tk.Tk()
    root.title("Метод Ньютона для інтерполяції")

    root.geometry("700x500")

    custom_font = ("Arial", 11)
    root.option_add("*Font", custom_font)

    root.configure(bg='white')

    size_label = tk.Label(root, text="Введіть к-ть вузлів:", bg='white')
    size_label.grid(row=0, column=0, padx=5, pady=5)

    size_entry_newton_interpolation = tk.Entry(root, width=5)
    size_entry_newton_interpolation.grid(row=0, column=1, padx=5, pady=5)

    size_button = tk.Button(root, text="Створити поле для введення", command=create_entries_newton_interpolation, bd=1, highlightthickness=0)
    size_button.grid(row=0, column=2, padx=5, pady=5)

    frame_newton_interpolation = tk.Frame(root)
    frame_newton_interpolation.grid(row=1, column=0, columnspan=3, pady=10)

    a_newton_interpolation_label = tk.Label(root, text="Значення а: ", bg='white')
    a_newton_interpolation_label.grid(row=2, column=0, padx=5, pady=5)

    a_newton_interpolation_entry = tk.Entry(root, width=5)
    a_newton_interpolation_entry.grid(row=2, column=1, padx=5, pady=5)

    b_newton_interpolation_label = tk.Label(root, text="Значення b: ", bg='white')
    b_newton_interpolation_label.grid(row=2, column=2, padx=5, pady=5)

    b_newton_interpolation_entry = tk.Entry(root, width=5)
    b_newton_interpolation_entry.grid(row=2, column=3, padx=5, pady=5)

    h_newton_interpolation_label = tk.Label(root, text="К-ть кроків h: ", bg='white')
    h_newton_interpolation_label.grid(row=2, column=4, padx=5, pady=5)

    h_newton_interpolation_entry = tk.Entry(root, width=5)
    h_newton_interpolation_entry.grid(row=2, column=5, padx=5, pady=5)
    
    x_newton_interpolation_label = tk.Label(root, text="Значення x: ", bg='white')
    x_newton_interpolation_label.grid(row=3, column=0, padx=5, pady=5)

    x_newton_interpolation_entry = tk.Entry(root, width=5)
    x_newton_interpolation_entry.grid(row=3, column=1, padx=5, pady=5)

    def solve_newton_i():
        x = float(x_newton_interpolation_entry.get())
        D_matrix = create_D_matrix_newton_interpolation()
        result = newton_interpolation(x, D_matrix)
        method_result.config(text=f'Y = {result}')
    
    solve_button = tk.Button(root, text="Розвʼязати", command=solve_newton_i, bd=1, highlightthickness=0)
    solve_button.grid(row=4, column=0, columnspan=3, pady=10)

    method_result = tk.Label(root, text="Результат: ", bg='white')
    method_result.grid(row=5, column=1, columnspan=3, pady=5)

    def create_graph_newton_interpolation():
        D_matrix = create_D_matrix_newton_interpolation()
        plt.clf()
        a = float(a_newton_interpolation_entry.get())
        b = float(b_newton_interpolation_entry.get())
        h = float(h_newton_interpolation_entry.get())
        hh = (b-a)/h
        x = np.arange(a, b+hh, hh)
        y = [newton_interpolation(x[i], D_matrix) for i in range(len(x))]
        plt.plot(x, y)
        canvas = FigureCanvasTkAgg(plt.gcf(), master=frame_graph_newton_interpolation)
        canvas.draw()
        canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        for i in range(int(size_entry_newton_interpolation.get())):
            plt.plot(float(entries_newton_interpolation[i][0].get()), float(entries_newton_interpolation[i][1].get()), 'o')

        #set new size of window to fit graph
        root.geometry("800x800")

    solve_button = tk.Button(root, text="Показати графік", command=create_graph_newton_interpolation, bd=1, highlightthickness=0)
    solve_button.grid(row=6, column=0, columnspan=3, pady=10)

    frame_graph_newton_interpolation = tk.Frame(root)
    frame_graph_newton_interpolation.grid(row=4, column=0, columnspan=3, pady=10)

    root.mainloop()


# -------------------------------------------------------------------------------------------------------------------------------------------------------

# інтеграли:

def solve_integral():
    global result_label_integral_1
    global result_label_integral_2
    global result_label_integral_3
    global entrie_function_integral
    global a_integral_entry
    global b_integral_entry
    global n_integral_entry

    x = sp.symbols('x')
    fun = sp.sympify(entrie_function_integral.get())
    a = float(a_integral_entry.get())
    b = float(b_integral_entry.get())
    n = int(n_integral_entry.get())

    #solve using rectangles
    h = (b-a)/n
    result = 0
    for i in np.linspace(a,b,n):
        result += fun.subs(x, i)
    result = result*h
    result_label_integral_1.config(text=f"Розвʼязок м-м прямокутників: {round(result, 5)}")
    
    #solve using trapezium
    result = 0
    for i in np.linspace(a,b,n):
        result += (fun.subs(x, i)+fun.subs(x, i+((a+b)/n))) / 2
    result = result*h
    result_label_integral_2.config(text=f"Розвʼязок м-м трапеції: {round(result, 5)}")
    
    #solve using simpson's rule
    result = 0
    for i in np.linspace(a,b,n):
        result += (fun.subs(x, i)+4*fun.subs(x, i+((a+b)/n)/2)+fun.subs(x, i+((a+b)/n)))/6
    result = result*h
    result_label_integral_3.config(text=f"Розвʼязок м-м параболи: {round(result, 5)}")

def integral_gui():
    global frame_integral
    global result_label_integral_1
    global result_label_integral_2
    global result_label_integral_3
    global entrie_function_integral
    global a_integral_entry
    global b_integral_entry
    global n_integral_entry

    root = tk.Tk()
    root.title("Обчислення інтегралів")

    root.geometry("700x500")

    custom_font = ("Arial", 11)
    root.option_add("*Font", custom_font)

    root.configure(bg='white')

    a_integral_label = tk.Label(root, text="Значення a: ", bg='white')
    a_integral_label.grid(row=0, column=0, padx=5, pady=5)

    a_integral_entry = tk.Entry(root, width=5)
    a_integral_entry.grid(row=0, column=1, padx=5, pady=5)

    b_integral_label = tk.Label(root, text="Значення b: ", bg='white')
    b_integral_label.grid(row=0, column=2, padx=5, pady=5)

    b_integral_entry = tk.Entry(root, width=5)
    b_integral_entry.grid(row=0, column=3, padx=5, pady=5)

    n_integral_label = tk.Label(root, text="К-ть розбиттів: ", bg='white')
    n_integral_label.grid(row=0, column=4, padx=5, pady=5)

    n_integral_entry = tk.Entry(root, width=5)
    n_integral_entry.grid(row=0, column=5, padx=5, pady=5)

    label_function_integral = tk.Label(root, text="Підінтегральна ф-я: ", bg='white')
    label_function_integral.grid(row=1, column=0, padx=5, pady=5)

    entrie_function_integral = tk.Entry(root, width=40)
    entrie_function_integral.grid(row=1, column=1, columnspan=6, padx=5, pady=5)

    solve_button = tk.Button(root, text="Розвʼязати", command=solve_integral, bd=1, highlightthickness=0)
    solve_button.grid(row=2, column=0, columnspan=6, pady=10)

    result_label_integral_1 = tk.Label(root, text="Розвʼязок м-м прямокутників: ", bg='white')
    result_label_integral_1.grid(row=3, column=0, columnspan=6, pady=5)

    result_label_integral_2 = tk.Label(root, text="Розвʼязок м-м трапеції: ", bg='white')
    result_label_integral_2.grid(row=4, column=0, columnspan=6, pady=5)

    result_label_integral_3 = tk.Label(root, text="Розвʼязок м-м параболи: ", bg='white')
    result_label_integral_3.grid(row=5, column=0, columnspan=6, pady=5)

    root.mainloop()

# -------------------------------------------------------------------------------------------------------------------------------------------------------
 

def main():
    root = tk.Tk()
    root.title("Калькулятор для розв'язування чисельних методів")

    root.geometry("700x500")

    custom_font = ("Arial", 11)
    root.option_add("*Font", custom_font)

    root.configure(bg='white')

    title_label = tk.Label(root, text="Розв'язування СЛАР:", bg='white')
    title_label.grid(row=0, column=0, padx=5, pady=5)

    gauss_button = tk.Button(root, text="Метод Гауса", command=gauss_gui, bd=1, highlightthickness=0)
    gauss_button.grid(row=1, column=0, padx=5, pady=5)

    least_squares_button = tk.Button(root, text="Метод найменших квадратів", command=least_squares_for_system_gui, bd=1, highlightthickness=0)
    least_squares_button.grid(row=1, column=1, padx=5, pady=5)

    iteration_method_button = tk.Button(root, text="Метод простої ітерації", command=gauss_gui, bd=1, highlightthickness=0)
    iteration_method_button.grid(row=1, column=2, padx=5, pady=5)

    title_label = tk.Label(root, text="Розв'язування нелінійних р-нь:", bg='white')
    title_label.grid(row=3, column=0, padx=5, pady=5)

    newton_method_button = tk.Button(root, text="Метод Ньютона", command=newton_method_gui, bd=1, highlightthickness=0)
    newton_method_button.grid(row=4, column=0, padx=5, pady=5)

    newton_method_button = tk.Button(root, text="Метод хорд", command=secant_method_gui, bd=1, highlightthickness=0)
    newton_method_button.grid(row=4, column=1, padx=5, pady=5)

    title_label = tk.Label(root, text="Інтерполяція:", bg='white')
    title_label.grid(row=6, column=0, padx=5, pady=5)

    lagrange_polinomial_button = tk.Button(root, text="Поліномами Лагранжа", command=lagrange_polinomial_gui, bd=1, highlightthickness=0)
    lagrange_polinomial_button.grid(row=7, column=0, padx=5, pady=5)

    newton_interpolation_button = tk.Button(root, text="Інтерполяція Ньютона", command=newton_interpolation_gui, bd=1, highlightthickness=0)
    newton_interpolation_button.grid(row=7, column=1, padx=5, pady=5)

    title_label = tk.Button(root, text="Обчислення інтегралів", command=integral_gui, bd=1, highlightthickness=0)
    title_label.grid(row=8, column=1, padx=5, pady=5)

    root.mainloop()


if __name__ == "__main__":
    main()
