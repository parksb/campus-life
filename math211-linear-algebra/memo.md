# 선형대수

$$
\gdef\sbmatrix#1{\begin{bmatrix}#1\end{bmatrix}}
$$

## Matrices and Systems of Equation

- 선형방정식(linear equation):
  - $a_1x_1 + a_2x_2 + \cdots + a_nx_n = b$처럼 선형적으로 결합된 방정식.
  - 선형함수의 그래프는 직선으로 표현됨.
  - 선형함수 $f$에 대해 $f(ax + by) = af(x) = bf(y)$를 만족.
- 선형시스템(linear system):
  - 동일한 변수를 사용하는 방정식이 여러 개가 있다면, 시스템으로 다룰 수 있음:
    - $a_{11}x_1 + a_{12}x_2 + \cdots + a_{1n}x_n = b_1$
    - $a_{21}x_1 + a_{22}x_2 + \cdots + a_{2n}x_n = b_2$
    - $a_{m1}x_1 + a_{m2}x_2 + \cdots + a_{mn}x_n = b_m$
    - $m \times n$ 선형시스템의 해는 ordered n-tuple $(x_1, x_2, \cdots, x_n)$ 형태.
  - 예시:
    - $x_1 + 2x_2 = 5$, $2x_1 + 3x_2 = 8$:
      - $2 \times 2$ 크기의 선형 시스템.
      - 두 방정식을 연립해서 풀면 답은 $(1, 2)$ 순서쌍.
    - $x_1 - x_2 + x_3 = 2$, $2x_1 + x_2 - x_3 = 4$
      - $2 \times 3$ 크기의 선형시스템.
  - 해를 구할 수 없는 경우, 시스템이 모순(inconsistent)이라고 한다.
- 선형시스템을 기하학적으로 표현할 수 있음. 세 가지 형태의 선형시스템이 있다:
  ![](./images/fig-1-1-1.png)
  1. 한 점에서 교차하는 경우: $x_1 + x_2 = 2$, $x_1 - x_2 = 2$
  2. 평행하는 경우(모순): $x_1 + x_2 = 2$, $x_1 + x_2 = 1$
  3. 같은 경우(해가 무수히 많음): $x_1 + x_2 = 2$, $-x_1 - x_2 = -2$
- 등가 시스템(equivalent systems):
  - 같은 변수로 구성이 되어 있는 두 선형시스템의 해집합(solution set)이 같은 경우.
  - 방정식의 순서는 해에 영향을 주지 않는다. 즉, 순서만 다른 두 시스템은 등가 시스템을 만족.
  - 양변에 같은 값을 더하거나 빼는 경우, 0이 아닌 같은 값을 곱하거나 나누는 경우에도 해에 영향을 주지 않는다.

### Strict Triangular Form

