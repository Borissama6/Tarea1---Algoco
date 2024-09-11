import numpy as np

def generar_matriz_hilbert(tamanio):
    matriz = np.zeros((tamanio, tamanio))
    for i in range(tamanio):
        for j in range(tamanio):
            matriz[i, j] = 1 / (i + j + 1)
    return matriz

def guardar_matriz_en_txt(matriz1, matriz2, nombre_archivo):
    with open(nombre_archivo, 'w') as archivo:
        for fila in matriz1:
            archivo.write(' '.join(map(str, fila)) + '\n')
        archivo.write('\n')
        for fila in matriz2:
            archivo.write(' '.join(map(str, fila)) + '\n')

def generar_y_guardar_matrices_hilbert(tamanio, i):
    matriz1 = generar_matriz_hilbert(tamanio)
    matriz2 = generar_matriz_hilbert(tamanio)
    nombre_archivo = f'hilbert_matrices_{i}.txt'
    guardar_matriz_en_txt(matriz1, matriz2, nombre_archivo)
    print(f'Matrices de Hilbert de {tamanio}x{tamanio} guardadas en {nombre_archivo}')

i = 0
for n in [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]:
    generar_y_guardar_matrices_hilbert(n, i)
    i += 1
