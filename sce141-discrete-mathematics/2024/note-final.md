# 이산수학

::: TOGGLE ToC
[[toc]]
:::

$$
\gdef\mod{\textbf{ mod }}
\gdef\bmod{\text{mod }}
\gdef\nequiv{\not\equiv}
\gdef\sbmatrix#1{\begin{bmatrix}#1\end{bmatrix}}
\gdef\relation#1#2#3{{}_#2#1_#3}
\gdef\poleq{\preccurlyeq}
\gdef\pole{\prec}
$$

## Relations

### Equivalence Relations

- 지금까지 관계의 정의와 특성, 표현, 폐쇄까지 공부했음.
- 이제 동치관계에 대해 배워보자. 어떤 관계 내에 유사한 성질을 가진 관계.
- 동치관계(equivalence relations):
  - Reflexive & Symmetric & Transitive 특성을 만족하는 관계.
  - 두 원소 $a, b$가 동치관계에 대한 관계가 있을 때 동치(equivalent)라고 한다: $a \sim b$
  - > $m > 1$인 정수 $m$이 있을 때, $R = \{(a, b) | a \equiv b (\bmod m)\}$. $R$이 동치관계인가?
    > - RST를 모두 만족하는지 하나씩 확인해 보면 된다.
    > - R: 같은 두 수는 당연히 나머지가 같으니 성립, $a \equiv a (\bmod m)$
    > - S: 교환해도 당연히 나머지가 같으니 성립, $b \equiv a (\bmod m)$
    > - T: $a \equiv b (\bmod m)$일 때 $a \equiv c (\bmod m)$이니까 성립.
  - > 문자열 길이 함수 $l$. $l(a) = l(b)$일 때 $\relation{R}{a}{b}$인 관계 $R$이 동치관계인가?
    > - R: 같은 두 문자열의 길이는 당연히 같으니 성립, $l(a) = l(a)$
    > - S: 교환해도 길이가 같으니 성립, $l(b) = l(a)$
    > - T: $l(a) = l(b)$이고, $l(b) = l(c)$이라면 $l(a) = l(c)$이므로 성립.
  - > "나누어 떨어짐" 관계가 동치관계인가?
    > - 관계를 정의해보면: $R = \{(a, b) | (a | b) \land a, b \in \Bbb{Z}^+\}$
    > - R: $a | a$가 성립.
    > - S: $a | b$일 때 $b | a$는 성립하지 않음. antisymmetric임.
    > - T: $a | b$이고 $b | c$일 때 $a | c$이므로 성립.
- 동치류(equivalence classes):
  - 집합 $A$에 대한 관계 $R$이 동치관계일 때, $A$의 어떤 원소 $a$와 관계된 모든 $A$의 원소 집합.
  - 즉, $R = \{(a, ?), (a, ?), (a, ?), ...\}$에서 $a$와 관계있는 모든 $?$의 집합이 동치류.
  - 관계 $R$에 대한 동치류: $[a]_R$, 관계가 하나만 있으면 그냥 $[a]$로 쓰기도.
  - 앞서 $?$를 $s$라고 하면, $[a]_R = \{s | (a, s) \in R\}$
  - > $a \equiv n (\bmod 4)$일 때 동치류 $[a]_m$을 구해보면?
    > - 동치류 중 하나를 아무거나 골라서 $a$ 자리에 써줘도 됨.
    > - $[0]_4 = \{\cdots, -8, -4, 0, 4, 8, \cdots\}$, 4로 나누어 떨어지는 정수의 집합이 됨.
    > - $[1]_4 = \{\cdots, -7, -3, 1, 5, 9, \cdots\}$, 4로 나눴을 때 나머지가 1인 정수 집합.
    > - 한 동치류에 속한 원소는 다른 동치류에 속하지 않는다.
    > - $a$가 해당 동치류 $[a]$의 원소에 포함되어 있음.
