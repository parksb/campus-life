# 데이터베이스

## Introduction to Database

- 미니월드: 데이터베이스에 저장된 데이터에 관한 리얼월드의 일부분.
- DBMS: 데이터베이스를 관리, 생성하기 위한 소프트웨어 시스템.
- 데이터베이스를 정의한다는 것은 데이터의 타입과 구조, 제약을 정의하는 것.
- 메타데이터: 데이터베이스 정의 또는 descriptive information.

### Simplified Database System

![](https://user-images.githubusercontent.com/6410412/229702076-9c695974-ffcc-45e4-b91f-3f86a43904fc.png)

### Characteristics of the Database Approach

- Traditional file processing vs Database approach:
  - 전통적 파일 처리는 각 사용자가 특정 애플리케이션에 필요한 파일을 정의하고 구현함.
  - 데이터베이스는 하나의 저장소가 한 번 정의된 데이터를 관리하고, 다양한 유저가 데이터에 접근함.
- Self-describing nature of a database system:
  - 데이터베이스 시스템은 구조와 제약에 대한 완전한 정의를 포함하고 있다.
  - 메타데이터는 데이터베이스의 구조를 설명한다. (NOSQL의 경우 메타데이터가 불필요함.)
  - 데이터베이스 카탈로그는 DBMS나 데이터베이스 구조에 대한 정보를 필요로하는 유저가 사용한다.
- Insulation between programs and data:
  - Program-data independence: 데이터를 바꿔도 프로그램을 다시 작성할 필요가 없다.
  - Program-operation independence: 명령은 두 부분(인터페이스와 구현)으로 나뉜다. 인터페이스는 명령의 이름과 인자의 데이터타입을 포함한다. 구현은 인터페이스에 영향을 미치지 않고 수정될 수 있다.
- Support of multiple views of the data:
  - 뷰는 데이터베이스의 서브셋, 데이터베이스로부터 유도되지만 명시적으로 저장되지는 않는 가상 데이터를 포함.
- Sharing of data and multiuser transaction processing:
  - 여러 유저가 데이터베이스에 동시 접근할 수 있게 해준다.
  - 동시성 제어, 트랜잭션(isolation, atomic)

## Database System concepts and Architecture

- 데이터 모델: 구조(Structures) + 명령(Operation) + 제약(Constraints)으로 이뤄진 추상 모델.
  - Conceptual(high-level, semantic): 사용자가 데이터를 인식하는 것과 같은 개념 제공.
  - Physical(low-level, internal): 데이터를 어떻게 저장할지에 대한 디테일한 개념 제공.
  - Implementation (representational) data models
  - Self-describing data models: 데이터에 대한 정의와 값이 합쳐진 모델. (e.g., XML, KV Stores, NOSQL, etc.)

### Schemas, Instances and States

- Schema: 데이터베이스의 구조와 제약, 데이터 타입에 대한 설명.
- Instance: 데이터베이스의 개별 요소를 가리키는 용어. (e.g., record instance, table instance, entity instance)
- State: 특정 시점의 데이터베이스에 저장된 실제 데이터. 즉, 데이터베이스의 스냅샷.
- 스키마는 거의 바뀌지 않지만, 스테이트는 수시로 변경될 수 있다.
- 스키마는 intension, 스테이트는 extension이라고도 부른다.

### Three-schema Architecture

![](https://user-images.githubusercontent.com/6410412/229702415-e9ea7b7e-e9cc-4bd6-a771-686b3588d7f8.png)

- DBMS 스키마를 3개 계층으로 정의할 수 있음.
- Internal schema: 물리적 스토리지 구조와 접근 경로를 정의하는 스키마 (e.g., 인덱스)
- Conceptual schema: 전체 데이터베이스 구조와 제약을 정의하는 스키마.
- External schema: 데이터베이스의 모든 데이터를 제공할 필요가 없는 경우 일부를 뷰로 제공하는 스키마. 보통 conceptual schema와 같은 데이터 모델을 사용.
- 다른 레벨 사이의 의존성을 분리하는 것을 data independence라고 한다:
  - Logical Data Independence: external schema를 변경하지 않고 conceptual schema를 변경할 수 있어야 한다.
  - Physical Data Independence: conceptual shema를 변경하지 않고 internal schema를 변경할 수 있어야 한다.

### DBMS Languages

- Data Definition Language (DDL): conceptual schema를 정의하기 위해 사용하는 언어. 많은 DBMS가 internal/external schema도 정의할 수 있도록 지원.
  - 어떤 DBMS는 internal schema에는 Storage Definition Language (SDL), external schema에는 View Definition Language (VDL)를 사용하도록 분리하기도.
- Data Manipulation Language (DML): 데이터를 조회, 변경하기 위해 사용하는 언어. 범용 언어를 임베드하여 사용할 수도 있음.
  - 하이레벨, 비절차적 DML로 SQL이 있음. declarative language라고도 한다.

### DBMS Architectures

### Physical centralized architecture

![](https://user-images.githubusercontent.com/6410412/229706095-e026beb9-82ea-4d10-85f1-a616bc4bc425.png)

### Logical two-tier client/server architecture

![](https://user-images.githubusercontent.com/6410412/229706162-de7f9f3e-a84f-4238-9db4-9ffd01b8335f.png)

- 클라이언트에게 쿼리와 트랜잭션 서비스를 제공.
- 클라이언트 애플리케이션은 서버 데이터베이스에 접근하기 위한 API(e.g., ODBC, JDBC)를 사용할 수 있음.

### Logical three-tier client/server architecture

![](https://user-images.githubusercontent.com/6410412/229706222-22a686e7-a4ef-4407-aed3-a72454cf427e.png)

- 웹 애플리케이션을 위한 일반적인 아키텍처.
- 웹 서버를 통해서만 데이터베이스에 접근할 수 있으므로 보안을 향상시킬 수 있음.

## Data Modeling Using E-R Model

- 아래와 같은 과정으로 모델링:
  ![](https://user-images.githubusercontent.com/6410412/229670315-de5a73e6-3c01-44b8-ad99-68afa05eb442.png)
  1. 미니월드의 요구사항을 수집, 분석해 데이터 요구사항을 얻는다.
  2. 요구사항을 바탕으로 개념적 설계를 해 모델을 만든다: ER Diagram
  3. 개념적 모델을 기반으로 논리적 모델을 만든다: Relational Model
  4. DB를 구현해 데이터베이스를 구축한다.
- Entity: 데이터베이스에 표현되는 미니월드의 특정 개체.
- Attribute: 엔티티를 묘사하는 속성.
    - Simple: 원자적 값을 가진 속성.
    - Composite: 여러 속성들로 구성된 속성.
    - Multi-valued: 여러 값을 가진 속성.
- Entity type: 같은 기본 속성들로 그룹핑되거나, 하나의 엔티티 타입으로 타이핑되는 엔티티. (e.g., EMPLOYEE, PROJECT)
- Key attribute: 엔티티 타입의 속성은 각 엔티티에 대해 고유한 값을 가져야 한다. (e.g., SSN of EMPLOYEE)
    - 복합 키를 만들 수 있음. (e.g., 차량번호는 번호와 지역으로 구성)
    - 여러 키를 가질 수 있음. (e.g., CAR는 차량등록번호와 차량번호)

### E-R Diagram

![](https://user-images.githubusercontent.com/6410412/229708819-c913d251-3cd5-4dae-b698-3d437a6c8aba.png)

- Employee는 EID, Department는 DID처럼 중복되는 이름을 피하면 구분이 편함.
- ER 다이어그램에서 여러 어트리뷰트로 묶인 키를 표현하려면 어떻게?
  - relational model에서 복합키를 pkey로 쓰는건 특수한 상황. ER 모델에서 여러 어트리뷰트를 묶어서 키로 표현할 필요가 없다.
- 왜 weak entity가 필요한가? 그냥 임의의 ID를 주면 되는데?
  - 실제로 대부분의 경우 그냥 ID를 줌. ID가 있는 엔티티는 중요하다는 것. 명시적으로 weak entity로 만들면 스키마만 보고도 그 엔티티 자체로는 의미가 없다는 것을 보여줄 수 있다.
- Relational 모델에서 여러 어트리뷰트에 underline하는 건 그 어트리뷰트들의 묶음이 하나의 pkey라는 의미, ER 다이어그램에서 여러 어트리뷰트에 underline하는 건 개별 어트리뷰트 하나 하나가 유니크한 key라는 의미. superkey는 relational model에만 존재하는 개념이다.

### Relationship

- 2개 이상의 엔티티 사이의 관계에 구체적인 의미를 갖는 것.
- Relationship type:
  - 관계의 이름과 참여하는 엔티티 타입.
  - 특정 관계 제약을 명시해야 한다 (e.g., 1:1, 1:N, etc.)
- Recursive relationship type
- Cardinality of Relationships:
  - One-to-one (1:1): A와 B가 일대일 대응.
  - One-to-many (1:N) or Many-to-one (N:1): A 하나에 여러 개의 B가 대응.
  - Many-to-many (M:N): 여러 개의 A에 여러 개의 B가 대응.
- Participation Constraints:
  - Total
  - Partial

### Weak Entity Types

- 키가 없는 엔티티.
- 반드시 indentifying relationship type에 참여해야한다.
- 엔티티는 weak entity type의 부분키(partial key)와 identifying relationship type에 관계된 특정 엔티티의 조합으로 식별된다.

## Relational Data Model

- Schema $R$: $R(A_1, A_2, \cdots, A_n)$
  - e.g., `STUDENT(Id, Name, Dept)`
- Tuple: 순서있는 집합.
  - e.g., `<202300001, "Park", "Media">`
  - relation은 각 튜플의 집합이다.
  - 튜플의 모든 값은 atomic하다.
  - null 값은 unknown, not available, inapplicable, undefined를 의미한다.
- Key: 테이블의 로우를 유일하게 식별 가능하게 하는 값.
- Domain: 논리적 정의와 데이터 타입 또는 형식을 갖는다.
- State: 어트리뷰트의 도메인에 대한 cartesian product의 서브셋.
  - relation state $r(R) \in dom(A_1) \times dom(A_2)$
  - state의 도메인은 cartesian product의 결과. 즉, 조합 가능한 모든 경우.
- 스키마의 어트리뷰트를 표현할 때는 순서가 중요.
  - $R(A_1, A_2, \cdots, A_n)$의 값은 $t_i = <v_1, v_2, \cdots, v_n>$.
  - 이걸 신경쓰지 않아도 되는 표현은 self-describing이라고 한다. (e.g., XML, JSON)
  - row의 순서는 중요하지 않다.

### Constraints

- constraints에는 3가지 주요 타입이 있음:
  - Inherent or Implicit Constraints:
    - 데이터 모델 자체에 기반하는 제약.
    - e.g., 관계형 모델은 리스트를 값으로 취급하지 않음.
  - Schema-based or Explicit Constraints:
    - 모델로부터 제공되는 제약.
    - e.g., ER 모델의 max cardinality ratio 제약
  - Application based or Semantic Constraints:
    - 애플리케이션 프로그램으로부터 제공되는 제약.
    - 종종 SQL의 assertions로 명시되기도 한다.
- explicit constraints에 3가지 주요 타입이 있음:
  - Key constraints:
    - pkey는 중복되어서는 안 된다.
    - Superkey: 여러 어트리뷰트의 집합으로 이뤄진 키.
    - Key: 최소한의 superkey. key는 superkey이지만, 그 반대는 아니다.
    - Primary key: 여러 후보키가 있을 때, 그 중 하나를 pkey로 사용.
  - Entity integrity constraints:
    - 각 relation schema의 pkey는 null이 될 수 없다.
    - entity를 식별할 수 있어야 한다는 제약이기 때문에 entity constraint.
  - Referential integrity constraints:
    - $R_1$에 있는 튜플의 fkey는 $R_2$에 실제 존재하는 튜플의 pkey를 참조해야 한다.
    - Foreign key: fkey는 자신이 참조하는 pkey와 같은 도메인이어야 한다.
- 또 다른 schema-based constraint는 Domain constraints.

### Update Operations

- 데이터 업데이트 시에 integrity constraints를 위반해서는 안 된다.
- CASCADE, SET NULL, SET DEFAULT와 같은 트리거를 설정할 수 있다.
- INSERT는 모든 제약을 위반할 가능성이 있음:
  - domain:
    - 새 튜플의 값이 어트리뷰트의 도메인에 포함되지 않은 경우.
    - 애플리케이션 코드에서 확인이 필요함.
  - key: 같은 키 속성을 가진 튜플이 이미 존재하는 경우.
  - referential: 새 튜플이 참조하는 외래키가 존재하지 않는 경우.
  - entity: 새 튜플의 주요키가 null인 경우.
- DELETE:
  - referential: 다른 튜플이 삭제하려는 값의 주요키를 참조하는 경우.
- UPDATE:
  - pkey를 변경하는 경우에는 모든 제약을 위반할 수 있다.
  - referential: fkey를 변경하는 경우.
  - domain: 일반적인 어트리뷰트를 변경하는 경우.

## SQL

- 관계형 모델의 관계, 튜플, 속성이 테이블, 행, 열로 대응.
- 각 구문 마지막에는 세미콜론이 있어야 한다. (중간고사에 세미콜론 꼭 써야 함.)
- 테이블 생성: `CREATE TABLE COMPANY.EMPLOYEE` 또는 `CREATE TABLE COMPANY`

### Specifying Constraints

- Key constraints: pkey 값은 중복될 수 없다.
- Entity integrity constraint: pkey 값은 null이 될 수 없다.
- Referential integrity constraint: fkey는 pkey로 표현되는 기존 값이거나, null이어야 한다.
- `CONSTRAINT` 구문으로 constraint에 이름을 붙일수도 있음:
  ```sql
  CREATE TABLE EMPLOYEE(
    Ssn CHAR(9) NOT NULL,
    ...
    CONSTRAINT EMPPK
      PRIMARY KEY (Ssn),
    CONSTRAINT EMPSUPERFK
      FOREIGN KEY (Super_ssn) REFERENCES EMPLOYEE(Ssn)
        ON DELETE SET NULL
        ON UPDATE CASCADE
  );
  ```
- 테이블을 생성하는 시점에 아직 없는 값을 fkey로 참조하면 referential integrity constraint를 위반하는 문제가 생김. 테이블을 생성한 뒤, `ALTER TABLE`해 fkey를 추가하면 된다.

### Basic Retrieval Queries

- 기본형은 `SELECT <attribute list> FROM <table list> WHERE <condition>;`.
- 'Research' 부서에서 일하는 모든 직원의 이름과 주소를 찾는 경우:
  - `FROM EMPLOYEE, DEPARTMENT` 쿼리는 두 테이블 사이 모든 쌍이 포함된 테이블을 만듦. 즉, `EMPLOYEE`와 `DEPARTMENT`의 cartesian product.
    ```sql
    SELECT Fname, Lname, Address
    FROM EMPLOYEE E, DEPARTMENT D
    WHERE D.Dname='Research' AND D.Dnumber=E.Dno;
    ```
  - 따라서 `WHERE`절이 필수.

## More SQL

### NULL

![](https://user-images.githubusercontent.com/6410412/233791999-fb1dada0-3288-4462-a033-4c7148ee9eb9.png)

- 위와 같이 three-valued logic에 logical connectives가 있다.
- 따라서 NULL 조건을 적용할 때는 비교 연산이 아니라 `IS` 연산을 해야한다:
  - e.g., `SELECT * FROM EMPLOYEE WHERE Pno IS NULL;`

### Nested Queries

- `WHERE` 절 안에 완성된 형태의 select-from-where 블록을 중첩시킬 수 있다.
- `IN` 명령을 이용해 튜플 집합에서 대상 튜플을 비교할 수 있음.
  ```sql
  SELECT DISTINCT Essn
  FROM WORKS_ON
  WHERE (Pno, Hours) IN (SELECT Pno, Hours
                         FROM WORKS_ON
                         WHERE Essn='123456789');
  ```
  - `DISTINCT`를 하면 중복된 값이 제거된다.
- 집합론을 기반으로 하므로 `UNION`, `INTERSECT`도 가능.
  ```sql
  (SELECT DISTINCT Pnumber
   FROM PROJECT, DEPARTMENT, EMPLOYEE
   WHERE Dnum = Dnumber AND Mgr_ssn = Ssn AND Lname = 'Smith')
   UNION
  (SELECT DISTINCT Pnumber
   FROM PROJECT, WORKS_ON, EMPLOYEE
   WHERE Pnumber = Pno AND Essn = Ssn AND Lname = 'Smith');
  ```

### Use of (`NOT`) `EXISTS`

- 5번 부서의 모든 프로젝트에 참여하는 직원의 이름을 찾는 경우:
  ```sql
  SELECT Fname, Lname
  FROM Employee
  WHERE NOT EXISTS (
    (SELECT Pnumber FROM PROJECT WHERE Dno = 5)
      EXCEPT (SELECT Pno FROM WORKS_ON WHERE Ssn = ESsn)
  );
  ```
- 5번 부서의 모든 프로젝트에서 개별 직원이 참여하는 프로젝트 목록을 뺐을 때, 남는 프로젝트가 없다면 해당 직원은 5번 부서의 모든 프로젝트에 참여하고 있다고 할 수 있음.

### SQL Joins

![](https://user-images.githubusercontent.com/6410412/229053775-944ef5a5-61e3-4cda-940e-7f5a569311b8.png)

- `INNER JOIN`:
  - `SELECT * FROM EMPLOYEE E INNER JOIN DEPENDENT D ON E.Ssn = D.Essn;`
  - DEPENDENT가 있는 모든 EMPLOYEE를 반환.
  - 비교하는 속성 이름이 같다면 `NATURAL JOIN`을 할 수 있다.
- `FULL OUTER JOIN`
- `LEFT OUTER JOIN`:
  - `SELECT * FROM EMPLOYEE E LEFT JOIN DEPENDENT D ON E.Ssn = D.Essn;`
  - DEPENDENT가 없는 직원까지 포함해 반환.
- `RIGHT OUTER JOIN`

### Aggregate Functions

- `COUNT`, `SUM`, `MAX`, `MIN`, `AVG` 등 함수로 여러 튜플을 하나로 요약할 수 있다.
- `SELECT Dno, COUNT(*), AVG(Salary) FROM EMPLOYEE GROUP BY Dno;`
  - 그루핑의 기준 컬럼(`Dno`)을 함께 선택해야 어떤 튜플이 어떤 조건에 속하는지 알 수 있음.
- 그루핑 조건은 `HAVING` 절에 작성한다:
  ```sql
  SELECT Pnumber, Pname, COUNT(*)
  FROM PROJECT, WORKS_ON
  WHERE Pnumber = Pno
  GROUP BY Pnumber, Pname
  HAVING COUNT(*) > 2;
  ```
  - 여러 개 컬럼으로 `GROUP BY`하면?
- `WHERE`는 조심해야 한다. 이미 필터링된 상태에서 그루핑을 하면 `HAVING` 조건을 만족하지 못할 수 있음:
  ```sql
  SELECT Dno, COUNT(*)
  FROM EMPLOYEE
  WHERE Salary > 40000 AND Dno IN
    (SELECT Dno FROM EMPLOYEE GROUP BY Dno HAVING COUNT(*) > 5)
  GROUP BY Dno;
  ```
- `GROUP BY`되지 않은 컬럼은 `SELECT`할 수 없다.

### Alter and Dropping

- `ALTER TALBE <table> <ADD|DROP> <column> [type] [CASCADE|RESTRICT]`: 컬럼 추가/제거.
  - `CASCADE`: 삭제할 컬럼에 있는 모든 제약과 뷰를 제거한다.
  - `RESTRICT`: 삭제할 컬럼이 제약을 위반하면 삭제를 막는다.
- `ALTER TALBE <table> ALTER COLUMN <column> <SET|DROP> DEFAULT [default]`: 디폴트 값 추가/제거.
- `DROP TABLE <table>`: 테이블 삭제.

## Relational Algebra and Relational Calculus

### Relational Algebra

- 관계형 모델에 대한 기본 명령 집합.
- 쿼리의 기본적인 구현과 최적화에 사용할 수 있음.

### Unary Relational Operations

- SELECT ($\sigma_{<condition>}(R)$):
  - SQL의 WHERE에 대응하는 명령.
  - $\sigma_{Dno = 4}(EMPLOYEE)$
  - $\sigma_{Salary > 30000}(EMPLOYEE)$
  - 교환법칙이 성립하므로 순서를 바꿔도 상관없다. 따라서 연산을 적게 하는 방향으로 명령을 구성할 수 있다.
  - AND 조건을 걸어 중첩된 $\sigma$ 명령을 하나로 작성할 수 있다.
- PROJECT ($\pi_{<attributes>}(R)$):
  - SQL의 SELECT에 대응하는 명령.
  - $\pi_{Lname, Fname, Salary}(EMPLOYEE)$
  - 결과에서 중복 튜플이 제거된다.
  - 교환법칙이 성립하지 않는다.
  - 아래첨자에 여러 속성을 나열하여 중첩된 $\pi$ 명령을 하나로 작성할 수 있다.
- Assignment ($\leftarrow$)
  - 화살표를 이용해 중간 결과값을 저장할 수 있다:
    - $DEP5\_EMPS \leftarrow \sigma_{DNO=5}(EMPLOYEE)$
    - $RESULT \leftarrow \pi_{Fname, Lname, Salary}(DEP5\_EMPS)$
- RENAME ($\rho_{S(B_1, B_2, \cdots, B_n)}(R)$)
  - 릴레이션 이름과 어트리뷰트 이름을 변경한다.
  - 둘 중 하나만 변경할 수도 있다: $\rho_S(R)$, $\rho_{B_1, B_2, \cdots, B_n}(R)$
  - 보통 대입 연산과 함께 쓰인다:
    $RESULT(F, M, L, S, B, A, SX, SAL, SU, DNO) \leftarrow \rho_{RESULT(F, M, L, S, B, A, SX, SAL, SU, DNO)}(DEP5\_EMPS)$
  - 이렇게 축약할 수도 있다: $RESULT(First\_name, Last\_name) \leftarrow \pi_{Fname, Lname}(EMPLOYEE)$


### Relational Algebra Operations From Set Theory

- UNION ($R \cup S$):
  - R, S에 존재하는 튜플을 모두 얻는다.
  - R, S 릴레이션의 타입이 서로 다르면 안 된다(type compatible).
  - 교환법칙(commutative)과 결합법칙(associative)이 성립한다.
  - 결과에서 중복된 결과는 제거된다.
- INTERSECTION ($R \cap S$):
  - R, S에 공통으로 존재하는 튜플을 얻는다.
  - R, S의 타입이 서로 다르면 안 된다.
  - 교환법칙과 결합법칙이 성립한다.
- SET DIFFERENCE ($R - S$)
  - R에서 S에 존재하는 튜플을 제외하고 얻는다.
  - R, S의 타입이 서로 다르면 안 된다.
  - 교환법칙과 결합법칙이 성립하지 않는다.

### Binary Relational Operations

- CARTESIAN PRODUCT ($R(A_1, A_2, \cdots, A_n) \times S(B_1, B_2, \cdots, B_m)$)
  - R, S 사이의 모든 튜플 조합을 얻는다.
  - 결과 Q에는 $n + m$개의 어트리뷰트가 생긴다.
  - R의 튜플 수가 $|R| = n_R$, S의 튜플 수가 $n_S$라면, $R \times S$에는 $n_R \times n_S$개의 튜플이 생긴다.
  - R, S의 타입이 서로 달라도 된다.
  - $\times$ 명령만으로는 큰 의미가 없고, 여기에 $\sigma$를 걸어야 한다.
- JOIN ($R \Join {}_{<condition>}S$):
  - 두 릴레이션을 결합해 조건을 만족하는 튜플들을 얻는다.
  - 여기서 condition을 theta라고 부른다: $R \Join {}_{theta}S$.
  - EQUI JOIN: 어트리뷰트 값이 같은 것을 기준으로 THETA JOIN하는 것.
  - NATURAL JOIN: $S \ast R$. 어트리뷰트 이름이 같은 것에 대해 EQUI JOIN 하는 것.
    - 명시적으로 조건을 걸 수도 있다: $Q \leftarrow R(A, B, C, D) \ast S(C, D, E)$.
      - EQUI JOIN과 달리 결과에서 이름이 중복되는 컬럼을 제거한다: $Q(A, B, R.C, S.C, R.D, S.D, E)$가 아닌 $Q(A, B, C, D, E)$.
    - e.g., DEPARTMENT에도 Dnumber가 있고, DEPT_LOCATION에도 Dnumber가 있다면 다음과 같이 부서별 위치를 구할 수 있다: $DPET\_LOCS \leftarrow DEPARTMENT \ast DEPT\_LOCATION$.
- DIVISION ($R(Z) \div S(X)$):
  - X가 Z의 부분집합일 때 나누기 연산을 할 수 있다.

### Additional Relational Operations

- Complete set of relational operations: SELECT, PROJECT, UION, DIFFERENCE, RENAME, CARTESIAN PRODUCT. 다른 모든 명령을 이 6개 명령으로 구성할 수 있다.
  - e.g., $R \cap S = (R \cup S) - ((R - S) \cup (S - R))$
  - e.g., $R \Join {}_{<condition>}S = \sigma_{<condition>}(R \times S)$
- LEFT/RIGHT/FULL OUTER JOIN 모두 가능:
  - OUTER JOIN은 기준 릴레이션의 모든 튜플이 포함. 매칭되지 않는 튜플의 조인된 어트리뷰트는 null로 채워짐.

### Query Tree Notation

- 쿼리를 표현하기 위한 internal data structure.
- 쿼리의 동작을 트리로 표현할 수 있다.
