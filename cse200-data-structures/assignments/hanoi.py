num = int(input())

time = 0
a = 1
b = 2
c = 3
all = a + b + c
logs = []

def moveDist(origin, dest, n):
    global time
    if n == 1:
        return 0
    moveDist(origin, all - origin - dest, n - 1)
    logs.append(str(origin) + " " + str(dest))
    time += 1
    moveDist(all - origin - dest, dest, n - 1)


moveDist(1, 3, num + 1)

print(time)
for i in logs:
    print(i)