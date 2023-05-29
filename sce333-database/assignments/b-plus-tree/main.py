'''
1. Replace folder name "202212345" with your student ID !!
2. Also, replace this file name "bptree_202212345" with your student ID !
3. Implement operations with "B_PLUS_TREE" class.
4. Run the code "python bptree_202212345.py < test_bp.txt > result.txt" in terminal to test.
'''

import sys
import math
from typing import Optional

Kidx = int # index for keys
STidx = int # index for subTrees

class Node:
    def __init__(self):
        # each node can have |order - 1| keys
        self.keys: list[int] = []

        # |order| / 2 <= # of subTree pointers <= |order|
        self.subTrees: list[Node] = []

        self.parent: Optional[Node] = None
        self.isLeaf = False

        # leaf node has next node pointer
        self.nextNode: Optional[Node] = None
        self.values: list[int] = []

    def find_stidx(self, k: int) -> STidx:
        idx = 0
        for i in range(len(self.keys)):
            if self.keys[i] > k:
                idx = i
                break
            idx = i + 1
        return idx

    def find_kidx_eq(self, k: int) -> Optional[Kidx]:
        for i in range(len(self.keys)):
            if self.keys[i] == k:
                return i
        return None

    def to_kidx(self, idx: STidx) -> Kidx:
        l = len(self.keys)
        if idx > l - 1: return l - 1
        return idx


