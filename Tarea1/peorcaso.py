count = 0
a = 0
b = 1000
limit = 10
xd = 10
while count < 6:
    with open(f'peorcaso{count}.txt', 'w') as f:
        pass
    i = 0
    lista = []
    while xd > 0:
        lista.append(xd)
        i += 1
        xd -= 1
    limit *= 10
    xd = limit

    with open(f'peorcaso{count}.txt','a') as f:
        for i in lista:
            i = str(i) + ' '
            f.write(i)
    count += 1