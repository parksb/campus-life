# Introduction to Database

- 미니월드: 데이터베이스에 저장된 데이터에 관한 리얼월드의 일부분.
- DBMS: 데이터베이스를 관리, 생성하기 위한 소프트웨어 시스템.
- 데이터베이스 시스템:
- 데이터베이스를 정의한다는 것은 데이터의 타입과 구조, 제약을 정의하는 것.
- 메타데이터: 데이터베이스 정의 또는 descriptive information.

## Simplified Database System

## Characteristics of the Database Approach

- Self-describing nature of a database system:
  - 데이터베이스 시스템은 구조와 제약에 대한 완전한 정의를 포함하고 있다.
  - 메타데이터는 데이터베이스의 구조를 설명한다. (NOSQL의 경우 메타데이터가 불필요함.)
  - 데이터베이스 카탈로그는 DBMS 소프트웨어에 사용된다.
- Insulation between programs and data:
  - Program-data independence: 데이터를 바꿔도 프로그램을 다시 작성할 필요가 없다.
  - Program-operation independence: 명령은 두 부분(인터페이스와 구현)으로 나뉜다.
- Support of multiple views of the data:
  - 뷰는 데이터베이스의 서브셋.
- Sharing of data and multiuser transaction processing:
  - 여러 유저가 데이터베이스에 동시 접근할 수 있다.

# Database System concepts and Architecture

- 데이터 모델: 구조 + 명령 + 제약으로 이뤄진 추상 모델.
  - Conceptual (high-level, semantic) data models
  - Physical (low-level, internal) data models
  - Implementation (representational) data models
  - Self-describing data models: 데이터에 대한 정의와 값이 합쳐진 모델. (e.g., XML, KV Stores, NOSQL, etc.)

## Schemas and Instances

- Schema: 데이터베이스의 구조와 제약, 데이터 타입에 대한 설명.
- Instance: 데이터베이스의 개별 요소. (e.g., record instance, table instance, entity instance)
- State: 데이터베이스에 저장된 실제 데이터에 대한 특정 시점의 스냅샷.
- 스키마는 거의 바뀌지 않지만, 스테이트는 수시로 변경될 수 있다.

## Three-schema Architecture

- DBMS 스키마를 3개 계층으로 정의할 수 있음.
- Internal schema
- Conceptual schema
- External schema

## DBMS Languages

- Data Definition Language (DDL)
- Data Manipulation Language (DML)
- Storage Definition Language (SDL)
- View Definition Language (VDL)

## DBMS Architectures

- Physical centralized architecture
- Logical two-tier client/server architecture
- Logical three-tier client/server architecture

# Data Modeling Using E-R Model