class B_PLUS_TREE:
    '''
    Implement below functions
    '''
    def __init__(self, order: int):
        self.order = order
        self.root: Optional[Node] = None
        self.min_st = math.ceil((order - 1) / 2)

    def _find_leaf_for(self, n: Node, k: int) -> tuple[Node, STidx]:
        idx = n.find_stidx(k)
        if n.isLeaf:
            return (n, idx)
        sub = n.subTrees[idx]
        return self._find_leaf_for(sub, k)

    def _find_node_eq(self, n: Node, k: int) -> tuple[Node, Kidx]:
        kidx = n.find_kidx_eq(k)
        if kidx is not None:
            return (n, kidx)
        stidx = n.find_stidx(k)
        sub = n.subTrees[stidx]
        return self._find_node_eq(sub, k)

    def _find_path_to(self, n: Node, k: int) -> list[Node]:
        if n.isLeaf: return [n]
        idx = n.find_stidx(k)
        sub = n.subTrees[idx]
        return [n] + self._find_path_to(sub, k)

    def insert(self, k: int):
        def rebalance(n: Node):
            piv: Kidx = math.floor(len(n.keys) / 2)
            k = n.keys.pop(piv)

            parent = n.parent
            if parent is None:
                parent = Node()
                self.root = parent

            # right
            right = Node()
            right.keys = n.keys[piv:]
            if n.isLeaf:
                right.keys = [k] + right.keys
            right.subTrees = n.subTrees[piv + 1:]
            for sub in n.subTrees[piv + 1:]:
                sub.parent = right
            right.parent = parent
            if not len(right.subTrees):
                right.isLeaf = True
                right.values = right.keys
            if right.isLeaf: right.nextNode = n.nextNode
            else: right.nextNode = None

            # left
            n.keys = n.keys[:piv]
            n.subTrees = n.subTrees[:piv + 1]
            for sub in n.subTrees[:piv + 1]:
                sub.parent = n
            n.parent = parent
            if not len(n.subTrees):
                n.isLeaf = True
                n.values = n.keys
            if n.isLeaf: n.nextNode = right
            else: n.nextNode = None

            idx = parent.find_stidx(k)
            parent.keys.insert(idx, k)
            if len(parent.subTrees) > 0:
                parent.subTrees.pop(idx)
            parent.subTrees.insert(idx, n)
            parent.subTrees.insert(idx + 1, right)
            parent.values = []

            if len(parent.keys) > self.order - 1:
                rebalance(parent)

        if self.root is None:
            n = Node()
            n.keys = [k]
            n.isLeaf = True
            self.root = n
        else:
            leaf, midx = self._find_leaf_for(self.root, k)
            idx = leaf.find_stidx(k)
            leaf.keys.insert(idx, k)
            if len(leaf.keys) > self.order - 1:
                rebalance(leaf)
            elif midx != 0 and idx == 0 and leaf.parent is not None:
                leaf.parent.keys[midx] = k

    def delete(self, k: int):
        def find_left_sibling(n: Node, k: int):
            if n.parent is None: return None
            idx = n.parent.find_stidx(k)
            if idx == 0: return None
            return n.parent.subTrees[idx - 1]

        def find_right_sibling(n: Node, k: int):
            if n.parent is None: return None
            idx = n.parent.find_stidx(k)
            if idx + 1 >= len(n.parent.subTrees): return None
            return n.parent.subTrees[idx + 1]

        def borrow_from_left(n: Node, left: Node):
            left_max = left.keys.pop()
            n.keys.insert(0, left_max)
            if n.parent is not None:
                kidx = n.parent.find_kidx_eq(left_max)
                if kidx is None: return left_max
                n.parent.keys[kidx] = left_max
            return left_max

        def borrow_from_right(n: Node, right: Node):
            right_min = right.keys.pop(0)
            n.keys.append(right_min)
            if n.parent is not None:
                kidx_to_replace = n.parent.find_kidx_eq(right_min)
                if kidx_to_replace is None: return right_min
                n.parent.keys[kidx_to_replace] = right.keys[0]
            return right_min

        def merge_with_left(n: Node, left: Node, right: Optional[Node]):
            left.keys.extend(n.keys)
            if left.isLeaf:
                left.nextNode = right
            else:
                left.subTrees.extend(n.subTrees)
                for st in n.subTrees: st.parent = left
            merge_with(n, left)

        def merge_with_right(n: Node, right: Node):
            right.keys = n.keys + right.keys
            if not n.isLeaf:
                right.subTrees = n.subTrees + right.subTrees
                for st in n.subTrees: st.parent = right
            merge_with(n, right)

        def merge_with(n: Node, into: Node):
            if into.parent is not None:
                lstidx = into.parent.find_stidx(n.keys[0] if len(n.keys) > 0 else k)
                into.parent.subTrees.pop(lstidx)
                if lstidx > 0: lstidx = lstidx - 1

                from_parent = into.parent.keys.pop(lstidx)
                into.parent.subTrees[lstidx] = into
                if from_parent != k and from_parent not in into.keys:
                    pstidx = into.find_stidx(from_parent)
                    into.keys.insert(pstidx, from_parent)

                if len(into.parent.keys) < self.min_st:
                    new_left = find_left_sibling(into.parent, from_parent)
                    new_right = find_right_sibling(into.parent, from_parent)
                    if new_left is not None:
                        merge_with_left(into.parent, new_left, new_right)
                    elif new_right is not None:
                        merge_with_right(into.parent, new_right)
                    else:
                        self.root = into
                        into.parent = None

        if self.root is None: return
        n, _ = self._find_leaf_for(self.root, k)
        kidx = n.find_kidx_eq(k)
        if kidx is None: return

        internal, _ = self._find_node_eq(self.root, k)
        internal_kidx = internal.find_kidx_eq(k)
        if internal_kidx is None: return

        n.keys.pop(kidx)

        if len(n.keys) < self.min_st:
            left_sibling = find_left_sibling(n, k)
            right_sibling = find_right_sibling(n, k)

            if left_sibling is not None and len(left_sibling.keys) > self.min_st:
                left_max = borrow_from_left(n, left_sibling)
                if not internal.isLeaf:
                    internal.keys[internal_kidx] = left_max
            elif right_sibling is not None and len(right_sibling.keys) > self.min_st:
                borrow_from_right(n, right_sibling)
                if not internal.isLeaf:
                    internal.keys[internal_kidx] = n.keys[0]
            else:
                if left_sibling is not None:
                    if not internal.isLeaf:
                        internal.keys[internal_kidx] = left_sibling.keys[0]
                    merge_with_left(n, left_sibling, right_sibling)
                elif right_sibling is not None:
                    if not internal.isLeaf:
                        internal.keys[internal_kidx] = n.keys[0] if len(n.keys) > 0 else right_sibling.keys[0]
                    merge_with_right(n, right_sibling)
        else:
            if n.parent is not None:
                kidx_to_replace = n.parent.find_kidx_eq(k)
                if kidx_to_replace is None: return
                n.parent.keys[kidx_to_replace] = n.keys[0]

    def print_root(self):
        l = "["
        if self.root is not None:
            for k in self.root.keys:
                l += "{},".format(k)
        l = l[:-1] + "]"
        print(l)

    def print_tree(self):
        def print_level(n: Node):
            fmt = lambda x: "[{}]".format(','.join(map(str, x)))
            subs = []
            for sub in n.subTrees:
                subs.append(fmt(sub.keys))
            ks = fmt(n.keys)
            if len(subs):
                print("{}-{}".format(ks, ','.join(subs)))
            elif n is self.root:
                print(ks)
            for sub in n.subTrees:
                print_level(sub)

        if self.root is not None:
            print_level(self.root)

    def find_range(self, k_from: int, k_to: int):
        def find_range_in(n: Node, k_from: int, k_to: int):
            ret: list[int] = []
            for k in n.keys:
                if k_from <= k and k <= k_to:
                    ret.append(k)
                elif k > k_to:
                    return (ret, None)
            return (ret, n.nextNode)

        if self.root is not None:
            found, _ = self._find_leaf_for(self.root, k_from)
            ks, cur = [], found
            while cur is not None:
                res, cur = find_range_in(cur, k_from, k_to)
                ks.extend(res)
            print(','.join(map(str, ks)))

    def find(self, k: int):
        fmt = lambda x: "[{}]".format(','.join(map(str, x)))
        if self.root is None:
            return None
        path = self._find_path_to(self.root, k)
        if k in path[len(path) - 1].values:
            print('-'.join(map(lambda x: fmt(x.keys), path)))
        else:
            print("NONE")


def main():
    '''
    Input: test_bp.txt
    Output: result.txt
    '''
    # sys.stdin = open("test_insert_3.txt",'r')
    # sys.stdout = open("result.txt","w")
    myTree = None

    while (True):
        comm = sys.stdin.readline()
        comm = comm.replace("\n", "")
        params = comm.split()
        if len(params) < 1:
            continue

        print(comm)

        if params[0] == "INIT":
            order = int(params[1])
            myTree = B_PLUS_TREE(order)

        elif params[0] == "EXIT":
            return

        elif params[0] == "INSERT":
            k = int(params[1])
            myTree.insert(k)

        elif params[0] == "DELETE":
            k = int(params[1])
            myTree.delete(k)

        elif params[0] == "ROOT":
            myTree.print_root()

        elif params[0] == "PRINT":
            myTree.print_tree()

        elif params[0] == "FIND":
            k = int(params[1])
            myTree.find(k)

        elif params[0] == "RANGE":
            k_from = int(params[1])
            k_to = int(params[2])
            myTree.find_range(k_from, k_to)

        elif params[0] == "SEP":
            print("-------------------------")

if __name__ == "__main__":
    main()
