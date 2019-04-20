class Stack:
    def __init__(self):
        self._data = []

    def push(self, value):
        self._data.append(value)

    def pop(self):
        if self.isEmpty():
            raise IndexError('Stack is empty')
        return self._data.pop()

    def size(self):
        return len(self._data)

    def isEmpty(self):
        return len(self._data) == 0

    def top(self):
        if self.isEmpty():
            raise IndexError('Stack is empty')
        return self._data[-1]

    def print(self):
        print("[ ", end="")
        for i in self._data:
            print(i, " ", end="")
        print("]")