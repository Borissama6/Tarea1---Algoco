import random

count = 0
a = 0
b = 1000
limit = 10

while count < 6:
    filename = f'semiordenado{count}.txt'
    lista = []
    half_limit = limit // 2
    for i in range(1, half_limit + 1):
        lista.append(i)

    while len(lista) < limit:
        rand = random.randint(a, b)
        lista.append(rand)
    
    with open(filename, 'w') as f:
        for number in lista:
            f.write(f'{number} ')

    limit *= 10
    count += 1