- 동치분할(equivalence partitions):
  - 주어진 관계가 동치관계라면 동치류를 구할 수 있음.
  - 동치류는 전체 집합 $A$를 빈 공간없이 정확히 분할한다.
  - 전체 집합 $A$를 관계 $R$로 분할한다: $A / B$
  - 정리 1, 관계 $R$이 $A$에 대한 동치 관계일 때:
    - $\relation{R}{a}{b}$
    - $[a] = [b]$
    - $[a] \cap [b] \neq \varnothing$ (exactly cover)
  - 동치분할:
    - 전체집합 $S$의 서로소이면서 공집합이 아닌 부분집합 $A_1, A_2 \cdots A_n$이 있음.
    - 이때 모든 부분집합의 합집합 $\bigcup_{i \in l} A_i = S$가 된다.
    - 즉, $A$에 대한 관계 $R$의 모든 동치류의 합은 $A$가 됨: $\bigcup_{a \in A} [a]_R = A$
    - $[a]_R \neq [b]_R$일 때 $[a]_R \cap [b]_R = \varnothing$.
    - 이걸 도대체 언제 쓰나요? 관계에 원소가 엄청 많을 때 유사한 특성을 가진 부분집합으로 분류.
    - 정리2: 역으로 동치류가 주어졌을 때 동치관계를 생성할 수 있음.
    - > 동치관계 $R$의 동치류 $A_1 = \{1, 2, 3\}, A_2 = \{4, 5\}, A_3 = \{6\}$이 주어짐.
      > $A_1$의 순서쌍은 $(1, 1), (1, 2), \cdots, (3, 2), (3, 3)$.
      > $A_2$의 순서쌍은 $(4, 4), \cdots, (5, 5)$
      > $A_3$의 순서쌍은 $(6, 6)$
      > 따라서 $R = \{(1, 1), (1, 2), \cdots, (6, 6)\}$
    - > 집합 $A = \{a, b, c\}$에 대한 관계 $R$이 동치관계인지 판별하고, 동치관계가 아니라면 동치관계를 만족하는 최소의 순서쌍을 포함하고, 이에 대한 동치류를 구하라.
      > - $M_R = \sbmatrix{1 & 0 & 1 \\ 0 & 1 & 0 \\ 1 & 1 & 0}$
      > - 일단 딱 봤을  때 reflexive하지 않고, symmetric하지 않으니 동치관계가 아님.
      > - $(c, a), (a, c)$가 있는데 $(c, c)$가 없으니 transitive도 아님.
      > - Reflexive하게 만드려면: $(c, c)$를 추가해준다.
      > - Symmetric하게 만드려면: $(b, c)$를 추가해준다.
      > - Transitive하게 만드려면:
      >   - 워셜 알고리즘으로 풀어본다.
      >   - 주의할 점은 $W_0$가 그냥 $R$이 아닌, 반사폐쇄와 대칭폐쇄까지 추가한 관계여야.
      >   - 결과적으로 $(a, b), (b, a), (b, c), (c, c)$가 추가됨.
      > - 따라서 $R = \{(a, a), (a, b), (a, c), \cdots, (c, c)\}$
      > - 동치류도 구해보면:
      >   - $[a] = \{a, b, c\}$
      >   - $[b] = \{a, b, c\}$
      >   - $[c] = \{a, b, c\}$
      >   - 동치류가 $A$와 같음을 알 수 있음.

### Partial Orderings

- 부분적으로 순서를 결정할 수 있는 관계.
- 어떤 관계 $R$이 부분순서 관계라는 것. 앞서 동치관계는 순서를 결정할 수 없음.
- 사전식 순서:
  - 사전을 생각해보면 알파벳 순서가 있음: $(a, b), (b, c), (c, d), \cdots$
  - $(a, a)$도 포함할 수 있을까? YES. 순서가 같다는 의미. Reflexive.
  - $(a, b)$가 있으면 $(b, a)$도 있을까? NO. 그러면 모순. Antisymmetric.
  - $(a, b)$와 $(b, c)$가 있으면 $(a, c)$도 있을까? YES. Transitive.
- Partially ordered set:
  - 부분순서가 있는 집합. poset이라고 줄여부름.
  - 부분 순서 집합 $(S, R)$에서 $S$는 대상 집합, $R$은 부분순서 관계.
  - 순서쌍 표현이랑 좀 헷갈리는데 책에서는 이렇게 씀...
- 전체 순서가 있을 수도 있고, 일부만 순서가 있을 수도 있음. 그래서 partial ordering임.
- > Greater than or equal 관계가 정수 집합에 대한 부분 순서 관계인가?
  > - R: $a \geq a$ for every integer $a$.
  > - A: if $a \geq b$ and $b \geq a$, then $a = b$.
  > - T: if $a \geq b$ and $b \geq c$, then $a \geq c$.
  > - 따라서 $(\Bbb{Z}, \geq)$는 poset이다.
