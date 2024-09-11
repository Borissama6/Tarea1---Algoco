import random

count = 0
a = 0
b = 1000
limit = 10

while count < 6:
    i = 0
    lista = []
    while i < limit:
        rand = random.randint(a,b)
        lista.append(rand)
        i += 1
    limit *= 10
    with open(f'random{count}.txt','a') as f:
        for i in lista:
            i = str(i) + ' '
            f.write(i)
    count += 1

limit = 10
count = 0
while count < 6:
    i = 0
    lista = []
    while i < limit:
        lista.append(i)
        i += 1
    limit *= 10
    with open(f'mejorcaso{count}.txt','a') as f:
        for i in lista:
            i = str(i) + ' '
            f.write(i)
    count += 1

limit = 10
count = 0
while count < 6:
    i = limit
    lista = []
    while i > 0:
        lista.append(i)
        i -= 1
    limit *= 10
    with open(f'peorcaso{count}.txt','a') as f:
        for i in lista:
            i = str(i) + ' '
            f.write(i)
    count += 1

limit = 10
count = 0
while count < 6:
    i = 0
    lista = []
    while i < limit/2:
        lista.append(i)
        i += 1
    while i < limit:
        rand = random.randint(a,b)
        lista.append(rand)
        i += 1
    limit *= 10
    with open(f'semiordenado{count}.txt','a') as f:
        for i in lista:
            i = str(i) + ' '
            f.write(i)
    count += 1

limit = 10
count = 0
while count < 6:
    i = 0
    lista = []
    while i < limit/2:
        lista.append(i)
        i += 1
    i = limit
    while i > limit/2:
        lista.append(i)
        i -= 1
    limit *= 10
    with open(f'ordenadoydesordenado{count}.txt','a') as f:
        for i in lista:
            i = str(i) + ' '
            f.write(i)
    count += 1

limit = 10
count = 0
while count < 6:
    
    lista = []
    i = limit
    while i > limit/2:
        lista.append(i)
        i -= 1
    i = 0
    while i < limit/2:
        lista.append(i)
        i += 1
    
    limit *= 10
    with open(f'desordenadoyordenado{count}.txt','a') as f:
        for i in lista:
            i = str(i) + ' '
            f.write(i)
    count += 1