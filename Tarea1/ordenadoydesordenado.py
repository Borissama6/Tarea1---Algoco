import random

count = 0
a = 0
b = 1000
limit = 10

while count < 6:
    filename = f'ordenadoydesordenado{count}.txt'
    # Inicializar la lista
    lista = []
    
    # Calcular la mitad del límite
    half_limit = limit // 2
    
    # Escribir números en orden ascendente desde 0 hasta half_limit - 1
    for i in range(half_limit):
        lista.append(i)
    
    # Escribir números en orden descendente desde limit - 1 hasta half_limit
    for i in range(limit - 1, half_limit - 1, -1):
        lista.append(i)
    
    # Agregar números aleatorios para completar el archivo si es necesario
    while len(lista) < limit:
        rand = random.randint(a, b)
        lista.append(rand)
    
    # Escribir la lista en el archivo
    with open(filename, 'w') as f:
        for number in lista:
            f.write(f'{number} ')
    
    # Aumentar el límite para la próxima iteración
    limit *= 10
    count += 1