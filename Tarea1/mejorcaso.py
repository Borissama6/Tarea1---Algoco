count = 0
a = 0
b = 1000
limit = 10
xd = 10
while count < 6:
    with open(f'mejorcaso{count}.txt', 'w') as f:
        pass
    i = 0
    lista = []
    while i < xd:
        lista.append(i)
        i += 1
    xd *= 10

    with open(f'mejorcaso{count}.txt','a') as f:
        for i in lista:
            i = str(i) + ' '
            f.write(i)
    count += 1