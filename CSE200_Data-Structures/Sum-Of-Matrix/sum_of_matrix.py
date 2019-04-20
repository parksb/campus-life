import numpy as np

def sum_of_list(a_list):
    if len(a_list) == 1:
        return a_list[0]
    else:
        return a_list[0] + sum_of_list(a_list[1:])
    
def sum_of_matrix(a_matrix):
    if len(a_matrix) == 1:
        return sum_of_list(a_matrix[0])
    else:
        return sum_of_list(a_matrix[0]) + sum_of_matrix(a_matrix[1:])

data = np.random.random((4,5))
print(data)
result = sum_of_matrix(data)
print(result)
