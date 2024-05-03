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
    - $\relation{a}{b}$
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

## Notices

- 중간고사 문제 풀 때 이상한 거 없었어요? 문제 6번 교집합이 15라고 되어 있는데 오타예요. 교집합이 될 수가 없지. 6번은 무조건 1점 부여할게요.
- 중간고사 질문 있으면 메일보내셈. 평균이랑 중간값도 공개해줄거임.
- 보강은 동영상 올려줄거니까 보세용. 출석체크는 안 할거임.
