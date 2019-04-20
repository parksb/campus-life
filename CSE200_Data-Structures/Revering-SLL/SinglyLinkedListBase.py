# Department of Digital Media 201700000 Park Seong-beom

class SinglyLinkedList:
    class _Node:
        __slots__ = '_element', '_next'

        def __init__(self, element, next=None):
            self._element = element
            self._next = next

        def element(self):
            return self._element

        def next(self):
            return self._next

        def set_element(self, element):
            self._element = element

        def set_next(self, next):
            self._next = next

    def __init__(self, head=None):
        self._head = head

    def __len__(self):
        length = 0
        node = self._head
        while node:
            length += 1
            node = node.next()
        return length

    def __str__(self):
        count = 0
        if self.is_empty():
            return str(count)+": "+str([])
        else:
            answer = []
            t = self._head
            while t:
                answer.append(t.element())
                t = t.next()
                count += 1
        return str(count)+": "+str(answer)

    def is_empty(self):
        return self._head == None

    def head(self):
        return self._head

    def insert_first(self, element):
        newNode = self._Node(element, self._head)
        self._head = newNode

    def remove_first(self):
        if self.is_empty():
            raise IndexError

        element = self._head.element()
        self._head = self._head.next()

        return element

    def insert_last(self, element):
        newNode = self._Node(element)
        if self.is_empty():
            self._head = newNode
        else:
            t = self._head
            while t.next():
                t = t.next()
            t.set_next(newNode)

    def remove_last(self):
        if self.is_empty():
            raise IndexError

        if self._head.next() is None:
            element = self._head.element()
            self._head = None
        else:
            t = self._head
            while t.next().next():
                t = t.next()
            element = t.next().element()
            t.set_next(None)

        return element

    def is_even(self):
        t = self._head
        while t is not None and t.getNext() is not None:
            t = t.next().next()

        if t is None:
            return True
        else:
            return False

    def find_middle(self):
        fast = self._head
        slow = self._head

        while fast is not None:
            fast = fast.next()
            if fast is None:
                return slow.element()
            fast = fast.next()
            slow = slow.next()

        return slow.element()

    def reverse(self, node):
        if node.next() is not None:
            self.reverse(node.next()).set_next(node)
        else:
            self.head().set_next(None)
            self._head = node

        return node


if __name__ == "__main__":
    sl = SinglyLinkedList()

    sl.insert_first("B")
    sl.insert_first("A")
    sl.insert_last("C")

    print(sl)
    e = sl.remove_last()
    print(sl)
    e = sl.remove_first()
    print(sl)
    e = sl.remove_first()
    print(sl)

    # removing will cause execption
    sl.insert_first("A")
    sl.insert_last("B")
    sl.insert_last("C")
    sl.insert_first("0")
    sl.insert_first("1")
    print(sl)

    print("Middle: {}".format(sl.find_middle()))
    e = sl.remove_last()
    print(sl)
    print("Middle: {}".format(sl.find_middle()))
    e = sl.remove_last()
    print(sl)
    print("Middle: {}".format(sl.find_middle()))
    e = sl.remove_first()
    print(sl)
    print("Middle: {}".format(sl.find_middle()))

    s1 = SinglyLinkedList()
    s1.insert_last("1")
    s1.insert_last("2")
    s1.insert_last("3")
    s1.insert_last("4")
    s1.insert_last("5")
    print(s1)

    try:
        s1.reverse(s1.head())
    except NotImplementedError:
        print("This homework is not yet implemented!!!")

    print(s1)