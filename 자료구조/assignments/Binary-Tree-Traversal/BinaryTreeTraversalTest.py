class BinaryTree:
    def __init__(self, element, parent=None, left=None, right=None):
        __slots__ = '_element', '_parent', '_left', '_right'

        self._element = element
        self._parent = parent
        self._left = left
        self._right = right

    def __str__(self):
        return "[ " + str(self._element) + \
               (" " + str(self._left) if self._left else '') + \
               (" " + str(self._right) if self._right else '') + " ]"

    def element(self):
        return self._element

    def parent(self):
        return self._parent

    def left(self):
        return self._left

    def right(self):
        return self._right

    def sibling(self):
        if self.is_root():
            return None
        elif self._parent._left == self:
            return self._parent._right
        elif self._parent._right == self:
            return self._parent._left
        else:
            raise ValueError("Strange node")

    def _set_element(self, element):
        self._element = element

    def _set_parent(self, parent):
        self._parent = parent

    def _set_left(self, left):
        self._left = left

    def _set_right(self, right):
        self._right = right

    def add_left(self, new_element):
        new_tree = BinaryTree(new_element, self)
        if self._left is None:
            self._left = new_tree
        else:
            new_tree._left = self._left
            self._left._parent = new_tree
            self._left = new_tree
        return new_tree

    def add_right(self, new_element):
        new_tree = BinaryTree(new_element, self)
        if self._right is None:
            self._right = new_tree
        else:
            new_tree._left = self._right
            self._right._parent = new_tree
            self._right = new_tree
        return new_tree

    def inorder(self):
        if self._left:
            for other in self._left.inorder():
                yield other
        yield self
        if self._right:
            for other in self._right.inorder():
                yield other

    def preorder(self):
        yield self
        if self._left:
            for other in self._left.preorder():
                yield other
        if self._right:
            for other in self._right.preorder():
                yield other

    def postorder(self):
        if self._left:
            for other in self._left.postorder():
                yield other
        if self._right:
            for other in self._right.postorder():
                yield other
        yield self

    def levelorder(self):
        queue = []
        queue.append(self)
        while len(queue) != 0:
            p = queue.pop(0)
            if p._left is not None:
                queue.append(p._left)
            if p._right is not None:
                queue.append(p._right)
            yield p

    def children(self):
        if self._left:
            yield self._left
        if self._right:
            yield self._right

    def depth(self):
        if self._parent is None:
            return 0
        else:
            return 1 + self._parent.depth()

    def is_internal(self):
        return self._left or self._right

    def is_external(self):
        return not self.is_internal()

    def is_root(self):
        return self._parent is None

    def height(self):
        if self.is_external():
            return 0
        else:
            return 1 + max(self._left.height(), self._right.height())

    def delete(self):
        if self._parent:
            if self._parent._left == self:
                self._parent._left = None
            elif self._parent._right == self:
                self._parent._right = None
            else:
                raise ValueError("Strange node cannot be deleted")

        self._parent = None
        for c in self.children():
            c.delete()

        self._left = self._right = self._element = None
        del self

    # Assignment begins here
    def inorder_prev(self):
        if self.is_root():
            if self.is_external() or self._left is None:
                return None
            else:
                node = self._left
                while node.is_internal():
                    node = node.right()
                return node
        elif self.is_internal():
            if self._left:
                node = self._left
                while node.is_internal():
                    if node.right():
                        node = node.right()
                    else:
                        return node
                return node
            elif self._right:
                return self._parent
            else:
                return None
        elif self.is_external() and self is self._parent.right():
            return self._parent
        elif self.is_external() and self is self._parent.left():
            node = self._parent
            while node is node.parent().left():
                node = node.parent()
                if node.is_root():
                    return node.parent()
            return node.parent()

    def inorder_next(self):
        if self.is_root():
            if self._right:
                node = self._right
                while node.is_internal():
                    if node.left():
                        node = node.left()
                    else:
                        return node
                return node
            else:
                return None
        elif self.is_internal():
            if self._right:
                node = self._right
                while node.is_internal():
                    node = node.left()
                return node
            else:
                return self._parent
        elif self.is_external() and self is self._parent.left():
            return self._parent
        elif self.is_external() and self is self._parent.right():
            node = self._parent
            while node is node.parent().right():
                node = node.parent()
                if node.is_root:
                    return node.parent()
            return node.parent()

    def preorder_prev(self):
        if self.is_root():
            return None
        elif self is self._parent.left():
            return self._parent
        elif not self._left and self.is_internal():
            return self._parent
        else:
            node = self._parent
            while not node.is_external():
                if node.right() is self and node.left():
                    node = node.left()
                else:
                    node = node.right()
            return node

    def preorder_next(self):
        if self.is_root():
            if self.is_external():
                return None
            elif not self._left and self._right:
                return self._right
            else:
                return self._left
        elif self.is_internal():
            if self._left:
                return self._left
            else:
                return self._right
        elif self._parent.left() is self:
            return self._parent.right()
        else:
            node = self
            while node is node.parent().right():
                if node.parent().is_root():
                    return None
                else:
                    node = node.parent()
            if node.parent().right() is not None:
                return node.parent().right()

    def postorder_prev(self):
        if self.is_root():
            if self._right:
                return self._right
            elif self._left:
                return self._left
            else:
                return None
        elif self is self._parent.right() and self.is_external():
            return self._parent.left()
        elif self is self._parent.left() and self.is_external():
            node = self._parent
            flag = True
            while node.is_internal():
                if node is node.parent().right():
                    flag = False
                if node.parent().is_root():
                    if node is node.parent().right():
                        return node.parent().left()
                    elif node is node.parent().left():
                        if flag is True:
                            return None
                        else:
                            return node.left()
                elif node.left() is not self and node.left().is_external():
                    return node.left()
                else:
                    node = node.parent()
            return node.left()
        else:
            if self._right:
                return self._right
            else:
                return self._left

    def postorder_next(self):
        if self.is_root():
            return None
        elif self is self._parent.left():
            node = self._parent
            while node and node.is_internal():
                if node.is_root():
                    if node.right():
                        node = node.right()
                    else:
                        return node
                elif self is node.left():
                    if node.right():
                        node = node.right()
                    else:
                        return node
                else:
                    node = node.left()
            return node
        else:
            return self._parent