- > 멱집합(power set)에 부분 순서가 있는가?
  > - R: $A \sube A$.
  > - A: if $A \sube B$ and $B \sube A$, then $A = B$.
  > - T: if $A \sube B$ and $B \sube C$, then $A \sube C$.
  > - 따라서 $(P(S), \sube)$는 poset이다.
- Comparability:
  - poset $(S, \poleq)$의 원소 $a, b$를 생각해보자.
  - $a \poleq b$: $(a, b) \in R$이라는 뜻. 부등호 아님. $a$가 $b$ 앞에 나온다는 것.
  - $a \poleq b$ 또는 $b \poleq a$ 둘 중 하나만 있어도 순서 비교가 가능하다.
  - 만약 둘 다 포함이 되어 있지 않다면 비교가 불가능(incomparable).
  - > poset $(\Bbb{Z}^+, |)$가 3과 9, 5와 7에 대해 comparable한가?
    > - 3과 9를 생각해보자:
    >   - $3 | 9$는 성립. 하지만 $9 | 3$은 성립하지 않음. 따라서 $(3, 9) \not\in |$
    >   - 근데 둘 중 하나($3 | 9$)만 있어도 된다고 했으니 비교 가능하다.
    > - 5와 7을 생각해보자: $5 | 7$도 안 되고, $7 | 5$도 안 되니까 비교 불가능.
  - 부분순서 집합이니까 집합 내에 비교가 불가능한 원소가 있을 수 있음.
  - 전체순서(total order) 또는 선형순서(linear order):
    - 만약 집합 내 모든 순서쌍이 비교 가능하다면 전체순서 집합.
    - totally ordered set은 chain이라고 부른다.
    - > poset $(\Bbb{Z}^+, \leq)$가 전체 순서 집합인가? 모든 원소에 $\leq$ 비교 가능하니 YES.
- 순서화집합(well-ordered set):
  - totally ordered set이 최소원소(least element)를 갖는다면 순서화집합.
  - $(a_1, a_2) \poleq (b_1, b_2)$에 대해 $a_1 < b_1$ 또는 $a_1 = b_1$ 그리고 $a_2 \leq b_2$라면 lexicographic ordering.
- Lexicographic order:
  - 영어사전 순서 생각해보세요. 알파벳 순서로, 길이가 짧은게 먼저 나옴.
  - 임의의 두 poset $(A_1, \poleq_1$)과 $(A_2, \poleq_2)$를 생각해보자.
  - 이때 순서쌍의 첫 번째 원소를 비교하고, 그게 같다면 두 번째 원소를 비교.
  - > discreet $\poleq$ discrete, $e \poleq t$이니까.
  - > discreet $\poleq$ discreetness, 길이가 짧은게 먼저.
- Hasse diagrams:
  - 부분 순서 관계를 다이그래프로 표현하면? RAT 특성을 갖는 모습:
    ```mermaid
    graph TD
      a((a)) --> b((b))
      b --> c((c))
      c --> d((d))
      a --> a
      b --> b
      c --> c
      d --> d
      a --> c
      c --> d
      a --> d
    ```
  - 너무 복잡하다. partial order니까 당연히 RAT라고 생각할 수 있음. 다 생략해보자:
    ```
    graph TD
      d((d)) --- c((c))
      c --- b((b))
      b --- a((a))
    ```
  - 이렇게 생략한게 하세 다이어그램. 유한 poset $(S, \poleq)$의 하세 다이어그램 그리는 절차:
    1. 일단 관계에 대한 다이그래프를 그린다.
    1. 모든 정점의 루프를 모두 지운다.
    1. transitive한 경로가 있다면 직접 가는 경로를 지운다.
    1. 모든 화살표가 위로 향하도록 다시 정렬해 그린다.
    1. 모든 화살표를 지우고 방향 없는 엣지로 만든다.
  - covering relation:
    - $x \pole z \pole y$ 관계가 있음. 이때 $z$가 없으면 $x$와 $y$는 인접 정접이 됨.
    - 이때, $y$가 $x$를 덮는다(cover). 이때 $(x, y)$의 집합이 covering relation.
  - > $S = \{a, b, c\}$에 대한 멱집합 $P(S)$의 부분 순서 $\{(A, B) | A \sube B\}$를 하세 다이어그램으로 그려라.
    > - $P(S) = \{\varnothing, \{a\}, \{b\}, \{c\}, \{a, b\}, \{a, c\}, \{b, c\}, \{a, b, c\}\}$
