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
                right.values = right.keys.copy()
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
                n.values = n.keys.copy()
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
            leaf.values.insert(idx, k)
            if len(leaf.keys) > self.order - 1:
                rebalance(leaf)
            elif midx != 0 and idx == 0 and leaf.parent is not None:
                leaf.parent.keys[midx] = k

    def delete(self, k: int):
        def find_left(n: Node, k: int, u: bool = True) -> Optional[Node]:
            if u:
                if n.parent is None: return None
                left_sibling = find_left_sibling(n, n.keys[0] if len(n.keys) > 0 else 0)
                if left_sibling is None:
                    return find_left(n.parent, n.parent.keys[0] if len(n.parent.keys) > 0 else 0)
                return find_left(left_sibling, left_sibling.keys[-1], False)
            if n.isLeaf: return n
            lstidx = n.find_stidx(k)
            right_child = n.subTrees[lstidx + 1 if lstidx + 1 < len(n.subTrees) else -1]
            return find_left(right_child, right_child.keys[-1], False)

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
            # print("borrow from left", left.keys, "to", n.keys)
            left_max = left.keys.pop()
            if left.isLeaf and len(left.values) > 0: left.values.pop()

            n.keys.insert(0, left_max)
            if n.isLeaf: n.values.insert(0, left_max)
            else: n.subTrees.insert(0, left.subTrees.pop())
            # print("now, left is", left.keys, "and n is now", n.keys)

            if n.parent is not None:
                if n.isLeaf:
                    # print("it's leaf, so it will update their parent:", n.parent.keys)
                    pkidx = find_kidx_in_parent_of(n)
                    # print("who's my parent?", pkidx, "in", n.parent.keys, "right?")
                    if pkidx is not None:
                        n.parent.keys[pkidx] = n.keys[0]
                    # print("now, parent is", n.parent.keys)
                else:
                    # print("it's internal, what should i do?", n.keys, n.parent.keys)
                    # 인터널 노드에서 형제 노드 값을 빌린 경우에는
                    # 부모를 어떻게 업데이트해야 하는지?
                    if len(n.keys) > 0 and len(n.parent.keys) > 0 and n.keys[-1] > n.parent.keys[-1]:
                        n.keys[-1], n.parent.keys[-1] = n.parent.keys[-1], n.keys[-1]

            return left_max

        def borrow_from_right(n: Node, right: Node):
            # print("borrow from right", right.keys, "to", n.keys)
            right_min = right.keys.pop(0)
            if right.isLeaf and len(right.values) > 0: right.values.pop(0)

            n.keys.append(right_min)
            if n.isLeaf: n.values.append(right_min)
            else: n.subTrees.append(right.subTrees.pop(0))
            # print("now, right is", right.keys, "and n is now", n.keys)

            if n.parent is not None:
                if n.isLeaf:
                    # print("it's leaf, so it will update their parent:", n.parent.keys)
                    pkidx = find_kidx_in_parent_of(right)
                    # print("who's my parent?", pkidx, "in", n.parent.keys, "right?")
                    if pkidx is not None: n.parent.keys[pkidx] = right.keys[0]
                    # print("now, parent is", n.parent.keys)
                else:
                    # 인터널 노드에서 형제 노드 값을 빌린 경우에는
                    # 부모를 어떻게 업데이트해야 하는지?
                    # print("it's internal, what should i do?")
                    if len(n.keys) > 0 and len(n.parent.keys) > 0 and n.keys[-1] > n.parent.keys[-1]:
                        n.keys[-1], n.parent.keys[-1] = n.parent.keys[-1], n.keys[-1]

            return right_min

        def merge_with_left(n: Node, left: Node):
            # print("merge with left, left + n =", left.keys, "+", n.keys)
            n.keys = left.keys + n.keys
            if n.isLeaf:
                n.values = left.values + n.values
            else:
                n.subTrees = left.subTrees + n.subTrees
                for st in left.subTrees: st.parent = n
            # print("now, n is:", n.keys)
            merge_with_parent(n, left)

        def merge_with_right(n: Node, right: Node):
            # print("merge with right, n + right =", n.keys, "+", right.keys)
            n.keys.extend(right.keys)
            if n.isLeaf:
                n.values.extend(right.values)
            else:
                n.subTrees.extend(right.subTrees)
                for st in right.subTrees: st.parent = n
            # print("now, n is:", n.keys)
            merge_with_parent(n, right)

        def merge_with_parent(into: Node, t: Node):
            def remove_from(a: Node, b: Node):
                for i in range(len(a.subTrees)):
                    if a.subTrees[i] is b:
                        a.subTrees.pop(i)
                        return a.keys.pop(i - 1 if i > 0 else 0)
                return None

            if into.parent is not None:
                # print("target", t.keys, "should be removed from", into.parent.keys, "and it's subtrees are", list(map(lambda x: x.keys, into.parent.subTrees)))
                from_parent = remove_from(into.parent, t)
                # print("so, parent is", into.parent.keys, "and it's subtrees are", list(map(lambda x: x.keys, into.parent.subTrees)))

                # print("now, let's merge with parent:", into.parent.keys, "into", into.keys)
                if from_parent is not None and from_parent not in into.keys:
                    if into.isLeaf and from_parent == k:
                        pass
                    else:
                        pstidx = into.find_stidx(from_parent)
                        into.keys.insert(pstidx, from_parent)
                        if into.isLeaf: into.values.insert(pstidx, from_parent)

                # print("now, it's", into.keys, "and parent is", into.parent.keys)
                if self.root == into.parent and not len(into.parent.keys):
                    self.root = into
                    into.parent = None

        def delete_by_condition(n: Node, left: Optional[Node], right: Optional[Node]):
            if left is not None and len(left.keys) > self.min_st:
                borrow_from_left(n, left)
            elif right is not None and len(right.keys) > self.min_st:
                borrow_from_right(n, right)
            elif left is not None or right is not None:
                if left is not None:
                    merge_with_left(n, left)
                    foundl = find_left(left, left.keys[0])
                    if foundl is not None: foundl.nextNode = n
                elif right is not None:
                    merge_with_right(n, right)
                    if n.isLeaf: n.nextNode = right.nextNode
                if n.parent is not None and len(n.parent.keys) < self.min_st:
                    parent_left = find_left_sibling(n.parent, n.keys[0])
                    parent_right = find_right_sibling(n.parent, n.keys[0])
                    delete_by_condition(n.parent, parent_left, parent_right)

        def find_internal_eq(n: Node, k: int) -> Optional[Node]:
            if n.isLeaf: return None
            ekidx = n.find_kidx_eq(k)
            if ekidx is not None: return n
            sub = n.subTrees[n.find_stidx(k)]
            return find_internal_eq(sub, k)

        def find_kidx_in_parent_of(n: Node):
            if n.parent is not None:
                for i in range(len(n.parent.subTrees)):
                    if n.parent.subTrees[i] is n:
                        if i == 0: return 0
                        else: return i - 1
            return None

        if self.root is None: return
        n, _ = self._find_leaf_for(self.root, k)
        kidx = n.find_kidx_eq(k)
        if kidx is None: return

        n.keys.pop(kidx)
        if n.isLeaf and len(n.values) > 0: n.values.pop()

        if n.parent is not None:
            # print("you have a parent")
            if len(n.keys) < self.min_st:
                # print("somebody help me")
                left = find_left_sibling(n, k)
                right = find_right_sibling(n, k)
                delete_by_condition(n, left, right)
            elif kidx == 0:
                # print("but you don't need to nothing", kidx)
                if n.keys[0] not in n.parent.keys:
                    pkidx = find_kidx_in_parent_of(n)
                    if pkidx is not None and pkidx > 0:
                        n.parent.keys[pkidx] = n.keys[0]

        internal = find_internal_eq(self.root, k)
        internal_kidx = internal.find_kidx_eq(k) if internal is not None else None
        if internal is not None and internal_kidx is not None and kidx is not None:
            internal.keys[internal_kidx] = n.keys[kidx]

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
        if k in path[-1].keys:
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
