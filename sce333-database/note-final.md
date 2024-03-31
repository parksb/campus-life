# 데이터베이스

## Functional Dependency and Normalization

- 데이터베이스의 품질을 측정하는 기준:
  - attribute semantics를 명확히 한다.
  - 튜플의 중복된 정보를 최소화한다.
  - 튜플의 NULL 값을 최소화한다.
  - 위변조 튜플의 생성을 방지한다.
- 각 튜플은 하나의 엔티티나 릴레이션십 인스턴스를 표현해야 함.

### Redundancy

- 중복 데이터는 저장 공간을 낭비.
- Insertion anomalies
- Deletion anomalies: 한 레코드를 지우려면 중복된 모든 레코드를 제거해야.
- Update anomalies: 레코드의 내용을 변경하려면 중복된 모든 레코드를 변경해야.

### Null values

- NULL은 다양한 의미를 가짐.
- 테이블을 분리하면 NULL을 없앨 수 있다. (NULL 대신 아예 레코드가 없게 됨)
- spurious tuples:
  - 실제로 존재하지 않는 fake record.
  - 조인을 잘못하면 spurious tuple이 생길 수 있음.

### Functional Dependencies (FD)

- relational design의 일반화된 formal measures of the goodness.
- X가 Y를 functionally determine한다: X의 값이 Y의 유니크한 값을 결정하는 경우.
  - e.g., 학번이 같으면 이름이 같다.
  - FD는 존재할 수 있다(may exist)고 표현. 반례를 찾으면 존재하지 않는다(do not exist).
- 테이블을 보고 FD가 존재할 수 있는지, 존재하지 않는지 판단할 수 있어야.

### Normalization

- '나쁜' 릴레이션을 쪼개 어트리뷰트들을 작은 릴레이션으로 나누는 것.
- Normal Forms (NF):
  - 포함관계: BCNF $\subset$ 3NF $\subset$ 2NF $\subset$ 1NF.
  - prime attribute: 후보키의 일부여야 한다.
  - nonprime attribute: prime attribute가 아닌 것들. 후보키의 일부도 아님.
  - decomposition할 때는 뭘로 조인할건지 고민해보면 된다.

#### 1st NF

- 모든 어트리뷰트가 키에 의존하는 형식.
- composite attr, nested attr, multivalued relation이 없다면 1NF.
- 별도 릴레이션으로 분리하거나, 컬럼을 추가함으로써 해결할 수 있음.

#### 2nd NF

