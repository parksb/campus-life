# 이산수학

- 정수, 그래프, 논리 등 연속되지 않은 값을 가지는 대상의 구조와 성질에 관심.
- 컴퓨터의 데이터는 모두 이산적. 이산적 데이터 구조를 수학적으로 해석할 수 있음.
- 집합, 함수, 수열, 순열과 조합, 관계, 그래프, 트리, 부울 대수 등의 주제를 다룸.
- 중간까지는 정수론과 암호, 귀납법, 관계까지. 기말에는 그래프, 트리, 부울 대수 등을 다룸.
- 과제는 중간 전 2번, 기말 전 2번.
  - 교재의 연습 문제를 과제로 내줄거임.
  - 과제는 BB로 제출하게 될거예요.
- 수업이 끝나면 그 수업 내용을 확장하는 동영상을 올려줌:
  - 영상에는 더 많은 예제와 설명이 있을거임.
  - 동영상은 부가적인게 아니라 꼭 봐야함.

## Basic Structures

- 집합, 함수, 수열과 합, 행렬에 대해 배움.
- 개념은 고등학교에서 배웠을테니 여기에서는 기호와 표현에 중점을 둘거임.

### Sets

- 집합은 자료를 구분하고 모음을 정의. 집합에는 순서가 없음.
  - 집합의 원소를 element, member라고 지칭.
  - 집합을 표현하는 방법:
    - 원소나열법(Roster method): $S = \{1, 2, 3\} = \{3, 2, 1\}$
    - 조건제시법(Set-builder notation): $S = \{x \in \Bbb{Z}^+ | x \text{is odd and } x \lt 10\}$
- 공집합 $\varnothing = \{\}$
  - 공집합과 공집합을 가진 집합은 다름: $\varnothing \neq \{\varnothing\}$
- 부분집합:
  - 하나의 집합이 다른 집합에 속했는지, 속하지 않았는지.
  - $A$가 $B$에 속함: $A \in B$
  - $A \in B$이고, $B \in A$인 경우에도 서로가 서로의 부분집합.
- 카디널리티:
  - 집합의 크기(원소 개수), $|A| = n$
  - $|\varnothing| = 0$, $|\{\varnothing\}| = 1$
  - $|A \cup B| = |A| + |B| - |A \cap B|$
  - 유한집합뿐만 아니라 무한집합의 크기도 표현 가능: $|\Bbb{Z}$ (정수 집합의 카디널리티)
- Tuple:
  - 집합에서 원소가 순서를 갖는 순서쌍.
  - Ordered n-tuple: $(a_1, a_b, \cdot, a_n)$
  - Cartesian product:
    - $A \times B = \{(a, b) | a \in A \and b \in B\}$
    - $A$와 $B$를 결합해 만들 수 있는 모든 순서쌍의 집합.
- Set operations:
  - 합집합(union), 교집합(intersection)
  - 여집합(complementation): $\bar A = A^c = U - A = \{x | x \in U | x \notin A\}$
  - 차집합(difference): $A - B$
- 대칭차집합(Symmetric difference):
  - XOR, $A$와 $B$ 중 한쪽에만 속한 원소들의 집합.
  - $A \oplus B = (A - B) \cup (B - A)$
- 집합의 항등관계:
  - 항등법칙(identity): $A \cup \varnothing = A$, $A \cap U = A$
  - 지배법칙(domination): $A \cup U = U$, $A \cap \varnothing = \varnothing$
  - 멱등법칙(idempotent): $A \cup A = A$, $A \cap A = A$
  - 보원법칙(complementation): $\bar{\bar{A}} = A$
  - 교환법칙(commutative): $A \cup B = B \cup A$, $A \cap B = B \cap A$
  - 결합법칙(associative):
    - $A \cup (B \cup C) = (A \cup B) \cup C$
    - $A \cap (B \cap C) = (A \cap B) \cap C$
  - 분배법칙(distributive):
    - $A \cap (B \cup C) = (A \cap B) \cup (A \cap C)$
    - $A \cup (B \cap C) = (A \cup B) \cap (A \cup C)$
    - 우변 대신 좌변의 연산을 수행하면 연산수를 줄일 수 있겠죠.
  - 드 모르간 법칙(De Morgan):
    - $\bar{A \cup B} = \bar A \cap \bar B$
    - $\bar{A \cap B} = \bar A \cup \bar B$
    - `!(A && B)`와 `!A || !B`가 같다는 것. 좌변 연산의 연산수가 적겠지.
  - 흡수법칙(absorption):
    - $A \cup (A \cap B) = A$
    - $A \cap (A \cup B) = A$
  - 보수법칙(complement): $A \cup \bar{A} = U$, $A \cap \bar{A} = \varnothing$

### Functions

- $\varnothing$이 아닌 어떤 두 집합의 원소간 대응관계가 함수.
  - $A$ 원소 각각에 $B$ 원소 하나를 대응시킨 것을 $A$에서 $B$로의 함수라고 함: $f: A \to B$
  - $A$의 원소 $a$, $B$의 원소 $b$에 대해 $f(a) = b$.
  - $f(x) = y_1$이고, $f(x) = y_2$일 때, $y_1 = y_2$이어야.
  - 함수는 매핑(mapping) 또는 변환(transformation)이라고도 한다.
- 용어 정리를 해보자, $f: A \to B$일 때, f(a) = b:
  - $a$는 원상(preimage), $b$는 상(image)
  - $A$는 함수 $f$의 정의역(domain), $B$는 함수 $f$의 공역(codomain)
  - $f$가 반환하는 $b$의 집합은 치역(range), 즉, 치역 $f(a)$는 항상 $B$의 부분집합.
- 함수로 관계(relation)을 표현할 수 있음.
  - 집합 $A$에서 $B$로의 모든 관계를 카테시안 곱으로 표현할 수 있음.
  - 결국 $f: A \to B$는 $A \times B$의 부분집합.
- Injection, surjection, 일대일대응(bijection)

## Relation

- 이항관계(binary relation)
  - 원소간 관계는 순서쌍의 집합으로 표현.
  - 순서쌍이므로 $(a, b)$와 $(b, a)$는 서로 다름.
  - 집합 $A$와 $B$ 사이 관계는 $A \times B$.
  - $|A \times B| = |A||B|$
  - e.g., $A = \{1, 2, 3\}, B = \{r, s\}$
    - $A \times B = \{(1, r), (1, s), (2, r), (2, s), (3, r), (3, s)\}$
    - $B \times A = \{(r, 1), (r, 2), (r, 3), (s, 1), (s, 2), (s, 3)\}$
    - 관계의 수학적 정의: 이항관계 $R$은 $A \times B$의 부분 집합.
- n항 관계(n-ary relation)
  - 이항관계를 확장하면 n개 항에 대한 관계를 표현할 수 있다. ($A_1 \times A_2 \times A_3 \times \cdots$)
  - RDB 테이블을 생각하면 됨. 이항관계는 컬럼이 2개 있는 테이블, n항관계는 컬럼이 n개 있는 테이블.
- 한 집합 내에도 관계를 정의할 수 있음:
  - e.g., $A = \{a, b, c, d\}, R \in A \times A$
    - $R = \{(a, a), (a, b), (b, c), (c, a), (d, c), (c, b)\}$
    - $a$와 관계가 있는 원소 집합, 즉 $(a, ?)$, $R(a) = \{a, b\}$
    - $b$와 관계가 있는 원소 집합, 즉 $(b, ?)$, $R(b) = \{c\}$
    - $A_1 = \{c, d\}$와 관계가 있는 원소 집합 $R(A_1) = \{a, b, c\}$