# test code for BinaryTree methods
root = BinaryTree('1')
root.add_left('2')
root.add_right('3')
root.left().add_left('4')
root.left().add_right('5')
root.right().add_left('6')
root.right().add_right('7')
root.right().left().add_left('8')
root.right().left().add_right('9')
root.right().left().right().add_left('10')
root.right().left().right().add_right('11')

print(root)
print(root.left())
print(root.left().sibling())
print(root.left().left())
print(root.left().right())
print(root.right().left())
print(root.right().right())

# test code for aux methods
t = root.left()
print("Depth of {}: {}".format(t.element(), t.depth()))
print("Height of {}: {}".format(t.element(), t.height()))
print("{} is".format(t.element()), "internal." if t.is_internal() else "external.")
print("{} is".format(t.element()), "a root." if t.is_root() else "not a root.")

# test code for traversal methods
print("\nInorder Traversal")
for p in root.inorder():
    print(p.element(), end=" ")
print("\n")

print("\nPreorder Traversal")
for p in root.preorder():
    print(p.element(), end=" ")
print("\n")

print("\nPostorder Traversal")
for p in root.postorder():
    print(p.element(), end=" ")
print("\n")

print("\nLevelorder Traversal")
for p in root.levelorder():
    print(p.element(), end=" ")
    last = p
print("\n")

print("The last is ", last.element(), end='\n\n')

# Tests for an assignment
for p in root.inorder():
    prev = p.inorder_prev()
    next = p.inorder_next()
    print(prev.element() if prev else None, p.element(), next.element() if next else None, end=" / ")
print("\n")

for p in root.preorder():
    prev = p.preorder_prev()
    next = p.preorder_next()
    print(prev.element() if prev else None, p.element(), next.element() if next else None, end=" / ")
print("\n")

for p in root.postorder():
    prev = p.postorder_prev()
    next = p.postorder_next()
    print(prev.element() if prev else None, p.element(), next.element() if next else None, end=" / ")
print("\n")