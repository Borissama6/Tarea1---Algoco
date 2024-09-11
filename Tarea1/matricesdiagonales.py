import numpy as np

def generar_matriz_diagonal(tamanio):
    matriz = np.diag(np.random.randint(1, 1000, size=tamanio))
    return matriz

def guardar_matriz_en_txt(matriz1, matriz2, nombre_archivo):
    with open(nombre_archivo, 'w') as archivo:
        for fila in matriz1:
            archivo.write(' '.join(map(str, fila)) + '\n')
        archivo.write('\n')
        for fila in matriz2:
            archivo.write(' '.join(map(str, fila)) + '\n')

def generar_y_guardar_matrices_diagonales(tamanio, i):
    matriz1 = generar_matriz_diagonal(tamanio)
    matriz2 = generar_matriz_diagonal(tamanio)
    nombre_archivo = f'diagonal_matrices_{i}.txt'
    guardar_matriz_en_txt(matriz1, matriz2, nombre_archivo)
    print(f'Matrices diagonales de {tamanio}x{tamanio} guardadas en {nombre_archivo}')

i = 0
for n in [2,4, 8, 16, 32, 64, 128,256,512,1024,2048,4096]:
    generar_y_guardar_matrices_diagonales(n, i)
    i += 1
