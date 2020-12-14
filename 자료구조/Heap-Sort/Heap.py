from BinaryTree import BinaryTree


class Heap(BinaryTree):
    def __init__(self, element):
        super().__init__(element)
        self._last = self

    def bubbling(self, node):
        if not node.is_root() and node.parent().element() > node.element():
            node._element, node.parent()._element = node.parent().element(), node.element()
            self.bubbling(node.parent())

    def search_last(self):
        node = self

        while not node.is_root():
            node = node.parent()

        if node.is_external():
            return node

        left_node = node
        while left_node.is_internal():
            if left_node.left() is not None:
                left_node = left_node.left()
        left_depth = left_node.depth()

        right_node = node
        while right_node.is_internal():
            if right_node.right() is not None:
                right_node = right_node.right()
            else:
                right_node = right_node.left()
        right_depth = right_node.depth()

        if left_depth == right_depth:
            if right_node.parent().right() is not None:
                return left_node
        elif left_depth - right_depth < 2:
            if self._last.parent().right() is not self._last:
                return left_node
            elif self._last.parent().parent().right() is not None:
                return self._last.parent().parent().right()
        return right_node

    def insert(self, new_element):
        node = self.search_last()

        if node.is_root():
            node.add_left(new_element)
            self._last = node.left()
            self.bubbling(node.left())
        elif node.parent().left() is None:
            node.parent().add_left(new_element)
            self._last = node.parent().left()
            self.bubbling(node.parent().left())
        elif node.parent().right() is None:
            node.parent().add_right(new_element)
            self._last = node.parent().right()
            self.bubbling(node.parent().right())
        else:
            node.add_left(new_element)
            self._last = node.left()
            self.bubbling(node.left())

    def down_heap(self, node):
        if node.is_external():
            self._last = node
        elif node.is_internal():
            if node.left() is None:
                if node.right().element() < node.element():
                    node._element, node.right()._element = node.right().element(), node.element()
                    node = node.right()
                else:
                    node = node.right()
            elif node.right() is None:
                if node.left().element() < node.element():
                    node._element, node.left()._element = node.left().element(), node.element()
                    node = node.left()
                else:
                    node = node.left()
            elif node.left().element() < node.right().element():
                node._element, node.left()._element = node.left().element(), node.element()
                node = node.left()
            else:
                node._element, node.right()._element = node.right().element(), node.element()
                node = node.right()
            self._last = node
            self.down_heap(node)

    def remove_min(self):
        node = self._last

        root = node
        while not root.is_root():
            root = root.parent()

        root._element, node._element = node.element(), root.element()

        min = node.element()
        node.delete()

        self.down_heap(root)

        return min
