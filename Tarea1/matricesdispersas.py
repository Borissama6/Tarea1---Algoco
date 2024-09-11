import numpy as np
from scipy.sparse import random

def valores_enteros_aleatorios(shape):
    return np.random.randint(0, 100, size=shape)

def generar_matrices_disp_y_guardar(tamanio, i, densidad):
    matriz1 = random(tamanio, tamanio, density=densidad, format='coo', data_rvs=valores_enteros_aleatorios).toarray()
    matriz2 = random(tamanio, tamanio, density=densidad, format='coo', data_rvs=valores_enteros_aleatorios).toarray()
    nombre_archivo = f'matricescxf{i}.txt'
    with open(nombre_archivo, 'w') as archivo:
        for fila in matriz1:
            archivo.write(' '.join(map(str, fila)) + '\n')
        archivo.write('\n')
        for fila in matriz2:
            archivo.write(' '.join(map(str, fila)) + '\n')
    
    print(f'Matrices Hilbert guardadas en {nombre_archivo}')

densidad = 0.1

i = 0
for n in [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]:
    generar_matrices_disp_y_guardar(n, i, densidad)
    i += 1


