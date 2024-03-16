# 선형대수

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
  행 연산 3을 두 번해서 첫 열에서 두 개의 nonzero 엔트리를 소거한다.
  $$
  \left[ \begin{array}{cccc|c}
      1 & -1 & -1 & 1 & 6 \\
      0 & -1 & -1 & 1 & 0 \\
      0 & 2 & -1 & -4 & -13 \\
      0 & -2 & -5 & -1 & -15
  \end{array} \right]
  $$
  이제 두 번째 행이 pivot이 되고, 두 번째열을 소거한다.
  $$
  \left[ \begin{array}{cccc|c}
      1 & -1 & -1 & 1 & 6 \\
      0 & -1 & -1 & 1 & 0 \\
      0 & 0 & -3 & -2 & -13 \\
      0 & 0 & -3 & -3 & -15
  \end{array} \right]
  $$
  마지막으로 세 번째 행이 pivot이 되고, 세 번째 컬럼을 소거한다.
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
