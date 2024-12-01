import matplotlib.pyplot as plt

# Datos de los tamaños de los arrays
tamanios = [2500, 5000, 10000, 35000, 80000, 120000, 150000]

# Tiempos del caso promedio para cada algoritmo (en segundos)
# Selección
tiempos_seleccion = [0.003000, 0.013000, 0.050000, 0.580000, 2.990000, 6.747000, 10.601000]

# Burbujeo
tiempos_burbujeo = [0.006000, 0.025000, 0.095000, 1.204000, 7.377000, 18.847000, 29.663000]

# Inserción
tiempos_insercion = [0.003000, 0.008000, 0.034000, 0.427000, 2.421000, 4.798000, 6.821000]

# Shell
tiempos_shell = [0.000000, 0.000000, 0.001000, 0.004000, 0.011000, 0.018000, 0.021000]

# QuickSort
tiempos_quicksort = [0.000000, 0.000000, 0.001000, 0.002000, 0.005000, 0.008000, 0.009000]

def graficar_algoritmo(tamanios, tiempos, titulo, color):
    plt.figure()
    plt.plot(tamanios, tiempos, marker='o', color=color)
    plt.title(titulo)
    plt.xlabel('Elementos')
    plt.ylabel('Tiempo (segundos)')
    plt.xticks(tamanios, rotation=45)
    plt.grid(True)
    plt.show()

def graficar_todos_juntos(tamanios, tiempos_dict):
    plt.figure()
    for algoritmo, datos in tiempos_dict.items():
        plt.plot(tamanios, datos['tiempos'], marker='o', label=algoritmo, color=datos['color'])
    plt.title('Comparación de Algoritmos de Ordenamiento (Caso Promedio)')
    plt.xlabel('Elementos')
    plt.ylabel('Tiempo (segundos)')
    plt.yscale('log')
    plt.xticks(tamanios, rotation=45)
    plt.legend()
    plt.grid(True)
    plt.show()

def main():
    print("Seleccione una opción:")
    print("1. Graficar cada algoritmo por separado")
    print("2. Graficar todos los algoritmos juntos para comparar")
    opcion = input("Ingrese el número de la opción deseada: ")

    if opcion == '1':
        # Graficar cada algoritmo por separado
        graficar_algoritmo(tamanios, tiempos_seleccion, 'Selección', 'blue')
        graficar_algoritmo(tamanios, tiempos_burbujeo, 'Burbujeo', 'red')
        graficar_algoritmo(tamanios, tiempos_insercion, 'Inserción', 'green')
        graficar_algoritmo(tamanios, tiempos_shell, 'Shell', 'purple')
        graficar_algoritmo(tamanios, tiempos_quicksort, 'QuickSort', 'orange')
    elif opcion == '2':
        # Graficar todos los algoritmos juntos
        tiempos_algoritmos = {
            'Selección': {'tiempos': tiempos_seleccion, 'color': 'blue'},
            'Burbujeo': {'tiempos': tiempos_burbujeo, 'color': 'red'},
            'Inserción': {'tiempos': tiempos_insercion, 'color': 'green'},
            'Shell': {'tiempos': tiempos_shell, 'color': 'purple'},
            'QuickSort': {'tiempos': tiempos_quicksort, 'color': 'orange'},
        }
        graficar_todos_juntos(tamanios, tiempos_algoritmos)
    else:
        print("Opción inválida.")

if __name__ == "__main__":
    main()