![](https://user-images.githubusercontent.com/6410412/244057741-f4e29ee6-9288-41c3-8a89-a6a711d01e97.png)

- 모든 non-prime attr이 PK에 Fully FD한 형식.
- 더 일반화된 정의: 모든 non-prime attr이 모든 키에 Fully FD한 형식.
- PK가 진짜 prime한 것만으로 구성되어 있는가?
- Full FD: e.g., (Ssn, Pnumber) $\rightarrow$ Hours. Ssn $\rightarrow$ Hours, Pnumber $\rightarrow$ Hours 둘 다 표현할 수 없으므로.
- Not a Full FD (Partial dependency): e.g., (Ssn , Pnumber) $\rightarrow$ Ename. Ssn $\rightarrow$ Ename으로 표현할 수 있으므로.
- PK의 일부가 non-prime attr을 결정해서는 안 됨.
- 1NF를 만족한다.

#### 3rd NF

![](https://user-images.githubusercontent.com/6410412/244057854-7883362c-d387-4d61-a660-e042367f7ab9.png)

- 어떠한 non-prime attr도 PK에 대해 transitively dependent하지 않은 형식.
- Transitive FD: $X \rightarrow Z$는 두 FD, $X \rightarrow Y$와 $Y \rightarrow Z$로 유도할 수 있다.
- transitive하다면 테이블을 분리할 수 있음.
- FD 관계 X $\rightarrow$ A 에서 X가 SK이거나, A가 prime attr이라면 3NF를 만족한다.
- non-prime attr이 다른 non-prime attr을 결정해서는 안 됨.
- 1NF와 2NF를 만족한다.

#### BCNF

- FD X $\rightarrow$ A에서 X가 SK인 형식.
- 키가 아닌 어트리뷰트가 결정자 역할을 한다면 분리해야 한다.
- N개 컬럼에 대해 decomposition 방법이 N개가 있을 수 있다.
- non-prime attr이 prime attr을 결정해서는 안 됨.
- 1NF, 2NF, 3NF를 만족한다.

## Indexing

- 인덱싱은 거대한 데이터베이스를 효율적으로 검색하기 위한 데이터 구조.
- 두 가지 핵심 개념:
  - 레코드를 디스크 블록에 매핑한다.
  - 빠른 검색을 위해 부가적인(auxiliary) 데이터 구조를 유지한다.
- 인덱스는 page id와 block address를 매핑해둔 auxiliary file.
  - 기본적으로 <field value, pointer to record> 형태.
  - auxiliary data structure의 장점: raw data에 비해 같은 공간에 더 많은 정보를 저장해둘 수 있음.
  - 단점: 인덱스 자체가 실제 데이터를 의미하지는 않으므로, 액세스가 한 번 더 필요함.
- 인덱스의 성격을 dense와 sparse로 나눌 수 있음:
  - Dense:
    - 모든 레코드가 인덱스 엔트리에 매핑되어 있는 경우.
    - 이때 page id는 데이터의 순서와 동일, binary search하면 된다.
    - 데이터가 정렬되어 있지 않다면 dense index를 사용해야 한다.
  - Sparse (or nondense):
    - 일부 레코드만 매핑되어 있는 경우.
    - 데이터 블록당 하나의 키-포인터 쌍이 존재한다.
    - 데이터가 정렬되어 있다면 sparse index를 사용해도 된다.
  - 인덱스는 sorted lists나 hashing으로 표현할 수 있다.

### Primary Index

![](https://user-images.githubusercontent.com/6410412/237427776-094fce65-b9e5-48f1-b04e-4f4dfa9636cf.png)

- 정렬된 데이터를 위한 sparse index.
- 인덱스 엔트리가 각 블록의 첫 번째 레코드를 가리킨다.
- record organization:
  - spanned: 레코드가 여러 블록에 걸쳐서 저장되는 경우. 레코드가 블록보다 클 때 필요하다.
  - unspanned: 레코드가 한 블록 안에만 저장되는 경우.
- 인덱스 엔트리는 정렬되어 있으므로 binary search가 가능함.

> 예시(without primary index):
> - r = 300000, b = 4096B
> - R = 100B on unspanned file
> - bfr = $\lfloor b / R \rfloor$ = $\lfloor {4096 \over 100} \rfloor$ = 40 records per block.
> - num of blocks = $\lceil {r \over \text{bfr}} \rceil$ = $\lceil {300000 \over 40} \rceil$ = 7500 blocks.
> - $\therefore$ total number of blocks = $\lceil \log_2 7500 \rceil$ = 13.

> 예시(with primary index):
> - r = 300000, b = 4096B
> - R = 100B on unspanned file
> - V = 9B, P = 6B
> - bfr = $\lfloor b / R \rfloor$ = $\lfloor {4096 \over 100} \rfloor$ = 40 records per block.
> - num of blocks = $\lceil {300000 \over 40} \rceil$ = 7500 blocks.
> - bfr for index = $\lfloor {b \over (V + P)} \rfloor$ = $\lfloor {4096 \over 15} \rfloor$ = 273 entries per block.
> - num of blocks for index = $\lceil {7500 \over 273} \rceil$ = 28 blocks.
> - $\therefore$ total number of blocks = $\lceil \log_2 28 \rceil$ = 5 + 1 = 6.

- 인덱스 엔트리 수는 레코드 수보다 적다.
- 인덱스 엔트리 크기는 레코드 크기보다 작다. (인덱스의 V + P 값이 R 값보다 작음.)
- 따라서 데이터 레코드를 binary search 하는 것보다 인덱스를 탐색하는 편이 훨씬 효율적.

### Secondary Index

![](https://user-images.githubusercontent.com/6410412/237428049-c2b58446-911a-41a3-bc27-7791b3458c34.png)

- primary index가 이미 있다고 가정, candidate keys에 사용하는 추가적인 인덱스.
- 정렬되지 않은 데이터를 위한 dense index. (물론 정렬된 경우에도 사용 가능.)
- 따라서 secondary index에는 레코드 수만큼의 엔트리가 필요하다.
- 인덱스는 두 개의 필드로 정렬되어 있음:
  - 첫 번째 필드: 데이터 파일의 non-ordering field와 같은 데이터 타입.
  - 두 번째 필드: block pointer 또는 record pointer 중 하나.
- 엔트리 수가 많으므로 primary index보다 더 많은 공간과 탐색 시간을 필요로한다.
- 하지만 정렬되지 않은 임의의 레코드에 대한 탐색 시간을 개선해줌.

> 예시:
> - r = 300000, b = 4096B
> - R = 100B on unspanned file
> - V = 9B, P = 6B
> - bfr = $\lfloor {b \over (V + P)} \rfloor$ = $\lfloor {4096 \over 15} \rfloor$ = 273 entries per block.
> - num of blocks for index = $\lceil 300000 / 273 \rceil$ = 1099 blocks. (dense)
> - $\therefore$ total number of blocks = $\lceil \log_2 1099 \rceil$ = 11 + 1 = 12.

### Multi-level Secondary Index

- 페이지 당 하나의 엔트리를 두려면 많은 저장공간이 필요함.
- 만약 secondary index가 엄청 커진다면?
- 인덱스의 인덱스를 만들면 더 적은 접근으로 데이터를 찾을 수 있다.

> 예시:
> - r = 300000, b = 4096B
> - R = 100B on unspanned file
> - V = 9B, P = 6B
> - bfr = $\lfloor {4096 \over 15} \rfloor$ = 273 entries per block.
> - num of blocks for index = $\lceil {300000 \over 273} \rceil$ = 1099 blocks. (dense)
> - num of blocks for 2nd-level index = $\lceil {1099 \over 273} \rceil$ = 5 blocks.
> - num of blocks for 3rd-level index = $\lceil {5 \over 273} \rceil$ = 1 block.
> - $\therefore$ total number of blocks = 3 + 1 = 4.

## B-Tree: Dynamic Multi-level Index

- multi-level index를 동적으로 관리(추가/삭제)하기 위한 자료구조.
- binary tree가 하나의 인덱스만 갖는다면, b-tree에는 여러 개의 인덱스가 있음.
- properties of b-tree:
  - balanced tree.
  - q 범위 노드에는 q - 1개의 키가 있음.
  - 최소 $q / 2$ 개의 엔트리가 있어야. (루트가 아닌 경우)
  - 루트부터 리프까지의 거리가 모두 같음.
- 포인터를 따라가며 탐색한다: $\log_B(n)$, 이때 B는 블록 당 엔트리 개수. 이걸 order of b-tree라고 한다.

## B+Tree: Optimizing B-Tree

- b-tree는 트리의 모든 노드에 레코드를 가리키는 포인터가 있음:
  - 반면 b+tree는 리프 노드만 data pointer를 가짐. internal node는 tree pointer만을 갖는다.
  - 또한 leaf node가 다른 leaf node를 가리킨다.
- 무조건 리프 노드에 도달할 수 있으므로 항상 같은 복잡도를 보장할 수 있음.
- higher-capacity indexes: $q - 1$개의 키로 $q$ 범위를 정의할 수 있음.
- 리프 노드가 링크드리스트를 이루고 있어서 빠르게 범위 탐색을 할 수 있음.

## Other Indexing Structures

- Hash-Based file Organization:
  - O(1) 시간복잡도.
  - 범위를 기준으로 검색하려면 결국 모든 노드를 살펴봐야 한다.
- R+Tree:
  - b+tree와 비슷한데 공간 데이터를 위한 자료구조.
  - 나와 가까운 매장찾기, 이런 거 minimum bounding box를 이용해 저장.

## Introduction to Transaction Processing Concepts and Theory

### Transaction Basics

- 트랜잭션은 데이터베이스 프로세싱의 논리적 단위.
- 하나의 트랙잭션이 하나 이상의 명령을 포함할 수도 있음. (e.g., 한 건의 계좌이체에 잔고 확인, 이체, 잔고 갱신의 과정이 포함됨.)
- 시스템에서 가장 기본적인 명령은 읽기, 쓰기 뿐.
- ACID: 데이터베이스 시스템을 사용하는 이유이기도.
  - Atomicity:
    - 트랜잭션은 하나의 단위로 커밋되거나, 롤백된다.
    - 위협: 시스템 실패, 책임: recovery manager
  - Consistency:
    - 데이터는 항상 정해진 규칙을 만족해야 한다.
    - 위협: 트랜잭션 로직 에러, 책임: 프로그래머
  - Isolation:
    - 트랜잭션이 서로 영향을 미쳐서는 안 된다. (independent하다는 건 아님!)
    - 위협: 동시적 실행, 책임: concurrency control manager
  - Durability:
    - 커밋된 데이터는 물리적인 상황(전원이 꺼지는 등)에도 유지되어야 한다.
    - 위협: 시스템 실패, 책임: recovery manager
- Transaction State
  - 에러 등으로 partially commit되는 경우, 시스템이 어느 부분에서 에러가 발생했는지 체크하고 롤백한다.
  - Three types of transaction life:
    - Successful
    - Application requests termination
    - Forced termination
  - 사용자가 버튼을 잘못 누른 경우 트랜잭션을 중단해야 함.
- Reovery manager:
  - Commit: 트랜잭션이 성공한 경우. 커밋되면 되돌릴 수 없음.
  - Rollabck (or abort): 트랜잭션이 실패한 경우.

### How to schedule transaction

- 동시성에 대해 생각해보자:
  - Interleaved processing: 하나의 CPU에서 여러 작업을 번갈아 실행.
  - Parallel processing: 여러 CPU에서 여러 작업을 동시에 실행.
- Transaction management가 필요한 이유:
  - Lost udpate problem: 업데이트되기 전 데이터를 기준으로 덮어쓰는 문제.
    ![](https://user-images.githubusercontent.com/6410412/244058042-87ab1c64-baf3-4aa2-a81b-79848a8e64e7.png)
  - Temporary update (dirty read) problem: 데이터가 변경되기 전에 읽는 문제.
    ![](https://user-images.githubusercontent.com/6410412/244058067-46f32377-74a9-4ae8-9c6e-ff6db1d4a0af.png)
  - Incorrect summary problem: 집계 후 데이터가 변경되어 잘못된 결과를 얻는 문제.
    ![](https://user-images.githubusercontent.com/6410412/244058089-0345aaff-65fc-47ea-8a6b-607f87786088.png)
- 트랜잭션을 어떻게 스케줄링할 것인가?
  - 트랜잭션 간 순서를 조정한다.
  - 순차(serial) 실행한다:
    - 한 트랜잭션이 끝난 다음에 다른 트랜잭션을 수행하도록 한다.
    - 단, 어떤 트랜잭션이 먼저 실행될지는 보장할 수는 없다.
- Serializability of Transactions:
  - Equivalent schedule: 두 스케줄의 효과가 동일한 경우 equivalent.
  - Serializable schedule: 트랜잭션의 순차 실행과 equivalent한 스케줄.
  - serializable한 것은 serial한 것과 같지 않다.
  - serializable하다는 것은 그 스케줄이 올바른 스케줄이라는 것.
- Anomalies for interleaved schedules:
  ![](https://user-images.githubusercontent.com/6410412/244058307-b3226614-640a-44c4-ac43-46f7fd62d64f.png)
  - 오퍼레이션을 수행하며 conflict가 발생할 수 있음:
    - 서로 다른 트랜잭션이 하나의 아이템에 접근할 때.
    - 적어도 하나의 write operation이 있는 경우.
  - RW conflict: 값이 변경되기 전에 읽는 문제.
  - WR conflict (dirty read): 커밋되지 않은 값을 읽는 문제.
  - WW conflict: 아직 커밋되지 않은 데이터를 덮어쓰는 문제.
- Serializability testing:
  - 트랜잭션 사이 그래프를 그려 serializable한지 확인할 수 있음:
    - T1이 W(X)하고, T2가 R(X): T1 $\rightarrow$ T2
    - T1이 R(X)하고, T2가 W(X): T1 $\rightarrow$ T2
    - T1이 W(X)하고, T2가 W(X): T1 $\rightarrow$ T2
  - 사이클이 없다면 안전하게 serializable schedule을 할 수 있음.

### Transaction Support in RDBMS

- SQL에서는 하나의 SQL 구문이 atomic하다.
- 모든 트랜잭션은 COMMIT 또는 ROLLBACK 구문으로 끝을 명시해야 함.
- Transaction isolation levels:
  ![](https://user-images.githubusercontent.com/6410412/244058337-79be4ff0-6af3-487f-af62-ef93eacf44df.png)
  - 트랜잭션의 격리 수준을 설정할 수 있음.
  - dirty write는 어떠한 격리 수준도 허용하지 않음.
  - SERIALIZABLE은 가장 높은 격리 수준, SELECT 쿼리만 실행해도 데이터에 락이 걸림.
- Drity read: 다른 트랜잭션에서 아직 커밋되지 않은 값을 읽을 수 있음.
- Nonrepeatable raed: 한 트랜잭션에서 여러 번 read했을 때 모두 다른 값을 읽을 수 있음.
- Phantom read: nonrepeatable의 일종, 여러 번 read했을 때 값이 없었다가 생기거나, 있었다가 없어질 수 있음.

## Concurrency Control

- 트랜잭션 매니저와 락 매니저가 동시성 컨트롤 담당.
- 동시성 컨트롤의 목적:
  - 트랜잭션 사이 isolation을 강제.
  - RW, WW conflicts를 해결.
  - 시스템의 consistency를 유지.

### Locking Basics

#### Binary Locks

- 각 트랜잭션은 데이터를 읽거나 쓰기 전에 락을 얻어야 한다.
- 락을 통해 스케줄러는 conflict-serializability를 보장할 수 있다.
- 두 가지 atomic opertaions: `lock(x)`, `unlock(x)`
- 읽기, 쓰기 전에 아이템 `x`에 락을 걸고, 이후에는 락을 해제한다.
- 이미 아이템 `x`가 락을 점유하고 있다면 대기한다.
- RW, WW conflicts는 방지할 수 있음.

```
    lock_itme(x):
B:    if LOCK(x) = 0
        then LOCK(x) ← 1
      else
        begin
        wait (until LOCK(x) == 0
          and the lock manager wakes up the transaction);
        goto B
        end;
```

```
unlock_itme(x):
  LOCK(x) ← 0
  if any transactions are waiting
    wakeup one of the waiting transactions;
```

- 트랜잭션은 read(x) 또는 write(x) 전에 반드시 lock_item(x)를 해야 함.
- read(x) 또는 write(x)를 마치면 unlock_item(x)을 해야 함.
- 이미 x에 락이 걸려있으면 lock_item(x)을 할 수 없으므로 락 매니저가 깨울 때까지 대기한다.

#### Shared / Exclusive Locks

- 애초에 RR에는 conflict가 발생하지 않는데 이때도 락이 필요할까?
- 읽기용, 쓰기용 락을 분리하자.
- Shared (read lock):
  - 여러 아이템이 read lock을 획득할 수 있음.
  - 누군가 write lock을 점유하고 있으면 획득할 수 없음.
  - reader가 몇 개인지 저장해두고, unlock할 때 0이 되면 대기 중인 트랜잭션을 깨운다.
- Exclusive (write lock):
  - 누군가 write lock을 점유하고 있으면 획득할 수 없음.
  - 누군가 read lock을 점유하고 있으면 획득할 수 없음.
- linked list 형태로 lock table을 관리한다.

```
    read_lock(x):
B:    if LOCK(x) = "unlocked"
        then begin LOCK(x) ← "read-locked"
          no_of_reads(x) ← 1
        end
      else if LOCK(x) = "read-locked"
        then no_of_reads(x) ← no_of_reads(x) + 1
      else begin
        wait (until LOCK(x) = "unlocked"
          and the lock manager wakes up the transaction);
        goto B
        end;
```

```
    write_lock(x):
B:    if LOCK(x) = "unlocked"
        then LOCK(x) ← "write-locked"
      else begin
        wait (until LOCK(x) = "unlocked"
          and the lock manager wakes up the transaction);
        goto B
        end;
```

```
unlock(x):
  if LOCK(x) = "write-locked"
      then begin LOCK(x) ← "unlocked";
        wakeup one of the waiting transactions, if any
        end
  else if LOCK(x) = "read-locked"
    then begin
      no_of_reads(x) ← no_of_reads - 1;
      if no_of_reads(x) = 0
        then begin LOCK(x) = "unlocked";
          wakeup one of the waiting transactions, if any
          end
      end;
```

### Two-Phase Locking

![](https://user-images.githubusercontent.com/6410412/244058362-9eee33fc-a80f-4e94-b737-9240afe818bd.png)

- 앞서 shared / exclusive locks를 나이브하게 쓰면 값이 최신인지 보장할 수가 없음.
- 두 개의 mutually exclusive한 phase가 있어야 함:
  - 2PL에는 growing phase와 shringking phase가 있다.
  - growing phase: 락을 얻기만 한다.
  - shrinking phase: 락을 해제하기만 한다.
- 데드락 문제가 발생할 수 있음.
- Strict 2PL:
  - 트랜잭션이 종료된 이후에 사용한 모든 락을 해제하는 방식.
  - 2PL 알고리즘에 주로 사용.
  - 데드락의 가능성이 있음.
- Conservative 2PL:
  - 트랜잭션이 시작하기 전에 필요한 모든 락을 획득, 종료 후에 사용한 모든 락을 해제하는 방식.
  - 데드락 문제가 없음.
  - 데드락이 예상되면 트랜잭션 시작이 지연되기 때문에 동시성이 저해될 수 있음.
- 데드락을 어떻게 해결할 것인가?
  - Prevention:
    - 트랜잭션 시작 전에 모든 아이템을 락한다.
    - 트랜잭션이 대기하지 않게 되므로 데드락을 방지할 수 있음.
    - Conservative 2PL의 접근법.
  - Detection:
    - wait-for graph, 타임아웃.
    - 이때 영원히 대기만 하는 starvation problem이 발생할 수 있음.
    - priority 기반 스케줄링 메커니즘에 내재된 문제, 우선순위 조정 필요.

### Timestamp-Based Protocol

- 트랜잭션이 시스템에 들어올 때 타임스탬프를 발급한다.
  - 트랜잭션 $T_i$는 타임스탬프 $TS(T_i)$를 갖는다.
  - 타임스탬프가 강하게 단조 증가한다는 전제.
- 타임스탬프는 serializability order를 결정한다.
- 각 데이터 Q는 두 개의 타임스탬프 값을 갖는다:
  - W-timestamp(Q): 가장 최근에 성공한 쓰기 타임스탬프.
  - R-timestamp(Q): 가장 최근에 성공한 읽기 타임스탬프.
- $T_i$가 read(Q)를 하는 경우:
  - $TS(T_i)$ < W-timestamp(Q):
    - Q가 다른 트랜잭션에 의해 덮어씌워졌을 것.
    - read(Q)를 리젝하고, $T_i$를 롤백한다.
  - $TS(T_i)$ >= W-timestamp(Q): read(Q)를 실행하고, R-timestamp(Q)를 갱신.
- $T_i$가 write(Q)를 하는 경우:
  - $TS(T_i)$ < R-timestamp(Q):
    - 다른 트랜잭션에서 dirty read가 일어났을 가능성.
    - write(Q)를 리젝하고, $T_i$를 롤백한다.
  - $TS(T_i)$ < W-timestamp(Q):
    - 다른 트랜잭션이 작성한 최신 값을 덮어쓸 가능성.
    - write(Q)를 리젝하고, $T_i$를 롤백한다.
  - 그 외: write(Q)를 실행하고, W-timestamp(Q)를 갱신.

## NoSQL

- 데이터 준비(ETL):
  1. Extract: 소스(파일, DB, 로그 등)에서 데이터를 추출.
  1. Transform: 데이터를 변환.
  1. Load: 싱크(Python, R, SQLite, RDBMS 등)로 데이터 적재.
- Tabular Data: 로우와 컬럼의 집합으로 구성된 데이터 포맷 (e.g., Excel, CSV)
- XML: 인간과 기계가 모두 읽을 수 있는 데이터 포맷.
- JSON:
  - self-describing 스키마.
  - Relational model과 달리 nested arrays 구조.
  - XML과 달리 타입이 있고 단순함.
- NoSQL:
  - RDBMS 원칙을 따르지 않는 모든 데이터베이스를 가리키는 용어.
  - Non-SQL (or No RDBMS), Not Only SQL.
  - 주로 unstructured large-scale 데이터를 다루는 데이터베이스.
- Non-relational DBMS는 새로운 개념이 아님:
  - 분산, 병렬 컴퓨팅 환경에서 확장 가능한 애플리케이션을 만들기 위한 시도.
  - 구글 파일 시스템(2003), MapReduce(2004)가 있었고, 이후 Hadoop, Dynamo가 등장.
- NoSQL은 빅데이터와 관련되어 언급된다:
  - 엄청나게 많은 데이터를 분산, 병렬 처리해야 해야 한다.
  - 변화하는 비정형 데이터를 관리하는 것은 어려운 일임.
  - fault tolerance와 backup 외에도 효율적으로 데이터를 관리해야 함.
- Brewer's CAP Theorem:
  - Consistency: 모든 클라이언트가 최신 데이터를 받을 수 있음.
  - Availability: 각 요청이 항상 응답을 받을 수 있음.
  - Partition-Tolerance: 노드간 네트워크 단절에도 시스템을 유지할 수 있음.
  - 분산 데이터 스토어는 이 중 하나를 희생할 수 밖에 없다:
    - CA: RDBMS
    - AP: DynamoDB, CouchDB, Cassandra
    - CP: MongoDB, HBase, Redis
- KV store, Document store, Wide column store, Graph store 등.

## MapReduce and Hadoop

- 무엇을 빅데이터라고 하는가?
- 3V of Big Data:
  - Volume: 일단 양이 많음.
  - Variety: 다양한 종류와 형식.
  - Velocity: 리얼타임, 스트리밍 (e.g., 지진 일어나면 경보보다 지진희 갤러리가 먼저 반응함.)
- 4V of Big Data: 3V + Veracity (불확실성, 신뢰성)
- 5V of Big Data: 4V + Value (영향력, 실용성)
- 데이터 분석:
  - inspecting, cleansing, transforming, modeling 과정.
  - descriptive(현재), predictive(미래), prescriptive(액션플랜)
- 데이터 마이닝: 데이터에서 중요한 패턴과 지식을 추출.
- Scale-up(vertical) vs Scale-out(horizontal):
  - Scale-up:
    - 리소스를 추가해 컴퓨팅 capacity를 높이는 것.
    - 캐파가 늘수록 비용은 지수 증가.
    - 노드 레벨 성능에 제한이 있을 때. (e.g., 데이터를 나눠 분산 저장할 수 없을 때)
    - 반복적으로 증가하는 워크로드를 다룰 때.
    - 작은 데이터셋을 구성할 때.
    - 향후 3-5년간 데이터셋이 증가하지 않을 때.
  - Scale-out:
    - 아키텍처에 capacity를 추가하는 것.
    - 캐파가 늘수록 비용은 선형 증가.
    - 여러 저장소 노드에 워크로드를 분산해야 할 때.
    - 지속적인 데이터의 증가가 예상될 때.
- Hadoop:
  - 데이터 저장소(S3, CouchDB)와 프로세싱(Spark, EC2) 영역에 해당.
  - 방대한 데이터는 싱글 노드로 모두 처리할 수 없다.
  - 노드가 죽어도 영속적으로 데이터를 저장하려면 분산 파일 시스템을 사용해야.
  - Hadoop Distributed File System (HDFS):
    - 고대역폭, 고가용성 분산 스토리지.
    - NameNode-DataNode로 구성된 Master-Slave 아키텍처.
    - NameNode는 적어도 하나의 레플리카를 다른 랙에 저장한다.
  - Hadoop MapReduce:
    - 분산 빅데이터 처리 인프라.
    - 데이터 파티셔닝, 프로그램 스케줄링 등.
    - MapReduce Paradigm: Map 함수와 Reduce 함수로 데이터를 처리.
    - Map: 리스트의 모든 요소에 함수를 적용. 추출.
    - Reduce: 리스트의 모든 요소를 합침. 집계.
    - 프로그래머가 Map 함수와 Reduce 함수만 작성하면 원하는 처리가 가능.
    - 만약 R, S 테이블을 조인하고 싶다면:
      1. R(a, b)를 (b, (a, R))로 매핑.
      1. S(b, c)를 (b, (c, S))로 매핑.
      1. 하둡이 자동으로 Reduce 프로세스 실행.
      1. b를 기준으로 조인해 (a, b, c) 반환.
- Hive:
  - HDFS에 저장된 방대한 데이터를 쿼리하기 위한 데이터 웨어하우스 시스템.
  - 하이브에 SQL-like 쿼리를 보내면 Hive가 MapReduce 태스크를 실행해 하둡에 전송.
  - 장점: 대량 데이터 처리가 쉽고, SQL 기반 쿼리 가능.
  - 단점: 데이터를 추가하기 어렵고, HDFS의 파일이 이뮤터블함.

## MongoDB

- Document stores: self-describing, hierarchical tree data structures, XML, JSON 등.
- 전통적인 relational model보다 유연하다.
- MongoDB: Hash-based, scheme-less database.
- JSON은 사실 전송에 적합, 그래서 빠르고 저장에 적합한 BSON(Binary JSON)을 사용.
- 인덱스를 알아서 잡아준다, 샤딩도 알아서 해줌.
