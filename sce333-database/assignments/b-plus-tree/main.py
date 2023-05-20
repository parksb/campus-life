'''
1. Replace folder name "202212345" with your student ID !!
2. Also, replace this file name "bptree_202212345" with your student ID !
3. Implement operations with "B_PLUS_TREE" class.
4. Run the code "python bptree_202212345.py < test_bp.txt > result.txt" in terminal to test.
'''

import sys
import math
from typing import Optional, Self


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

    def find_idx(self, k: int):
        idx = 0
        for i in range(len(self.keys)):
            if self.keys[i] > k:
                idx = i
                break
            idx = i + 1
        return idx

    def find_position_for(self, k: int) -> tuple[Self, int]:
        idx = self.find_idx(k)
        if self.isLeaf:
            return (self, idx)
        sub = self.subTrees[idx]
        return sub.find_position_for(k)

    def find_path_to(self, k: int) -> list[Self]:
        if self.isLeaf: return [self]
        idx = self.find_idx(k)
        sub = self.subTrees[idx]
        return [self] + sub.find_path_to(k)

class B_PLUS_TREE:
    '''
    Implement below functions
    '''
    def __init__(self, order: int):
        self.order = order
        self.root: Optional[Node] = None
        pass

    def insert(self, k: int):
        def rebalance(n: Node):
            # print("----- rebalance for {} -----".format(n.keys))
            piv = math.floor(len(n.keys) / 2)
            k = n.keys.pop(piv)

            parent = n.parent
            if parent is None:
                parent = Node()
                self.root = parent

            left = Node()
            left.keys = n.keys[:piv]
            left.subTrees = n.subTrees[:piv + 1]
            for sub in n.subTrees[:piv + 1]:
                sub.parent = left
            left.parent = parent
            if not len(left.subTrees):
                left.isLeaf = True
                left.values = left.keys
            # print("keys of left: {}".format(left.keys))

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
            # print("keys of right: {}".format(right.keys))

            idx = parent.find_idx(k)
            # print("{} will be inserted to {} at idx {}".format(k, parent.keys, idx))
            parent.keys.insert(idx, k)
            # print("{} is inserted: {}".format(k, parent.keys))

            # print("current subtrees of parent is {}".format(list(map(lambda x: x.keys, parent.subTrees))))

            if len(parent.subTrees) > 0:
                parent.subTrees.pop(idx)
            parent.subTrees.insert(idx, left)
            parent.subTrees.insert(idx + 1, right)
            parent.values = []

            # print("subtrees of parent is {}".format(list(map(lambda x: x.keys, parent.subTrees))))
            if len(parent.keys) > self.order - 1:
                rebalance(parent)
            pass

        if self.root is None:
            n = Node()
            n.keys = [k]
            n.isLeaf = True
            self.root = n
        else:
            leaf, midx = self.root.find_position_for(k)
            idx = leaf.find_idx(k)
            # print("gotcha! {} will be inserted to {} at idx {}".format(k, leaf.keys, idx))
            leaf.keys.insert(idx, k)
            # print("{} is inserted {}".format(k, leaf.keys))
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
            pass

        if self.root is not None:
            print_level(self.root)
        pass

    def find_range(self, k_from: int, k_to: int):
        pass

    def find(self, k: int):
        fmt = lambda x: "[{}]".format(','.join(map(str, x)))
        if self.root is None:
            return None
        path = self.root.find_path_to(k)
        if k in path[len(path) - 1].values:
            print('-'.join(map(lambda x: fmt(x.keys), path)))
        else:
            print("NONE")
        pass


def main():
    '''
    Input: test_bp.txt
    Output: result.txt
    '''
    sys.stdin = open("test_find.txt",'r')
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