- 아래와 같은 과정으로 모델링:
  ![](https://user-images.githubusercontent.com/6410412/229670315-de5a73e6-3c01-44b8-ad99-68afa05eb442.png)
  1. 미니월드의 요구사항을 수집, 분석해 데이터 요구사항을 얻는다.
  2. 요구사항을 바탕으로 개념적 설계를 해 모델을 만든다: ER Diagram
  3. 개념적 모델을 기반으로 논리적 모델을 만든다: Relational Model
  4. DB를 구현해 데이터베이스를 구축한다.
- Entity: 데이터베이스에 표현되는 미니월드의 특정개체.
- Attribute: 엔티티를 묘사하는 속성.
    - Simple: 원자적 값을 가진 속성.
    - Composite: 여러 속성들로 구성된 속성.
    - Multi-valued: 여러 값을 가진 속성.
- Entity type: 같은 기본 속성들로 그룹핑되거나, 하나의 엔티티 타입으로 타이핑되는 엔티티. (e.g., EMPLOYEE, PROJECT)
- Key attribute: 엔티티 타입의 속성은 각 엔티티에 대해 고유한 값을 가져야 한다. (e.g., SSN of EMPLOYEE)
    - 복합 키를 만들 수 있음. (e.g., 차량번호는 번호와 지역으로 구성)
    - 여러 키를 가질 수 있음. (e.g., CAR는 차량등록번호와 차량번호)

## E-R Diagram

## Relationship

- 2개 이상의 엔티티 사이의 관계에 구체적인 의미를 갖는 것.
- Relationship type
- Recursive relationship type
- Cardinality of Relationships:
  - One-to-one (1:1)
  - One-to-many (1:N) or Many-to-one (N:1)
  - Many-to-many (M:N)
- Participation Constraints:
  - Total
  - Partial

## Weak Entity Types

# Relational Data Model

- Schema of Relation $R$: $R(A_1, A_2, \cdots, A_n)$
  - e.g., `STUDENT(Id, Name, Dept)`
- Tuple: 순서있는 집합.
  - e.g., `<202300001, "Park", "Media">`
  - relation은 각 튜플의 집합이다.

## Constraints

- Domain constraints
- Key integrity constraints
- Entity integrity constraints
- Referential integrity constraints

## Update Operations

- 데이터 업데이트 시에 integrity constraints를 위반해서는 안 된다.
- CASCADE, SET NULL, SET DEFAULT와 같은 트리거를 설정할 수 있다.
- INSERT:
  - Domain:
    - 새 튜플의 값이 어트리뷰트의 도메인에 포함되지 않은 경우.
    - 애플리케이션 코드에서 확인이 필요함.
  - Key: 같은 키 속성을 가진 튜플이 이미 존재하는 경우.
  - Referential: 새 튜플이 참조하는 외래키가 존재하지 않는 경우.
  - Entity: 새 튜플의 주요키가 null인 경우.
- DELETE:
  - 다른 튜플이 삭제하려는 값의 주요키를 참조하는 경우.

# SQL

- 관계형 모델의 관계, 튜플, 속성이 테이블, 행, 열로 대응.
- 각 구문 마지막에는 세미콜론이 있어야 한다. (중간고사에 세미콜론 꼭 써야 함.)
- 테이블 생성: `CREATE TABLE COMPANY.EMPLOYEE` 또는 `CREATE TABLE COMPANY`

## Basic Constraints

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

## Basic Retrieval Queries

- 기본형은 `SELECT <attribute list> FROM <table list> WHERE <condition>;`.
- 'Research' 부서에서 일하는 모든 직원의 이름과 주소를 찾는 경우:
  - `FROM EMPLOYEE, DEPARTMENT` 쿼리는 두 테이블 사이 모든 쌍이 포함된 테이블을 만듦.
    ```sql
    SELECT Fname, Lname, Address
    FROM EMPLOYEE E, DEPARTMENT D
    WHERE D.Dname='Research' AND D.Dnumber=E.Dno;
    ```
  - 따라서 `WHERE`절이 필수.

# More SQL

## Use of `NOT EXISTS`

- 5번 부서의 모든 프로젝트에 참여하는 직원의 이름을 찾는 경우:
  ```sql
  SELECT Fname, Lname
  FROM Employee
  WHERE NOT EXISTS (
    (SELECT Pnumber FROM PROJECT WHERE Dno=5)
      EXCEPT (SELECT Pno FROM WORKS_ON WHERE Ssn=ESsn)
  );
  ```
- 5번 부서의 모든 프로젝트에서 개별 직원이 참여하는 프로젝트 목록을 뺐을 때, 남는 프로젝트가 없다면 해당 직원은 5번 부서의 모든 프로젝트에 참여하고 있다고 할 수 있음.

## SQL Joins

![](https://user-images.githubusercontent.com/6410412/229053775-944ef5a5-61e3-4cda-940e-7f5a569311b8.png)

- `INNER JOIN`:
  - `SELECT * FROM EMPLOYEE E INNER JOIN DEPENDENT D ON (E.Ssn = D.Essn);`
  - DEPENDENT가 있는 모든 EMPLOYEE를 반환.
  - 비교하는 속성 이름이 같다면 `NATURAL JOIN`을 할 수 있다.
- `FULL OUTER JOIN`
- `LEFT OUTER JOIN`
  - `SELECT * FROM EMPLOYEE E LEFT JOIN DEPENDENT D ON (E.Ssn = D.Essn);`
  - DEPENDENT가 없는 직원까지 포함해 반환.
- `RIGHT OUTER JOIN`

## Aggregate Functions

- `COUNT`, `SUM`, `MAX`, `MIN`, `AVG` 등 함수로 여러 튜플을 하나로 요약할 수 있다.
- `SELECT Dno, COUNT(*), AVG(Salary) FROM EMPLOYEE GROUP BY Dno;`
  - 그루핑의 조건(`Dno`)을 함께 선택해야 어떤 튜플이 어떤 조건에 속하는지 알 수 있음.
