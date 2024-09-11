import random

def generar_matriz(filas, columnas, a, b):
    """Genera una matriz de tamaño filas x columnas con números aleatorios entre a y b."""
    matriz = []
    for i in range(filas):
        fila = []
        for j in range(columnas):
            fila.append(random.randint(a, b))
        matriz.append(fila)
    return matriz

def guardar_matriz_en_archivo(matriz, filename):
    """Guarda una matriz en un archivo."""
    with open(filename, 'w') as f:
        for fila in matriz:
            fila_str = ' '.join(map(str, fila))
            f.write(fila_str + '\n')

def generar_datasets_matrices(cantidad_datasets, a, b):
    """Genera y guarda datasets de matrices cuadradas con tamaños en potencias de 2."""
    limit = 2
    for count in range(cantidad_datasets):
        filename = f'matriz{limit}x{limit}.txt'
        matriz = generar_matriz(limit, limit, a, b)
        guardar_matriz_en_archivo(matriz, filename)
        print(f'Matriz guardada en {filename}')
        limit *= 2  # Incrementar el tamaño de la matriz en potencias de 2

# Parámetros
cantidad_datasets = 6  # Número de datasets (matrices cuadradas) a generar
a = 0                  # Valor mínimo de los elementos de la matriz
b = 1000                # Valor máximo de los elementos de la matriz

# Generar los datasets
generar_datasets_matrices(cantidad_datasets, a, b)