- Maximal and Minimal elements:
  - 극대원소: 다른 어떤 원소보다도 작지 않은 원소들.
  - 극소원소: 다른 어떤 원소보다도 크지 않은 원소들.
  - 하세 다이어그램을 그리면 쉽게 찾을 수 있음. 무한 집합에서는 존재하지 않을 수도.
- Greatest and Least elements:
  - 최대원소: 다른 모든 원소보다 큰 유일한 원소.
  - 최소원소: 다른 모든 원소보다 작은 유일한 원소.
  - 극대원소가 여러 개면 최대원소가 존재하지 않음.
  - 극소원소가 여러 개면 최소원소가 존재하지 않음.
- Upper and Lower bound:
  - 상한계: 부분집합 A의 모든 원소보다 크거나 같은 원소.
  - 하한계: 부분집합 A의 모든 원소보다 작거나 같은 원소.
  - 최소상한계(Least upper bound, LUB): 상한계에서 가장 작은 유일한 원소.
  - 최대하한계(Greatest lower bound, GLB): 하한계에서 가장 작은 유일한 원소.
  - 상한계와 하한계에 자기 자신이 포함된다는 걸 잊으면 안 됩니당.
  - > e.g., $(\Bbb{Z}^+, |)$에 대해 lub는 최소공배수, glb는 최대공약수.
- Lattices:
  - poset의 모든 원소간 쌍에 lub와 glb가 존재하는 경우.
  - 임의의 두 원소를로 만들어지는 모든 쌍에 대해 lub와 glb가 존재하는지 확인해보면 된다.
- 위상정렬(topological sorting):
  - 주어진 partial order로부터 total order를 구하는 것.
  - $\relation{a}{R}{b}$일 때 $a \poleq b$이면 partial order와 total order가 양립할 수 있음.
  - 보조정리 1: 모든 유한한 nonempty poset $(S, \poleq)$은 최소 하나의 극소원소를 갖는다.
  - 비교가 불가능한 두 원소 중 아무거나 선택해도 되므로, 위상정렬의 결과가 유일하지 않을 수도 있음.

## Graphs

- 앞에서는 그래프가 관계를 표현하는 한 방법이었음.
- 방대한 네트워크를 그래프로 모델링하고 알고리즘을 만들면 컴퓨터가 계산해준다.
- 그래프 이론은 대학원에서 배울 수 있음. 우리는 기본적인 것들만 보자.
- 알고리즘을 다루지는 않을거임. 자구나 알고에서 배우렴.

### Graphs and Graph Models

- 그래프: $G = (V, E)$
  - 공집합이 아닌 정점 집합 $V$와 간선 집합 $E$로 구성.
  - 각 간선은 한 두개의 정점과 연결됨. 이때 간선과 연결된 정점을 끝점(endpoint)라고 한다.
- Infinite graph: $V$가 무한집합인 그래프. 유한집합이면 finite graph.
- Simple graph:
  - 간선이 두 개의 서로 다른 정점을 연결하고 (루프가 없어야)
  - 같은 정점 쌍을 연결하는 두 개 이상의 간선이 없는 그래프 (멀티엣지가 없어야)
- Multigraph: 멀티엣지를 가진 그래프. 멀티엣지는 허용, 루프는 없어야.
- Pseudograph: 루프와 멀티엣지를 가진 그래프.
- Undirected graph:
  - 간선에 방향이 없는 그래프. 양방향 관계라고 볼 수 있음.
  - 순서가 없으니까 간선을 $\{u, v\}$로 표현. 순서가 상관없음.
  - 근데 보통은 다 $(u, v)$로 표현한다. 대신 방향이 없다고 말해줘야.
- Directed graph or digraph:
  - 간선에 방향이 있는 그래프. 방향그래프, 유향그래프 등 다양하게 부름.
  - 간선에 방향이 있으므로 $E$를 표현할 때는 순서가 있는 순서쌍 집합으로 표현해줘야.
  - 간선 $(u, v)$는 정점 $u$에서 $v$로 향하는 간선. 순서가 중요함.