- 주어진 선형시스템이 $n \times n$일 때.
- 시스템을 strict triangular form으로 변형할 수 있다면 유일한 ordered n-tuple 해를 구할 수 있음.
- $k$번째 방정식에서 첫 $k - 1$개의 변수가 모두 0이고, $x_k$는 0이 아닌 형태.
- 행렬에서 값이 0인 요소들이 삼각형의 형태를 이룸.
- e.g., 아래와 같은 시스템이 있다:
  $$
  \begin{aligned}
  4 - x_2 - x_3 + x_4 &= 0 \\
  x_1 - x_2 - x_3 + x_4 &= 6 \\
  2x_1 + 4x_2 + x_3 - 2x_4 &= -1 \\
  3x_1 + x_2 - 2x_3 + 2x_4 &= 3
  \end{aligned}
  $$
  이 시스템의 증강행렬은 아래와 같음.
  $$
  \left[ \begin{array}{cccc|c}
      0 & -1 & -1 & 1 & 0 \\
      1 & -1 & -1 & 1 & 6 \\
      2 & 4 & 1 & -1 & -1 \\
      3 & 1 & -2 & 2 & 3
  \end{array} \right]
  $$
  행 연산 1을 통해 첫 번째 행과 두 번째 행을 교체한다. 이제 첫 행은 pivot이 되고, piove 원소는 1($a_{11} = 1$)이다.
  $$
  \left[ \begin{array}{cccc|c}
      1 & -1 & -1 & 1 & 6 \\
      0 & -1 & -1 & 1 & 0 \\
      2 & 4 & 1 & -1 & -1 \\
      3 & 1 & -2 & 2 & 3
  \end{array} \right]
  $$
  행 연산 3을 두 번해서 첫 번째 열에서 두 개의 nonzero 엔트리를 소거한다.
  $$
  \left[ \begin{array}{cccc|c}
      1 & -1 & -1 & 1 & 6 \\
      0 & -1 & -1 & 1 & 0 \\
      0 & 2 & -1 & -4 & -13 \\
      0 & -2 & -5 & -1 & -15
  \end{array} \right]
  $$
  이제 두 번째 행이 pivot이 되고, 두 번째 열을 소거한다.
  $$
  \left[ \begin{array}{cccc|c}
      1 & -1 & -1 & 1 & 6 \\
      0 & -1 & -1 & 1 & 0 \\
      0 & 0 & -3 & -2 & -13 \\
      0 & 0 & -3 & -3 & -15
  \end{array} \right]
  $$
  마지막으로 세 번째 행이 pivot이 되고, 세 번째 열을 소거한다.
  $$
  \left[ \begin{array}{cccc|c}
      1 & -1 & -1 & 1 & 6 \\
      0 & -1 & -1 & 1 & 0 \\
      0 & 0 & -3 & -2 & -13 \\
      0 & 0 & 0 & -1 & -2
  \end{array} \right]
  $$
  후진대입법(back substitution)으로 해를 구하면 $(2, -1, 3, 2)$.

### Row Echelon Form (REF)

- strict triangular form으로 간소화할 수 없을 때, 사다리꼴로 간소화할 수 있음.
- 행렬이 아래 조건을 충족할 때 REF라고 할 수 있음:
  - 각 행의 첫 nonzero 값이 1이어야.
  - 0으로 채워진 행이 없다면, 다음 행의 0개수가 더 많아야.
  - 0으로 채워진 행이 있다면, 실수를 포함하는 행보다 아래에 있어야.
- lead variable: 각 행의 첫 nonzero 요소.
- free variable: lead variable 외의 요소.
- REF로 간소화해서 연립방정식을 푸는 방식이 가우시안 소거법.
- overdetermined system: 방정식의 개수보다 미지의 수가 많은 시스템.
- underdetermined system:
  - 미지의 수가 방정식의 개수보다 많은 시스템.
  - 모순이 되거나, 무수히 많은 해를 갖는다.
- homogeneous system: 우변이 모두 0인 시스템. 항상 유일한 해가 존재.
- Reduced Row Echelon Form (RREF):
  - 행렬이 REF이고, 각 행의 lead variable이 그 열에서 유일한 nonzero인 경우.
  - RREF를 사용하는 소거법이 가우스-조던 소거법.

### Matrix Arithmetic

- 행렬을 연산할 수 있음: 덧셈, 뺄셈, 곱셈.
- 행렬의 구성 성분은 실수 스칼라 값. 행렬 표현법, 열 벡터와 행 벡터, 스칼라 얘기...
  - 우리는 주로 열 벡터를 쓸거임: $\bf{x}$
  - 행 벡터는 화살표를 붙일게요: $\bf{\overrightarrow x}$
- 스칼라 곱셈(scalar multiplication):
  $$
  \begin{bmatrix}
  3 & 2 & 1 \\
  4 & 5 & 6
  \end{bmatrix} \times
  10 =
  \begin{bmatrix}
  30 & 20 & 10 \\
  40 & 50 & 60
  \end{bmatrix}
  $$
  - 행렬 $A$에 스칼라 $\alpha$를 곱하면 $\alpha A$로 표기.
  - $A$의 모든 요소에 $\alpha$를 곱하면 됨.
