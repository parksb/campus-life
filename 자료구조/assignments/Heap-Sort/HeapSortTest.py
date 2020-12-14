import random
import time
from Heap import Heap

count = 100
a_list = []
for i in range(count):
    a_list.append(random.randrange(1, 100 * count))
print(a_list)

s_time = time.time()
aHeap = Heap(0)
for i in range(count):
    aHeap.insert(a_list[i])

sorted_list = []
for i in range(count + 1):
    sorted_list.append(aHeap.remove_min())
e_time = time.time()
print(sorted_list)
print("Execution time : ", (e_time - s_time) * 1000, "ms")
