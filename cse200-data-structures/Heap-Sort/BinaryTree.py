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