- Mixed graph or hybrid graph: 방향이 있는 간선과 없는 간선이 섞여있는 그래프.
- Simple directed graph:
  ```mermaid
  graph LR
  a((a)) --> b((b))
  b --> c((c))
  a --> c
  c --> b
  ```
  - 루프와 멀티엣지가 없으니 단순그래프임.
  - 방향이 있으니 유향그래프임.
- Directred multigraph:
  ```mermaid
  graph LR
  a((a)) --> b((b))
  b --> c((c))
  b --> c
  b --> b
  a --> c
  a --> c
  c --> c
  ```
  - 루프나 멀티엣지를 가질 수 있음.
  - 멀티그래프에는 루프가 없어야 한다며? 유향그래프에서는 루프가 허용됨.
- 그래프 종류 총정리:
  | Type                  | Edges                 | Multiple Edges Allowed? | Loops Allowed? |
  |-----------------------|-----------------------|-------------------------|----------------|
  | Simple graph          | Undirected            | No                      | No             |
  | Multigraph            | Undirected            | Yes                     | No             |
  | Pseudograph           | Undirected            | Yes                     | Yes            |
  | Simple directed graph | Directed              | No                      | No             |
  | Directed multigraph   | Directed              | Yes                     | Yes            |
  | Mixed graph           | Directed & undirected | Yes                     | Yes            |
- 그래프 모델:
  - 그래프로 모델링할 때 해볼 질문들:
    - 방향이 있어야 하는가?
    - 멀티엣지가 필요한가?
    - 루프가 필요한가?
  - 컴퓨터 네트워크 예시, 소셜 네트워크 예시.

### Graph Terminology and Special Types of Graphs

#### Undirected graph

- undirected graph 관련 기본 용어:
  - 인접(adjacent or neighbors):
    - 어떤 두 정점을 직접 잇는 간선이 존재한다면 둘은 인접정점.
    - 이때 간선 $e$는 두 정점에 부속되며(incident), 두 정점을 연결(connect)한다.
  - Neighborhood of $v$: $N(v)$
    - 정점 $v$와 인접한 정점의 집합.
    - 정점집합 $V$의 어떤 부분집합 $A$에 대해 $N(A) = \bigcup_{v \in A} N(v)$
    - 루프가 있는 경우 자기 자신도 인접정점에 포함된다.
  - 차수(degree): $\text{deg}(v)$
    - 어떤 점점의 차수는 그 정점과 연결된 엣지의 개수.
    - 루프를 가진 정점의 차수는 2. 나가는 거 하나, 들어오는 거 하나.
  - Isolated vertex: 그래프에서 어떠한 정점과도 연결되지 않은 정점.
  - Pendant vertex: 그래프에서 단 하나의 정점과 연결된 정점.
- 정리 1 (handshaking theorem):
  - 어떤 undirected graph $G = (V, E)$가 $m$개의 간선을 가지고 있는경우.
  - 모든 차수를 더하면 간선의 2배가 된다: $2m = \sum_{v \in V} \text{deg}(v)$
  - 즉, 차수의 합이 언제나 짝수임을 보장할 수 있다.
  - > 차수가 6인 정점이 10개 있는 그래프에서 간선의 개수는? 차수의 합이 60, 따라서 간선은 30개.
  - > 정점이 5개 있는 그래프에서 각 정점의 차수가 3이 될 수 있나?
    > - 차수의 합이 15면 간선의 개수 $m$은 7.5가 되어야 함.
    > - 정수로 떨어지지 않으므로 불가능하다.
- 정리 2: 홀수 차수를 가진 정점의 개수는 항상 짝수이다.
- 여기서 차수에 대한 정리는 다 undirected graph 얘기임.

#### Directed graph

- 유향그래프는 순서쌍으로 구성된다. $(u, v)$는 $u$에서 출발해서 $v$에 도착하는 간선.
- 시점(initial vertex): 간선이 출발하는 정점. $(u, v)$에서 $u$.
- 종점(terminal vertex): 간선이 도착하는 정점. $(u, v)$에서 $v$.
- 유향그래프의 차수에 대해 생각해보자:
  - 진입차수(in-degree): 들어오는 간선 개수, $\text{deg}^-(v)$
  - 진출차수(out-degree): 나가는 간선 개수, $\text{deg}^+(v)$
  - isolated 정점의 진입/진출 차수는 둘 다 0.
