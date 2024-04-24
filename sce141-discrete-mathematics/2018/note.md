# 이산수학

## Ch.1. Fundamental

### Regular Expression

- 어떤 집합 A의 원소들로 만들 수 있는 모든 sequence를 표현하는 식.
- `λ` : Empty string
- `∧` : AND
- `∨` : OR
- `*` : Loop

## 3. Counting

### Pigeonhole principle

- "비둘기 10마리가 비둘기집 5개에 모두 무작위로 들어갔다"가 항상 참이려면 적어도 한 둥지에는 두마리 이상의 비둘기가 들어가야 한다.
- "어떤 집단에 같은 달에 태어난 사람이 8명이 있으려면 최소 몇 명이 필요한가?"가 참이려면 85명이 있어야 한다.
- 모든 자리에 골고루 분포되는 경우를 생각하면 된다. 위 생일 예시는 11개 비둘기 집에 7명씩, 나머지 하나에는 8명이 들어가기 때문에 85명이다.
- n은 비둘기, m은 비둘기 집일 때, 최소 비둘기는 `(n - 1) / m + 1`

### Recurrence Relations

- Backtracking: n이 주어지면 A(n)을 구할 수 있는 식을 만드는 것.
- Linear homogeneous relation of degree k: 항에 상수를 곱해 더하는 것을 linear, 항의 차수가 모두 동일한 것을 homogeneouse라고 함. `A(n) = R(1)A(n - 1) + R(2)A(n - 2) + ... + R(k)A(n - k)` 와 같은 형식. `us^n + vs^n`
- `A(n) = 7A(n-1) - 10A(n-2)`와 같은 recurrence relation이 주어지는 경우:
    1. characteristic equation을 구한다:  `x^(2) - 7x + 10 = 0`
    2. `x`에 대해 풀면: `(x - 2)(x - 5) = 0`
    3. `A(n)`에 대한 식을 세운다: `A(n) = A2^(n) + B5^(n)`
- `A(n) = 6A(n-1) - 9A(n-2)`와 같은 같은 recurrence relation이 주어지는 경우:
    1. characteristic equation을 구한다: `x^(2) - 6x + 9 = 0`
    2. `x`에 대해 풀면: `(x - 3)^(2) = 0`
    3. `A(n)`에 대한 식을 세운다: `A(n) = A3^(n) + Bn3^(n)`

## Ch.4. Relations and Partitions

### Properties of Relations

- Reflexive: 자기 자신을 가리키는 관계가 있음. `Δ`
- Irreflexive: 자기 자신을 가리키는 관계가 없음.
- Symmetric: 자신이 가리키는 요소가 자신을 가리킴. `R^(-1)`
- Asymmetric: 자신이 가리키는 요소가 자신을 가리키지 않음.
- Antisymmetric: 자기 자신을 가리키는 건 제외하고, 자신이 가리키는 요소가 자신을 가리지지 않음.
- Transitive: 연결된 경로가 있는 요소와 직접 연결 관계가 있음. `R^(∞)`

### Equivalence Relation

- reflexive, symmetric, transitive를 만족하는 관계.
- Equivalence relation `P = A / R`

### Closure

- 관계 R과 원하는 성질을 만족하기 위해 R에 최소한으로 추가되어야 하는 관계를 포함한 관계.
- Reflexive closure of `R = R ∪ Δ`
- Symmetric closure of `R = R ∪ R^(-1)`
- Transitive closure of `R = R^(∞) = R ∪ R^(2) ∪ ... ∪ R^(n)`
    - Warshall's Algorithm: 행렬 곱셈을 계속하지 않고 transitive closure를 구하는 알고리즘. k번째 행, 열을 보고 k열에 있는 1의 수평, k행에 있는 1의 수직을 보고 겹친 부분에 1을 추가해 `W(k+1)` 행렬을 얻는다.  `W(n)` 행렬이 `R^(∞)`가 된다.

## Ch.6. Order Relations and Structures

### Poset

- 부분적으로 순서가 정해진 관계. reflexive, antisymmetric, transitive를 만족해야 함.
- Hasse diagram으로 표현.
- Topological sorting: 기존 순서를 유지하며 요소의 선서를 일렬로 정렬. 순서가 정해지지 않은 요소의 경우, 예를 들어 a, b, c, d에서 c와 b의 순서가 정해지지 않았다면, a, b, c, d로 해도 되고, a, c, b, d로 해도 되고, a, c, d, b로 해도 된다. b가 a 위에만 있으면 된다.

### Extremal Elements of Posets

- Greatest element: 최상위 원소. 0 or 1개 존재.
- Least element: 최하위 원소. 0 or 1개 존재.
- Maximal element: 자신보다 높은 원소가 없는 원소. 0 or 1개 이상 존재.
- Minimal element: 자신보다 낮은 원소가 없는 원소. 0 or 1개 이상 존재.
- Upper Bound & Lower Bound: 어떤 원소의 상위, 하위 원소. 0 or 1개 이상 존재.
- LUB(Least Upper Bound): 두 원소와 가장 가까운 상위 원소. 0 or 1개 존재. 자기 자신이 LUB가 될 수 있다. `a ∨ b`
- GLB(Greatest Lower Bound): 두 원소와 가장 가까운 하위 원소. 0 or 1개 존재. 자기 자신이 GLB가 될 수 있다. `a ∧ b`

### Lattice

- 모든 두 원소가 LUB와 GLB를 가지고 있는 poset.
- hasse diagram에 나비 모양이나 끝이 갈라진 모양이 포함되어 있다면 lattice가 될 수 없다.
- a가 `a ∨ b`보다 작거나 같고, b가 `a ∨ b`보다 작거나 같으면 lub.
- a가 c보다 작거나 같고, b가 c보다 작으면, `a ∨ b`는 c보다 작거나 같다.
- a가 `a ∧ b`보다 크거나 같고, b가 `a ∧ b`보다 크거나 같으면 glb.
- a가 c보다 크거나 같고, b가 c보다 크거나 같으면, `a ∧ b`는 c보다 크거나 같다.

### Boolean Algebra

- Bounded: greatest element와 least element가 존재하는 poset. 무한집합은 bounded 불가능.
- Distributive: `a ∧ (a ∨ b) = (a ∧ b) ∨ (a ∧ c)`, `a ∨ (a ∧ b) = (a ∨ b) ∧ (a ∨ c)`을 만족하는 poset.
    - hasse diagram에 경로의 길이가 다르거나 서로 다른 경로가 3개 이상 존재하는 모양이 포함되어 있다면 distributive하지 않는다.
- Complemented: 두 원소의 upper bound가 greatest element이고, lower bound가 least element인 poset. `a ∨ b = Greatest`이고, `a ∧ b = Least`라면 a의 complement는 b, b의 complement는 a가 된다. complement는 여러 개일 수 있다.
- Boolean Algebra: bounded, distributive, complemented를 만족하는 poset.
- Simplification: `a ∨ a' = I`, `a ∧ I = a`
    - `(a ∧ b ∧ c) ∨ (b ∧ c) = (a ∨ I) ∧ (b ∧ c)`
- element가 `2^(n)`개가 아니면 boolean algebra가 될 수 없다.
- {a, b, c}를 111, {a, b}를 110, {b, c}를 011, 이렇게 나타낸다면, `∧`와 `∨` 연산이 AND와 OR과 동일하게 동작한다.  `110 {a, b} ∧ 011 {b, c}`은 AND 연산을 하면 `010`이며 이 둘의 GLB가 `{b}`임을 의미한다.
