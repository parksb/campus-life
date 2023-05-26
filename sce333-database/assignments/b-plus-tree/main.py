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
        self.min_order = math.floor((order - 1) / 2)

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
            # FIXME: check correct condition for updating a parent.
            elif midx != 0 and idx == 0 and leaf.parent is not None:
                leaf.parent.keys[midx] = k

    def delete(self, k: int):
        def find_prev_node(n: Node):
            if n.parent is None: return None
            idx = n.parent.find_stidx(min(n.keys))
            if idx == 0: return None
            return n.parent.subTrees[idx - 1]

        def steal_from_left(n: Node, m: Node, left: Node, kidx: Kidx):
            left_last = left.keys.pop()
            n.keys = [left_last]
            m.keys[kidx] = left_last
            if n.parent is not None and len(left.keys) > 0:
                kidx_to_replace = n.parent.find_kidx_eq(left_last)
                if kidx_to_replace is None: return
                n.parent.keys[kidx_to_replace] = left_last

        def steal_from_right(n: Node, m: Node, right: Node, kidx: Kidx):
            right_first = right.keys.pop(0)
            n.keys = [right_first]
            m.keys[kidx] = right_first
            if n.parent is not None and len(right.keys) > 0:
                kidx_to_replace = n.parent.find_kidx_eq(right_first)
                if kidx_to_replace is None: return
                n.parent.keys[kidx_to_replace] = right.keys[0]

        if self.root is None: return
        n, stidx = self._find_leaf_for(self.root, k)
        kidx = n.find_kidx_eq(k)

        if kidx is None: return
        if self.root == n:
            n.keys.pop(kidx)
            if stidx < len(n.subTrees):
                n.subTrees.pop(stidx)
            return

        if kidx > 0:
            n.keys.pop(kidx)
        else:
            if len(n.keys) > self.min_order:
                n.keys.pop(kidx)
                if n.parent is not None:
                    kidx_to_replace = n.parent.find_kidx_eq(k)
                    if kidx_to_replace is None: return
                    n.parent.keys[kidx_to_replace] = n.keys[0]
            else:
                internal, internal_stidx = self._find_node_eq(self.root, k)
                internal_kidx = internal.find_kidx_eq(k)
                if internal_kidx is None: return

                left = find_prev_node(n)
                right = n.nextNode

                if left is not None and len(left.keys) > self.min_order:
                    steal_from_left(n, internal, left, internal_kidx)
                elif right is not None and len(right.keys) > self.min_order:
                    steal_from_right(n, internal, right, internal_kidx)
                else:
                    if n.parent is not None and len(n.parent.keys) > self.min_order:
                        n.keys.pop(kidx)
                        kidx_to_replace = n.parent.find_kidx_eq(k)
                        if kidx_to_replace is None: return
                        n.parent.keys.pop(kidx_to_replace)
                    else:
                        pass

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
