import numpy as np

def generar_matrices(tamanio, i):
    matriz1 = np.random.randint(0, 100, size=(tamanio, tamanio))
    matriz2 = np.random.randint(0, 100, size=(tamanio, tamanio))
    nombre_archivo = f'matricescxf{i}.txt'
    with open(nombre_archivo, 'w') as archivo:
        for fila in matriz1:
            archivo.write(' '.join(map(str, fila)) + '\n')
        archivo.write('\n')
        for fila in matriz2:
            archivo.write(' '.join(map(str, fila)) + '\n')

    print(f'Matrices de {tamanio}x{tamanio} guardadas en {nombre_archivo}')

i = 0
for n in [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]:
    generar_matrices(n, i)
    i = i + 1