- 행렬 덧셈(matrix addtion):
  $$
  \begin{bmatrix}
  3 & 2 & 1 \\
  4 & 5 & 6
  \end{bmatrix} +
  \begin{bmatrix}
  2 & 2 & 2 \\
  1 & 2 & 3
  \end{bmatrix} =
  \begin{bmatrix}
  5 & 4 & 3 \\
  5 & 7 & 9
  \end{bmatrix}
  $$
  - 두 행렬 $A$와 $B$의 차원이 같을 때 두 행렬을 더할 수 있음: $A + B$
  - 두 행렬의 같은 위치에 있는 값을 더해서($a_{ij} + b_{ij}$) 새로운 행렬을 만들 수 있음.
- 행렬 곱셈(matrix multiplication):
  - 선형방적식 $ax = b$를 행렬로 표현하면: $[a][x] = [b]$.
  - $m \times n$ 선형 시스템을 행렬 방정식으로 표현하면: $A\bf x = \bf b$
  - 이때, $A\mathbf{x} = a_1x_1 + a_2x_2 + \cdots + a_nx_n = \bf b$
  - 곱셈은 두 행렬의 차원이 달라도 됨. 단, 좌측 행렬의 열 개수와 우측 행렬의 행 개수가 같아야.
  - 선형 방정식 $3x_1 + 2x_2 + 5x_3 = 4$는 아래와 같은 행렬 곱으로 표현할 수 있음:
    $$
    A\mathbf{x} =
    \begin{bmatrix}
    3 & 2 & 5
    \end{bmatrix}
    \begin{bmatrix}
    x_1 \\ x_2 \\ x_3
    \end{bmatrix} =
    3x_1 + 2x_2 + 5x_3 = 4
    $$
  - 행렬 곱셈에서 교환법칙은 성립하지 않음.
  - 두 행렬 $A$는 $m \times n$이고, $B$는 $n \times r$이라면:
    $$
    A=\begin{bmatrix}a_{11} & a_{12} & \cdots & a_{1n} \\ {\color{blue}a_{21}} & {\color{blue}a_{22}} & {\color{blue}\cdots} & {\color{blue}a_{2n}} \\ \vdots & \vdots & \ddots & \vdots \\ a_{m1} & a_{m2} & \cdots & a_{mn}\end{bmatrix},\space
    B=\begin{bmatrix}{\color{red}b_{11}} & b_{12} & \cdots & b_{1r} \\ {\color{red}b_{21}} & b_{22} & \cdots & b_{2r} \\ {\color{red}\vdots} & \vdots & \ddots & \vdots \\ {\color{red}b_{n1}} & b_{n2} & \cdots & b_{nr}\end{bmatrix}
    $$
    이때 두 행렬의 곱 $AB$는 $m \times r$ 행렬:
    $$
    AB=\begin{bmatrix}\sum_k a_{1k}b_{k1} & \sum_k a_{1k}b_{k2} & \cdots & \sum_k a_{1k}b_{kr} \\ {\color{#C0C}\sum_k a_{2k}b_{k1}} & \sum_k a_{2k}b_{k2} & \cdots & \sum_k a_{2k}b_{kr} \\ \vdots & \vdots & \ddots & \vdots \\ \sum_k a_{mk}b_{k1} & \sum_k a_{mk}b_{k2} & \cdots & \sum_k a_{mk}b_{kr}\end{bmatrix}
    $$
    여기서 $AB$의 $i$행 $j$열의 성분은 $\sum_k a_{ik}b_{kj}$. 예를 들어, $AB$의 2행 1열의 성분은 ${\color{#C0C}\sum_k a_{2k}b_{k1}}$. 이는 $A$의 ${\color{blue}\text{2행}}$의 각 성분과 $B$의 ${\color{red}\text{1열}}$의 대응되는 성분의 곱을 모두 합한 것과 같음.
- 전치(transpose):
  - $m \times n$ 행렬의 열과 행을 뒤바꿔서 $n \times m$ 행렬로 변형.
  - $A$에 대한 전치행렬은 $A^T$로 표현. 당연하지만 ${A^T}^T = A$.
  - $n \times n$ 행렬 $A$가 $A^T = A$라면 대칭(symmetric).

### Elementary Matrices

- 기본행렬: $A\bf x = \bf b$의 양변에 곱했을 때 등가시스템을 만족하게 하는 행렬.
  - 그냥 수라면 $\bf x = \bf b / A$ 같은 식으로 했겠지만, 행렬이니까 $A^{-1}A\bf x = A^{-1}\bf b$, $\bf x = A^{-1}\bf b$처럼 구해야.
  - $m \times m$의 nonsingular 행렬 $M$을 가정: $MA\bf x = M\bf b = A\bf x = \bf b$.
- 기본행연산이 3개니까 기본 행렬의 종류도 3개:
  - Type 1:
    - 단위행렬에서 서로 다른 두 행을 교환한 행렬 $E_1$.
    - 행렬 $A$의 좌측에 곱하면($E_1A$): $A$의 두 행이 교환됨.
    - 행렬 $A$의 우측에 곱하면($AE_1$): $A$의 두 열이 교환됨.
  - Type 2:
    - 단위행렬에서 한 행에 nonzero 상수를 곱한 행렬 $E_2$.
    - 행렬 $A$의 좌측에 곱하면($E_2A$): $A$의 행에 상수가 곱해짐.
    - 행렬 $A$의 우측에 곱하면($AE_2$): $A$의 열에 상수가 곱해짐.
  - Type 3:
    - 단위행렬에서 한 행에 nonzero 상수를 곱한 값을 다른 행에 더한 행렬 $E_3$.
    - 행렬 $A$의 좌측에 곱하면($E_3A$): $A$의 행에 상수가 곱해진 값이 더해짐.
    - 행렬 $A$의 우측에 곱하면($AE_3$): $A$의 열에 상수가 곱해진 값이 더해짐.
- 기본행렬로 복잡한 행렬을 분해하여 간소화할 수 있음.
- 간소화에 쓰이는 몇가지 행렬들:
  - Upper triangular: $\begin{bmatrix} 3 & 2 & 1 \\ \color{blue}0 & 2 & 1 \\ \color{blue}0 & \color{blue}0 & 5 \end{bmatrix}$
    - 왼쪽 아래 삼각형 요소가 모두 0.
  - Lower triangular: $\begin{bmatrix} 1 & \color{blue}0 & \color{blue}0 \\ 6 & 0 & \color{blue}0 \\ 1 & 4 & 3 \end{bmatrix}$
    - 오른쪽 위 삼각형 요소가 모두 0.
  - Diagonal: $\begin{bmatrix} \color{blue}1 & 0 & 0 \\ 0 & \color{blue}3 & 0 \\ 0 & 0 & \color{blue}1 \end{bmatrix}$
     - 주대각을 제외한 모든 원소가 0.

## Determinants

- 행렬의 특성을 나타낼 수 있도록 행렬를 하나의 실수에 대응시켜 표현해보자.
- 세 가지 방법이 있음: determinant, norm, eigenvalue
- Determinant: 행렬식. 역행렬이 존재하게 하는 값. 행렬에 역행렬이 존재하는지 확인할 수 있다.
- $\text{det}(A) \neq 0$이라면 $A$는 nonsingular 행렬이다. (역행렬이 존재한다)
- 크기가 $1 \times 1$인 행렬을 가정해보자:
  - 역행렬이 있어야 하므로 nonsingular 행렬이어야.
  - 즉, $A^{-1} = {1 \over a}$. $a \neq 0$.
  - 이때 $\text{det}(A) = a \neq 0$.
- 크기가 $2 \times 2$인 행렬을 가정해보자:
  - $A = \begin{bmatrix} a_{11} & a_{12} \\ a_{21} & a_{22} \end{bmatrix}$
  - $a_{22} - {a_{21} \over a_{11}} a_{12} \neq 0$
  - 양변에 $a_{11}$을 곱해 정리하면: $\text{det}(A) = a_{11}a_{22} - a_{12}a_{21} \neq 0$
  - $A^{-1} = {1 \over \text{det}(A)} \begin{bmatrix} a_{22} & -a_{12} \\ -a_{21} & a_{11} \end{bmatrix}$
- $3 \times 3$부터는 복잡해짐. 특정 행이나 열을 기준으로(0이 많을수록 연산이 적음) cofactor 계산.
- 전치행렬에 대한 행렬식은? $\text{det}(A) = \text{det}(A^{-1})$
- 행렬 $A$가 $n \times n$ triangular 행렬이라면?
  - 상삼각 행렬이거나 하삼각 행렬 중 하나일것.
  - 주대각 원소의 곱으로 구할 수 있다.
  - 행렬을 triangular form으로 바꿀 수 있다면 행렬식을 쉽게 구할 수 있을 것.
- 모두 0으로 채워진 행이나 열이 있다면 $\text{det}(A) = 0$.
- 동일한 행이나 열이 두 개 있다면 $\text{det}(A) = 0$.

## Vector Spaces

- 벡터는 이미 잘 알죠. 행렬은 n차원의 벡터를 표현하기 위한 방법이죠.
- 벡터간 닫힌 연산(덧셈, 스칼라곱)을 할 수 있는 공간이 벡터 공간.
- 공간을 차원으로 나눠서 생각:
  - $n$개의 차원: $\Bbb R^n \; (n = 1, 2, \cdots)$
  - $n$차원 벡터 공간의 벡터에는 n개의 성분이 있음.
- $\Bbb R^2$ 유클리디안 벡터 공간:
  - 유클리디안 2차원 벡터 공간 $\Bbb R^2$에서 벡터는: $\sbmatrix{x_1 \\ x_2}$
  - 벡터 공간에서의 이동: $(a, b)$에서 $(a + x_1, b + x_2)$로 향하는 선분.
  - 벡터 $x$의 유클리디안 거리: $\sqrt{x_1^2 + x_2^2}$
  - 벡터간 덧셈과 스칼라 곱셈에 대해 닫혀있음.
    - 덧셈:
      - $\sbmatrix{u_1 \\ u_2} + \sbmatrix{v_1 \\ v_2} = \sbmatrix{u_1 + v_1 \\ u_2 + v_2}$
    - 스칼라곱:
      - $\alpha \sbmatrix{x_1 \\ x_2} = \sbmatrix{\alpha x_1 \\ \alpha x_2}$
      - $\alpha$가 양수면 방향은 같고 크기만 바뀜. 음수면 방향이 180도 반대로.
- $\Bbb R^{m \times n}$ 유클리디안 벡터 공간:
  - $m \times n$ 실수 행렬의 집합으로 생각할 수 있음.
  - 당연히 연산이 가능하므로, 행렬 연산을 함.
  - 행렬 덧셈: $A + B = C$, $c_{ij} = a_{ij} + b_{ij}$
  - 행렬 스칼라곱: $\alpha A$, $c_{ij} = \alpha a_{ij}$
- 어떤 집합을 벡터 공간이라고 하려면 아래 공리를 만족해야:
  - 덧셈과 스칼라곱이 가능.
  - 덧셈의 결합법칙 성립.
  - 덧셈에 대한 항등원이 존재.
  - 덧셈에 대한 역원이 존재.
  - 스칼라곱의 분배법칙 성립.
  - 스칼라곱의 결합법칙 성립.
  - 스칼라곱에 대한 항등원이 존재.
- e.g., 닫힌 구간에서 실변속 연속함수의 집합 $C[a, b]$가 벡터 공간인지?
  - 덧셈: $C[a, b]$의 함수 $f, g$에 대해, $(f + g)(x) = f(x) + g(x)$
  - 스칼라곱: $(\alpha f)(x) = \alpha f(x)$
  - $z(x) = 0$, 0벡터가 존재하므로 덧셈에 대한 항등원도 존재: $f + z = f$
  - 이렇게 하나씩 공리를 만족하는지 확인해보면 된다.
- e.g., $n$차 미만의 차수를 갖는 다항식 집합 $P_n$가 벡터 공간인지?
  - 덧셈: $(p + q)(x) = p(x) + q(x)$
  - 곱셈: $(\alpha p)(x) = \alpha p(x)$
  - $z(x) = 0x^{n - 1} + 0x^{x - 2} + \cdots + 0x + 0 = \mathbf{0}$
