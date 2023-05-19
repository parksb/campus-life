'''
1. Replace folder name "202212345" with your student ID !!
2. Also, replace this file name "bptree_202212345" with your student ID !
3. Implement operations with "B_PLUS_TREE" class.
4. Run the code "python bptree_202212345.py < test_bp.txt > result.txt" in terminal to test.
'''

import sys
import math
from typing import Optional


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

class B_PLUS_TREE:
    '''
    Implement below functions
    '''
    def __init__(self, order: int):
        self.order = order
        self.root: Optional[Node] = None
        pass

    def insert(self, k: int):
        def find_idx(n: Node, k: int):
            idx = 0
            for i in range(len(n.keys)):
                if n.keys[i] == k or n.keys[i] > k:
                    idx = i
                    break
                else:
                    idx = i + 1
            return idx

        def find_position(n: Node, k: int) -> tuple[Node, int]:
            idx = find_idx(n, k)
            if n.isLeaf:
                return (n, idx)
            sub = n.subTrees[idx]
            return find_position(sub, k)

        def rebalance(n: Node):
            piv = math.floor(len(n.keys) / 2)
            k = n.keys.pop(piv)

            parent = n.parent
            if parent is None:
                parent = Node()
                self.root = parent

            idx = find_idx(parent, k)
            parent.keys.insert(idx, k)

            left = Node()
            left.keys = n.keys[:piv]
            left.subTrees = n.subTrees[:piv]
            if not len(left.subTrees):
                left.isLeaf = True
                left.values = n.values[:piv]

            right = Node()
            right.keys = n.keys[piv:]
            right.subTrees = n.subTrees[piv:]
            if not len(right.subTrees):
                right.isLeaf = True
                right.values = n.values[piv:]

            parent.subTrees.insert(idx, left)
            parent.subTrees.insert(idx + 1, right)

            if len(parent.keys) > self.order - 1:
                rebalance(parent)
            pass

        if self.root is None:
            n = Node()
            n.keys = [k]
            n.values = [k]
            n.isLeaf = True
            self.root = n
        else:
            leaf, midx = find_position(self.root, k)
            idx = find_idx(leaf, k)
            leaf.keys.insert(idx, k)
            if len(leaf.keys) > self.order - 1:
                rebalance(leaf)
            elif idx == 0 and leaf.parent is not None:
                leaf.parent.keys[midx] = k
        pass

    def delete(self, k: int):
        pass

    def print_root(self):
        l = "["
        if self.root is not None:
            for k in self.root.keys:
                l += "{},".format(k)
        l = l[:-1] + "]"
        print(l)
        pass

    def print_tree(self):
        def print_level(n: Node):
            fmt = lambda x: "[{}]".format(','.join(x))
            subs = []
            for sub in n.subTrees:
                subs.append(fmt(map(str, sub.keys)))
                print_level(sub)

            ks = fmt(map(str, n.keys))
            if len(subs):
                print("{}-{}".format(ks, ','.join(subs)))
            elif n is self.root:
                print(ks)
            pass

        if self.root is not None:
            print_level(self.root)
        pass

    def find_range(self, k_from: int, k_to: int):
        pass

    def find(self, k: int):
        pass


def main():
    '''
    Input: test_bp.txt
    Output: result.txt
    '''
    sys.stdin = open("test_insert.txt",'r')
    sys.stdout = open("result.txt","w")
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
