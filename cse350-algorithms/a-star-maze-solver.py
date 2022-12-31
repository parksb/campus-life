from typing import Optional, Union
from queue import PriorityQueue

P = tuple[int, int] # Position (row, column)
M = tuple[int, int, list[list[str]]] # Maze (width, height, map)

class N: # Node
    def __init__(self, g: int, h: int, p: P, parent: Optional['N']):
        self.g = g
        self.h = h
        self.p = p
        self.parent = parent

    def iterate(self):
        '''루트 노드까지의 모든 노드를 반환한다.'''
        cursor = self
        result: list[N] = []
        while not cursor is None:
            result.append(cursor)
            cursor = cursor.parent
        return result

    def __hash__(self) -> int: return hash(self.p)

    def __eq__(self, x: Optional[Union['N', P]]) -> bool:
        if x is None: return self is None
        elif type(x) is tuple: return self.p[0] == x[0] and self.p[1] == x[1]
        elif type(x) is N: return self.p[0] == x.p[0] and self.p[1] == x.p[1]
        else: raise TypeError
    def __ne__(self, x: Optional[Union['N', P]]) -> bool:
        return not self == x

class NEval: # Evaluatable Node
    def __init__(self, x: N):
        self.n = x

    def __eq__(self, x: 'NEval') -> bool: return self.n.g + self.n.h == x.n.g + x.n.h
    def __ne__(self, x: 'NEval') -> bool: return not self == x
    def __lt__(self, x: 'NEval') -> bool: return self.n.g + self.n.h < x.n.g + x.n.h
    def __gt__(self, x: 'NEval') -> bool: return self.n.g + self.n.h > x.n.g + x.n.h
    def __le__(self, x: 'NEval') -> bool: return self < x or self == x
    def __ge__(self, x: 'NEval') -> bool: return self > x or self == x

class NTable: # Node Table
    def __init__(self, x: N):
        self.t = { hash(x): x }

    def has(self, x: Union[N, P]) -> bool:
        return hash(x) in self.t

    def get_or_set(self, x: N) -> N:
        key = hash(x)
        if key in self.t:
            return self.t[key]
        else:
            self.t[key] = x
            return x

    def update(self, x: N, h: Optional[int] = None, g: Optional[int] = None, parent: Optional[N] = None):
        key = hash(x)
        if not h is None and self.has(x): self.t[key].h = h
        if not g is None and self.has(x): self.t[key].g = g
        if not parent is None and self.has(x): self.t[key].parent = parent

class NPriorityQueue: # Node Priority Queue
    def __init__(self, x: N):
        self.q: PriorityQueue[NEval] = PriorityQueue()
        self.q.put(NEval(x))
        self.d = { hash(x): 1 }

    def get(self) -> N:
        n = self.q.get().n
        key = hash(n)
        if key in self.d:
            self.d[key] -= 1
            if self.d[key] < 1: del self.d[key]
        return n

    def put(self, x: N):
        key = hash(x)
        self.q.put(NEval(x))
        if key in self.d: self.d[key] += 1
        else: self.d[key] = 1

    def empty(self):
        return self.q.empty()

    def has(self, x: N):
        return hash(x) in self.d

def available_on(x: P, maze: M) -> list[P]:
    '''maze 상의 x 위치에서 이동 가능한 모든 위치를 반환한다.'''
    up = (x[0] - 1, x[1])
    down = (x[0] + 1, x[1])
    left = (x[0], x[1] - 1)
    right = (x[0], x[1] + 1)

    result: list[P] = []
    is_valid = lambda x: (x[0] >= 0 and x[1] >= 0) and (x[0] < maze[1] and x[1] < maze[0])
    for (r, c) in list(filter(is_valid, [up, down, left, right])):
        if maze[2][r][c] != '*': result.append((r, c))
    return result

def manhattan_distance(x: P, y: P) -> int:
    '''x 위치에서 y 위치까지의 맨해튼 거리를 반환한다'''
    return abs(x[0] - y[0]) + abs(x[1] - y[1])

def find_path(maze: M, start: P, goal: P) -> list[P]:
    '''start 위치에서 출발해 goal 위치에 도착하는 최단 경로를 반환한다.'''
    if maze[2][start[0]][start[1]] == '*' or maze[2][goal[0]][goal[1]] == '*':
        return []

    h = manhattan_distance
    root = N(0, h(start, goal), start, None)
    last = root

    nodes = NTable(root)
    candidates = NPriorityQueue(root)
    visited = set([root])

    while not candidates.empty():
        current = candidates.get()
        last = current

        if current.p == goal:
            break

        for available_position in available_on(current.p, maze):
            cost = current.g + 1
            successor = nodes.get_or_set(N(cost, h(available_position, goal), available_position, current))

            is_expensive = successor.g <= cost
            if candidates.has(successor) and is_expensive:
                continue
            elif successor in visited:
                if is_expensive:
                    continue
                visited.remove(successor)
                candidates.put(successor)
            else:
                candidates.put(successor)
                nodes.update(successor, h = h(successor.p, goal))
            nodes.update(successor, g = cost, parent = current)
        visited.add(current)

    if last.p != goal: return []
    return list(map(lambda x: x.p, last.iterate()))

def draw(maze: M, path: list[P]):
    for (r, c) in path: maze[2][r][c] = 'x'
    for x in maze[2]: print(''.join(x))
    print("\n{}".format(len(path)))

file = open('map.txt', 'r')
lines = file.readlines()
file.close()

[w, h] = map(int, lines[0].split())
maze = (w, h, list(map(lambda x: [*(x.strip())], lines[1:-1])))
[sx, sy, gx, gy] = map(int, lines[-1].split())

path = find_path(maze, (sy, sx), (gy, gx))

if len(path) > 0:
    draw(maze, path)
else:
    print("Path not found")

