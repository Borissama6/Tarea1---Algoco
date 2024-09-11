import numpy as np

def generar_matrices_y_guardar(dim1, dim2, dim3, dim4, i):
    matriz1 = np.random.randint(0, 100, size=(dim1, dim2))
    matriz2 = np.random.randint(0, 100, size=(dim3, dim4))
    nombre_archivo = f'matricescxf{i}.txt'
    with open(nombre_archivo, 'w') as archivo:
        for fila in matriz1:
            archivo.write(' '.join(map(str, fila)) + '\n')
        archivo.write('\n')
        for fila in matriz2:
            archivo.write(' '.join(map(str, fila)) + '\n')

    print(f'Matrices de {dim1}x{dim2} y {dim3}x{dim4} guardadas en {nombre_archivo}')

i = 0
dimensiones = [(2, 3, 3, 4),(4, 5, 5, 6),(8, 10, 10, 12),(16, 20, 20, 24),(32, 40, 40, 48),(64, 80, 80, 96),(128, 160, 160, 192),
               (256, 320, 320, 384),(512, 640, 640, 768),(1024, 1280, 1280, 1536),(2048, 2560, 2560, 3072),(4096, 5120, 5120, 6144)]

for dims in dimensiones:
    generar_matrices_y_guardar(*dims, i)
    i += 1