- 정리 3:
  - 유향그래프 $G = (V, E)$에서 간선의 개수는 진입/진출차수의 합과 같음.
  - $|E| = \sum_{v \in V} \text{deg}^-(v) = \sum_{v \in V} \text{deg}^+(v)$
  - 나가는 간선이 있으면 들어가는 간선도 무조건 있으니까.

#### Simple graph

- 완전그래프(complete graph), $K_n$:
  - 가능한 모든 간선을 갖는 simple graph.
  - $n$개의 정점을 가진 완전그래프를 $K_n$이라고 한다.
  - 여기에 k_1부터 k_6까지 그래프 사진.
  - 완전그래프의 간선 개수: $|V| = n$일 때, $|E| = {}_nC_2 = {2(n - 1) \over 2}
- 사이클(cycle), $C_n$:
  ```
  graph LR
    a((a)) --- b((b))
    b --- c((c))
    c --- d((d))
    d --- e((e))
    e --- a
  ```
  - $n \geq 3$의 정점을 갖는 그래프에서 모든 정점을 한 번씩 거쳐 시점으로 돌아오는 그래프.
  - $|V| = n, |E| = n$
- Wheel, $W_n$:
  - 사이클에 정점 하나를 추가한 심플 그래프.
  - $|V| = n + 1, |E| = 2n$, 여기서 $n$은 사이클의 $n$.
- Cube, $Q_n$:
  - n-dimensional hypercube 또는 n-cube이라고도 함.
  - $Q_n$의 정점 개수는 $2^n$개. 이때 $n$은 비트스트링의 길이.
  - 각 정점이 유니크한 비트스트링을 의미한다.
  - 자신의 비트스트링에서 딱 한 비트를 변경한 정점과 간선으로 연결된다.
  - 가령 $000$의 인접정점은 $100, 010, 001$이 된다. $011, 111$ 같은 건 안 되겠지.
  - $n$개 비트를 표현하려면 $2^n$개의 정점이 필요할 것임: $|V| = 2^n$
  - 비트스트링이 어떤 집합의 원소의 유무를 표현하는 식으로 사용할 수 있음.
- 이분그래프(bipartite graph):
  - $V$의 두 부분집합 $V_1$과 $V_2$의 정점이 서로 연결된 심플그래프.
  - 단, 같은 집합 내에서는 서로 연결되면 안 된다.
  - 정점 집합을 공통부분이 없는 두 부분 집합으로 나눈다고 생각하면 됨.
  - 사이클 $C_n$에서 $n$이 짝수일 때 이분그래프가 된다.
- 완전 이분그래프(complete bipartite graph), $K_{m,n}$:
  - 정점의 두 부분집합에 대해 $V = V_1 \cup V_2$이고, $V_1 \cap V_2 = \varnothing$.
  - 이때 $V_1$의 모든 정점과 $V_2$의 모든 정점이 서로 연결된 이분그래프.
- Topology
  - 컴퓨터 네트워크를 생각해보자. 네트워크의 요소들을 연결하는 형태를 토폴로지라고 한다.
  - Star topology: 모든 노드들이 중앙의 한 노드에만 연결된 형태. 완전 이분그래프.
  - Ring topology: 한 노드가 양쪽의 두 노드에 연결된 형태. 사이클.
  - $W_n$ based topology: star와 ring 토폴로지를 결합한 형태. wheel.
  - Mesh topoogy: 병렬처리를 위한 모델. n-dimensional hypercube.

### New graph from old

- 기존 그래프를 수정해서 새로운 그래프를 만드는 방법에 대해 살펴보자.
- 부분그래프(subgraph):
  - 어떤 그래프 $G = (V, E)$에 대해 $W \sub V$, $F \sub E$인 그래프 $H = (W, F)$.
  - 진부분그래프(proper subgraph):
    - $G$와 동일한 경우는 제외한 $H$, $G \not \eq H$
    - 이때 $W, F$도 각각 $V, E$에 대해 진부분집합임.
  - 당연히 한 그래프에 대해 다양한 진부분그래프가 만들어질 수 있음.

## Notices

- 중간고사 문제 풀 때 이상한 거 없었어요? 문제 6번 교집합이 15라고 되어 있는데 오타예요. 교집합이 될 수가 없지. 6번은 무조건 1점 부여할게요.
- 중간고사 질문 있으면 메일보내셈. 평균이랑 중간값도 공개해줄거임.
- 보강은 동영상 올려줄거니까 보세용. 출석체크는 안 할거임.
