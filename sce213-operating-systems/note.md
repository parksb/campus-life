# 운영체제

## Introduction to Operating Systems

### System Calls

- 폰 노이만 구조, 모드 얘기, privileged instructions.
  ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter1/1_5_HowItWorks.jpg)
- 인터럽트:
  - 인터럽트는 하드웨어 장치가 만드는 신호. 비동기적으로 발생.
  - 현대 컴퓨터는 인터럽트 주도 방식으로 동작. 인터럽트가 발생하면 모드가 전환될 수 있음.
  - 익셉션(exception):
    - 소프트웨어가 인스트럭션을 실행하다가 만드는 신호.
    - 동기적으로 발생. CPU가 인스트럭션을 실행할 때만 일어남.
    - 의도를 갖고 일으킨 익셉션은 트랩(trap).
    - 예상치 못한 익셉션은 폴트(fault)
- 시스템 콜:
  ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter2/2_06_Open.jpg)
  - 식당에서 벨 누르면 주방에서 커널모드로 일하던 사장님이 홀에 나와서 유저모드로 전환하심.
  - OS가 서비스에게 제공하는 프로그래밍 인터페이스:
    - Win32 API for Windows, POSIX API for POSIX-based systems, Java API for JVM 등.
    - OS가 제공하는 서비스는 프로그램 실행, 파일 시스템, IO, 통신, 에러 감지 등.
  - man 페이지에 다 나와있음. 궁금하면 그냥 무조건 man 페이지보세요.
  - 리눅스에 시스템 콜이 몇 개나 있을 것 같아요? 350개 정도.
  - 저는 시스템 콜 써본 적이 없는데용? 사실 다 쓰고 있음.
  - `printf`도 시스템 콜인가요? 그건 표준 C 라이브러리. 라이브러리가 `write` 시스템 콜을 호출함.
- 컴퓨터 켜면 무슨 일이 일어나나요? Bootstrap program > Bootloader > Kernel phase 1 > Kernel phase 2

### OS Structures

- 과제 질문이 많이 들어옴. 윈도우즈 시스템에서 하지 마세용.
- 운영체제를 새로 하나 만들다고 생각해보죠:
  - 절대적인 답도 없고 최고의 방법도 없음. 대충 이렇게 했더니 성공적인 운영체제가 만들어지더라.
  - 그래서 우리는 운영체제가 일반적으로 어떻게 되어있고, 성공한 운영체제는 어떻더라 같은 얘기만 할거임.
  - 기본적으로 요구사항과 목적을 달성할 수 있어야. 스펙을 잘 정의해야 한다.
    - 어떤 하드웨어로, 어떤 종류의 시스템에서, 어떤 환경에서, ...
    - 사용자: 사용하기 편하고 배우기 쉬워야, 믿을 수 있어야, 안전해야, 빨라야.
    - 시스템: 설계하기 쉬워야, 구현하기 쉬워야, 유지보수가 쉬워야, 유연해야, 오류없어야, 효율적이어야.
  - 어떻게 구현할까?
    - 초기 운영체제는 어셈블리로 작성. 그 이후로는 Algol, PL/1 사용.
    - 오늘 날에는 굉장히 많은 시스템이 C/C++로 작성됨. 시스템을 하나의 언어만으로 구현하지 않음.
    - 리눅스는 대부분 C로 작성됨. 토발즈가 C++ 안 좋아함. 저도 C++ 안 좋아해요. 언어가 지저분해.
- 운영체제의 구조:
  - 리눅스 커널은 monolithic 구조: https://makelinux.github.io/kernel/map/
    - MS-DOS 방식은 심플하지만 유지보수가 어려움. 레이어드는 유지보수 쉽지만 성능 문제.
    - 리눅스 OS의 실체는 모듈끼리 강하게 커플링되어 있는 하나의 소프트웨어 커널(kernel).
    - 성능 이점이 있지만, 레이어드보다는 유지보수가 어렵고, 보안과 안정성 측면에서 문제가 있음.
  - 그 대안이 마이크로커널:
    - 커널에는 진짜 핵심적인 것만 남기고 유저 공간에 위임. 확장 쉽고, 포팅 쉽고, 보안도 향상.
    - 다만 유저 공간과 커널 공간 통신으로 성능 오버헤드가 발생함.
    - Tanenbaum-Tovalds debase: 토발즈가 리눅스 만들고 소개하는 글을 썼는데, 타넨바움이 "요즘 세상에 무슨 모놀리식이냐, 마이크로커널이 짱이다"라면서 까는 바람에 키배가 일어남. (https://www.oreilly.com/openbook/opensources/book/appa.html)
  - 요즘 시스템은 어떤 하나의 구조라고 말하기 어려움. 하이브리드.

## Processes

- 지금까지 오버뷰 얘기만 했음. 오늘부터는 실제 운영체제 얘기를 하겠습니다.
- 프로세스는 실행된 프로그램의 인스턴스:
  - 메모리에 로드되어 활성화되어있는 동적인 엔티티.
  - 프로그램은 디스크에 저장된 정적인 엔티티.
- 각 프로세스는 메모리에서 자기만의 주소공간을 갖는다: code, data, heap, stack.
- 프로세스의 상태: new, ready, running, wait, terminated.
  ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_02_ProcessState.jpg)
- 시스템 콜을 이용한 프로세스 관리:
  ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_10_ProcessCreation.jpg)
  - `pid_t fork(void)`:
    - 루트에 init 프로세스가 있는데, 여기에 자식 프로세스를 만드는 것. 결국 하나의 트리를 이루게 됨.
    - 새 프로세스를 만드려면 당연히 커널 모드에서 해야. 따라서 시스템 콜(`fork`)을 사용해야 한다.
    - 어떤 프로세스에서 `fork()`를 하면 동일한 프로세스가 만들어짐.
    - 프로세스가 제대로 만들어지면 부모에게는 자식 프로세스의 PID를 반환, 자식에게는 0을 반환.
      - `pid_t getpid(void)`: 자신의 (진짜) PID.
      - `pid_t getppid(void)`: 부모의 PID.
    - 자식 프로세스는 `fork` 직후의 인스트럭션을 실행한다.
    - `fork`하는 시점의 메모리 섹션을 그대로 복제하므로, 변수도 `fork` 시점의 값을 갖는다.
    - 부모 프로세스와 자식 프로세스는 독립적임. 자식은 자식의 인생을 살아야 해요.
  - `exec` family:
    - 현재 프로세스의 이미지를 새 프로세스 이미지로 교체.
    - 현재 주소공간을 날리고 새로운 내용을 채운다. `exec("vi")`하면 vi를 실행하는 프로세스가 됨.
    - 여러분이 탐색기를 띄웠어요. 탐색기에서 파워포인트를 더블클릭하면 탐색기가 운영체제한테 `fork`를 날리죠. 그러면 탐색기 프로세스가 하나 더 만들어집니다. 근데 파워포인트를 실행해야하니 `exec`로 스스로를 교체.
  - `void exit(int status)`:
    - 프로세스를 삭제한다. 프로세스의 반환 값이 부모 프로세스에게 전달됨.
    - `pid_t wait(int *wstatus)`: 부모 프로세스는 `wait` 시스템 콜을 통해 자식의 반환 값을 기다림.
    - `pid_t waitpid(pid_t pid, int* status, int options)`: 특정 자식을 기다림.
    - `void abort(void)`: 특정 프로세스와 그 부모까지 삭제.
- 좀비 프로세스:
  - 자식이 삭제됐는데 부모 프로세스가 `wait`를 하지 않는다면?
  - 자식의 반환 값과 PID가 남음. 따라서 종료되었지만 삭제되지는 않은 좀비가 됨.
- 고아 프로세스:
  - 부모가 삭제된 자식 프로세스.
  - 고아 프로세스를 방지하려면:
    - 부모가 삭제될 때 그 자식도 삭제해는 cascading termination.
    - 아니면 다른 프로세스의 자식으로 만드는 reparenting. 어떤 프로세스의 자식으로 만들 것인가?
      - 옛날 시스템 중에는 부모의 부모가 입양하는 경우도 있었음.
      - 리눅스는 `init` 프로세스의 자식으로 만든다. `init`은 주기적으로 `wait`을 호출해 자식을 정리.
- 프로세스의 구현:
  - 각 프로세스는 Process Control Blcok(PCB)로 표현된다.
    ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_03_PCB.jpg)
  - 프로세스에 대한 모든 정보가 PCB에 담겨있음.
  - 상태, PC(Program Counter), PID, PPID, 레지스터, 메모리 제한, CPU 스케줄링 정보 등.
  - 리눅스에서 프로세스는 `task_struct`로 구현된다.
- IPC(Inter-Process Communication):
  - 하나의 프로그램을 여러 프로세스로 만드는게 굉장히 흔한 모델.
  - 프로세스끼리 통신을 해야 하는데...
  - 공유 메모리(shared memory):
    - 프로세스가 운영체제에게 명시적으로 공유 메모리를 요청할 수 있음: `shm_open`
    - 운영체제가 공유 메모리를 제공한 뒤에는 신경쓰지 않아도 됨.
    - 하지만 관리가 안 된다. 각종 동시성 문제가 일어남.
  - 메시지 패싱(message passing):
    - 택배. `send`, `receive`를 이용해서 프로세스간 메시지 교환을 할 수 있음.
    - 운영체제가 다 알아서 해준다. 마이크로커널이 메시지 패싱을 적극 활용. 분산환경에 좋음.
  - 시그널:
    - 강아지가 시그널을 날려요(?)
    - 프로세스에게 이벤트를 알리는 IPC 매커니즘. 동기적일수도 있고, 비동기적일수도 있음.
    - 소프트웨어 인터럽트라고 생각할수도. 시그널 핸들러가 시그널을 처리한다.
    - `sigaction`으로 어떤 시그널을 받았을 때 어떤 행동을 하라고 정의할 수 있음.
    - 시그널 핸들러도 PCB에 있음. `fork` 어떤 시그널은 복사가 되지만, 어떤 시그널은 안 됨.
  - Remote Procedure Call(RPC):
    - 로컬 기기에서만 IPC를 할 수 있을까? RPC로 원격 프로시저를 호출할 수도 있음.
    - 실제로는 stub을 사용하고, 운영체제의 RPC 레이어에서 통신을 처리해준다.
    - XDR: 범용적인 데이터 표현 형식. 시스템마다 엔디언이 다르기 때문에 RPC 데이터를 XDR로 표현.
  - 파이프:
    - 파이프로 다른 프로세스에 데이터를 밀어넣을 수 있음. 초기 UNIX 시스템의 IPC 매커니즘 중 하나.
    - 데이터가 단방향(unidirectional) 또는 양방향(bidirectional)로 흐를 수 있음.
    - 양방향 파이프에서 읽기/쓰기가 동시에 된다면 full-duplex, 그렇지 않다면 half-duplex.
      - 빨대는 마실수도 있고 뱉을 수도 있으니 양방향이죠. 하지만 마시는 동시에 불 수는 없으므로 half-duplex.
    - Ordinary pipe:
      - 부모-자식 관계에서만 통신 가능한 양방향 파이프.
      - 파일 디스크립터에 따라 읽기 파이프와 쓰기 파이프가 구분됨:
        - `pipe[1]`에 쓴 값을 `pipe[0]`에서 읽을 수 있음. 프로세스 하나에서만 쓰면 그냥 버퍼같겠지.
        - 파이프를 만들고 포크해야 재밌어짐. 파일 디스크립터를 포함해 부모의 컨텍스트가 복제된다.
        - 따라서 자식이 `pipe[1]`에 값을 쓰면 부모가 `pipe[0]`에서 읽을 수 있다. 물론 그 반대도 가능.
    - Named pipe:
      - 부모-자식 관계를 필요로하지 않는 양방향 파이프.
      - 이름이 붙여져 있기 때문에 어떤 프로세스든 파이프를 사용할 수 있음.

## Threads

- 프로세스 하나만 쓴다면 멀티코어의 이점을 누릴 수 없음.
  - 여러 프로세스를 만든다 해도, IPC하는 애플리케이션 작성이 쉽지 않음.
  - 프로세스 생성과 커뮤니케이션, 컨텍스트 스위칭에 비용이 많이 든다.
  - 더 효율적인 방법으로 동시성을 제고할 수 있을까?
- 프로그램의 실행 흐름을 따라 그려보면 하나의 실을 그리게 될 것.
  - 스레드는 실타래입니다. 만약 실타래가 여러 개가 된다면?
  - 프로세스의 실행 상태를 분리해낸다면 어떨까?
- 각 스레드는 주소공간을 공유한다
  ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter4/4_01_ThreadDiagram.jpg)
  - 스레드가 서로 공유하는 것: 코드, 전역변수, 힙, 파일
  - 각자에 속한 것: 스레드 ID, PC와 SP를 비롯한 레지스터, 스택
  - 한 프로세스는 여러 스레드를 가질 수 있고, 스레드는 하나의 프로세스에 종속됨.
- 멀티 스레딩의 장점:
  - 멀티 코어 아키텍처의 장점을 살릴 수 있다.
  - 멀티 프로세스에 비해 리소스가 덜 든다. IPC가 필요없고 그냥 주소공간에 접근하면 됨.
  - 여러 스레드가 주소공간을 공유하기 때문에 리소스 공유가 투명해짐.
  - 더 많은 I/O 연산을 처리할 수 있고, 더 많은 동시성 이벤트에 응답할 수 있음. (e.g., 웹 서버)
- 동시성(concurrency) vs 병렬성(parallelism):
  - 님들이 과제1을 풀고, 같은 시각에 친구가 과제2를 풀어주면 병렬적으로 하는거죠.
  - 님들이 과제1을 풀다가 과제2를 조금 풀고, 과제3을 풀고, 다시 과제1을 푸는게 동시성.
  - 사실 병렬성이 있으면 동시성도 가질 수 있겠죠. 동시성이 상위개념임.
  - 데이터 병렬성: 하나의 데이터셋을 쪼개서 같은 연산을 병렬적으로 수행.
  - 태스크 병렬성: 서로 다른 태스크를 병렬적으로 수행.
- 암달의 법칙:
  - 프로그램은 병렬처리 가능한 부분과 불가능한 순차적인 부분으로 나뉨.
  - 따라 아무리 열심히 병렬화를 해도 더 이상 성능이 향상되지 않는 한계가 있다.
  - 병렬화로 어디까지 향상할 수 있나? $S \le {1 \over S + {(1 - S) / N}}$
    - $S$는 순차적인 부분, $1 - S$는 병렬적인 부분. $N$은 코어수.
    - 코어가 무한히 많으면: $1 \over S$. 어쩔 수 없다.
- 멀티스레딩 모델:
  - 커널 스레드:
    - 운영체제가 직접 관리하는 스레드.
    - 커널 스레드는 운영체제가 프로세서에 태스크를 할당할 때 스케줄링의 단위.
  - 유저 스레드:
    - 유저 레벨 스레드 라이브러리에서 관리되는 스레드.
  - One-to-One 모델:
    - 하나의 커널 스레드가 하나의 유저 스레드에 대응하는 모델.
    - 스레드가 너무 많아지면 스케줄링에 너무 많은 리소스가 드는 문제.
    - 대부분의 운영체제가 커널 스레드의 수를 제한하고 있음.
  - Many-to-One 모델:
    - 하나의 커널 스레드 위에 여러 유저 스레드를 올리는 모델.
    - 유저 스레드간 컨텍스트 스위치가 가볍고 빠름. One-to-One 모델의 문제를 해결.
    - 스케줄링 단위는 커널 스레드이므로, 멀티코어 환경에서 의도한대로 유저 스레드가 병렬처리되지 않을수도.
    - 유저 스레드 중 하나가 블로킹되면 다른 스레드가 블로킹될수도.
  - Many-to-Many 모델:
    - 여러 커널 스레드가 여러 유저 스레드에 대응하는 모델.
    - Two-level 모델: 특정 유저 스레드만 커널 스레드에 일대일 대응하고, 나머지는 M:M.
    - 현실적으로 많이 쓰이지는 않음.
- 스레드 라이브러리:
  - POSIX를 잘 지키는 운영체제라면 pthread (POSIX thread)가 있다.
  - 스레드 생성과 동기화를 위한 POSIX 표준(IEEE 1003.1c)
- 암묵적 스레딩:
  - 실제로 멀티스레드 프로그래밍을 하는건 어려운 일임.
    - 물론 성능이 향상되고, 스레드를 잘 사용하는건 중요함. 하지만 인간은 멀티태스킹이 안 되는 동물.
    - 하이레벨에만 신경쓰고 싶다면 다른 방법이 필요. 암묵적 스레딩은 스레드의 생성과 반납을 추상화.
  - 스레드 풀:
    - 풀에 미리 스레드를 만들어두고, 필요할 때 풀에서 하나를 가져와 사용 후 반납.
    - 스레드의 생성과 사용이 분리되는 것. 개발자는 사용만하면 되니 편리하다.
  - Fork Join:
    - 메인 스레드에서 `fork`해서 두 개의 스레드로 분리, 각 스레드의 결과는 `join`으로 병합.
    - divide and conquer 문제를 멀티스레딩으로 해결할 때 유용.
  - OpenMP:
    - C/C++, FORTRAN 컴파일러를 똑똑하게 만들어서 멀티스레딩을 쉽게 만들자.
    - `#pragma omp parallel` 같은 디렉티브를 만나면 코어 개수만큼 스레드를 만들고 알아서 병렬 처리.
    - 공유 메모리 환경으로 병렬 프로그래밍을 지원한다.
- 멀티 스레딩의 문제들:
  - 앞서 배운 `fork`와 `exec`는 싱글코어를 상정한 것.
  - 스레드 하나에서 `fork`하면 어떻게 되나? 스레드도 다 복사되나?
    - In pthread: 호출한 스레드만 복사한다.
    - UNIX: 두 개의 시스템 콜을 제공한다.
      > A call to forkall() replicates in the child process all of the threads in the parent process.
      >
      > A call to fork1() replicates only the calling thread in the child process. (...) In  Solaris 10, a call to fork() is identical to a call to fork1(); only the calling thread is replicated in the child process. This is the POSIX-specified behavior for fork().
      - `forkall`: 부모의 모든 스레드를 자식으로 복사한다. (강의에서는 `fork`로 소개함.)
      - `fork`, `fork1`: 호출한 스레드만 복사한다.
  - `exec`는 멀티스레딩이어도 상관없죠. 어떤 스레드 하나가 `exec`하면 그냥 프로세스의 모든 스레드가 죽음.
- 시그널 핸들링:
  - 시그널이 오면 누가 받아야 하나? 시그널을 어떤 스레드가 받느냐에 따라 동작이 달라질거임.
  - 스레드마다 받을 수 있는 시그널을 명시하기. 명시하지 않으면 아무 스레드에 시그널이 간다.
- 스레드 삭제:
  - 한 스레드에서 다른 스레드를 죽이려면? 특정 스레드를 삭제하는 API가 있음.
  - Deferred cancellation:
    - 스레드를 삭제하긴 하는데, 그 스레드가 죽기전에 뭘하고 있었는지 알고싶다.
    - 즉지 죽지 않고 cancellation point에 도달할 때까지 기다리고 죽는다.
  - Asynchronous cancellation: 대상 스레드를 즉시 삭제한다.
- Thraed-Local Storage(TLS):
  - TLS 타입의 변수를 만들 수 있다.
    - 전역변수처럼 여러 스레드에서 접근할 수 있음.
    - 지역변수처럼 스레드에 종속되어 자체적인 값을 갖는다.
    - 특정 스레드에서 TLS 변수에 값을 써도 그 스레드에서만 변경된다.
  - TLS를 쓰면 동기화 오버헤드를 줄일 수 있다:
    ```diff
    for (i = 0; i < 10; i++) {
    -   LOCK();
    -   sum_global = sum_global + i
    -   UNLOCK();
        sum_tls = sum_tls + i;
    }

    + LOCK();
    + sum_global = sum_tls;
    + UNLOCK();
    ```
  - `errno` 값을 다룰 때도 유용하다:
    - 스레드 하나가 에러나서 `errno`를 `-1`로 설정, 이어서 들어온 다른 스레드가 `errno`를 `0`으로 덮는 문제.
    - `errno`를 TLS로 만들면 문제를 해결할 수 있음.
- 리눅스의 스레드:
  - 사실 프로세스도, 스레드도 그냥 `task_struct`로 구현됨.
    - 스레드는 그저 같은 주소공간을 공유하는 `task_struct`.
    - 주소공간이 다르다면 다른 프로세스.
  - `clone`:
    > clone() creates a new process, in a manner similar to fork(2). (...) The main use of clone() is to implement threads: multiple threads of control in a program that run concurrently in a shared memory space.
    - 실행 컨텍스트를 복제해서 새로운 `task_struct`를 만든다.
    - 주소공간이 같은 `task_struct`를 만들 수 있다. 즉, 스레드를 만드는 것.

## Process Scheduling

- CPU 코어가 20개인데 프로세스가 100개면 어떡하죠?
- 운영체제의 스케줄러가 어떤 프로세스를 할당할지 적절히 스케줄링해주면 된다.
- 프로세스 상태 다이어그램 생각나시죠? 프로세스 상태가 바뀔 때 스케줄러가 개입한다.
- 스케줄링을 배운다는게 뭘 배운다는건가?
  - 프로세스간 스위치를 어떻게 하는가?
  - 스케줄링 가능한 프로세스를 어떻게 찾고 관리할 것인가?
  - 다음에 실행할 프로세스를 어떻게 선택할 것인가?
- Time sharing:
  - 운영체제가 하드웨어 타이머와 인터럽트 핸들러로 시분할을 제공.
  - 간단한 예시:
    1. 운영체제가 타이머에 1초 뒤 울리라는 알람을 설정.
    2. 어떤 프로세스가 유저모드에서 돌다가, 1초가 지나서 인터럽트가 발생.
    3. 인터럽트 핸들러로 넘어가면서 커널 모드로 전환.
    4. 인터럽트 핸들러를 통해 스케줄러가 돌고, 다음 프로세스를 선정.
    5. 스케줄러가 기존 프로세스를 빼고 새 프로세스를 CPU에 할당.
    6. 다시 유저모드로 실행하고 1번으로 돌아간다.
- 컨텍스트 스위치:
  ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_04_ProcessSwitch.jpg)
  - CPU가 다른 프로세스를 실행하려면, 현재 프로세스의 상태를 저장하고, 다음 프로세스의 상태를 로드해야.
  - 프로세스의 컨텍스트는 PCB로 표현된다. PCB에 각종 레지스터가 있었죠.
  - 컨텍스트 스위치 자체가 오버헤드. 컨텍스트 스위치를 너무 자주하면 안 좋아요.
  - 그렇다고 컨텍스트 스위치가 너무 안 일어나도 문제. 더 중요한 작업이 있는데 그 작업을 못한다.
- 프로세스는 큐로 관리됨:
  ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter3/3_06_QueueingDiagram.jpg)
  - Job queue: 모든 프로세스.
  - Ready queue: ready 상태인 프로세스
    - 프로세스 스케줄러가 레디 큐에서 프로세스를 꺼내서 CPU에 할당.
    - CPU에서 처리하면 적절한 절차를 따라 다시 레디 큐로 들어간다.
  - Device queue: 사용할 디바이스를 기다리는 프로세스.
  - 그 외 큐들은 필요에 따라 만들고 사용한다.
- 스케줄링 평가 지표:
  - Want to maximize: CPU utilization, throughput
  - Want to minimize: turnaround time, waiting time, response time
- 각종 알고리즘:
  - OSTEP에도 잘 설명되어 있음: https://pages.cs.wisc.edu/~remzi/OSTEP/Korean/07-cpu-sched.pdf
  - FIFO(First In First Out), SJF, SRJF, RR, Priority scheduling, MLFQ
  - Priority inversion:
    - 나사의 화성 패스파인더. 착륙 후 컴퓨터가 반복 재부팅되는 일이 일어남.
    - 와치독 타이머가 태스크가 한동안 실행되지 않으면 컴퓨터를 재부팅시킴.
    - 패스파인더에는 3가지 태스크가 있었음: 버스 관리, 통신, 데이터 수집
      - 데이터 수집 태스크가 락을 릴리즈하면 버스 관리 태스크가 락을 얻어야 함.
      - 만약 데이터 수집 태스크가 락을 갖고 있으면 락을 얻지 못하고 대기한다.
      - 그런데 중간에 통신 태스크가 끼어든다. 때문에 우선순위가 높은 태스크가 아니라 끼어든 태스크를 수행함.
    - 해결법:
      - Priority Inheritance Protocol(PIP):
        - 실제 우선순위가 높은 태스크의 우선순위를 빌려준다.
        - 락을 릴리즈할 때 원래 우선순위로 돌아온다.
      - Priority ceiling protocol(PCP)
        - 우선순위를 높일 때 그 천장을 정해둔다.
  - 실제 리눅스 스케줄러는?
    - MLFQ 아이디어를 기반으로 Completely Fair Scheduling(CFS).
    - 사용자와 인터랙티브하는 프로세스는 우선순위를 높임.
    - preemptive, time-shared based on time slice
    - 온갖 휴리스틱과 부두 상수가 난무합니다.
  - Real-time systems:
    - Hard real-time: 어떤 태스크를 데드라인 안에 끝내지 못하면 치명적인 시스템. e.g., 자율주행, 로봇
    - Soft real-time:
      - 태스크를 데드라인 안에 끝내지 못해도 치명적이지 않은 시스템.
      - 실시간 태스크가 non-critical 태스크보다 우선권을 받는다.
    - Real-time CPU Scheduling:
      - 주기적인 프로세스가 있다고 생각하자. 인터벌 $p$, 처리시간 $t$, 데드라인 $d$.
      - Rate Monotonic Scheduling(RMS):
        - $p = d$, $1 / p$가 높은 프로세스를 preemptive하게 우선 할당.
        - 데드라인을 못 지킬 수 있음. RMS는 feasible한 real-time scheduling을 찾을 수 없음.
      - Ealiest Deadline First(EDF):
        - $p = d$, 현재 상황에서 데드라인이 임박한 프로세스를 우선 할당.
        - 데드라인까지 남은 기간이 priority가 되는 셈. 님들이 과제할 때 이렇게 하죠.
        - 인터벌 없이 데드라인만 있어도 잘 동작. 이론적으로 optimal하다. 데드라인을 안 놓친다.

## Synchronization

- 멀티 코어 시스템에서의 각종 동시성 문제.
- 조건: mutex, progress, bounded waiting
- critical section과 mutex를 화장실로 설명하심.
- 스핀락의 나이브한 구현과 피터슨 알고리즘:
  - 우리 교과서는 mutex lock을 스핀락이랑 같은 걸로 설명한다.
  - 근데 mutex lock의 정의에 busy-waiting해야 한다는 건 없음. blocking해도 mutex lock일 수 있음.
  - 그러니까 스핀락은 mutex lock의 서브셋임.
- 하드웨어 지원: test-and-set, compare-and-swap
- busy-waiting semaphore, blocking semaphore
- 모니터: 프로그래밍 언어 차원에서 공유 데이터에 대한 동기화를 지원.
- 컴파일러와 동기화:
  - 이건 책에는 없는 내용.
  - C/C++은 문법적으로 싱글 스레드 실행만을 전제한다.
  - 컴파일러가 코드를 컴파일할 때 멋대로 최적화해버릴 수 있음.
    ```c
    bool ready = false;

    void wait(void) {
        while (!ready) {
            do_nothing();
        }
    }

    void signal(void) {
        ready = true;
    }
    ```
    - 가령 busy-waiting할 때 쓰는 `ready` 변수를 레지스터에서 읽도록 최적화하면 문제가 생김.
    - `volatile` 키워드를 사용하면 매번 메모리에서 변수를 읽도록 개발자가 강제할 수 있다.
  - 코드는 님들이 작성한대로 실행되지 않는다. 컴파일러도 최적화해주고, 프로세서도 최적화해줌.
  - 이게 멀티 스레드 환경에서 문제가 됨. 이때 메모리 배리어로 인스트럭션의 순서를 지키게 해야한다.
- 동기화의 고전적 문제들:
  - Bounded-buffer problem:
    - Producer-consumer problem: 하나의 버퍼를 producer와 consumer 동시에 사용하는 상황.
    - 그런 상황에서 한정된 버퍼에서 일어날 수 있는 문제. (무한 버퍼 상황에서 일어나는 문제는 따로 있음.)
    - producer는 버퍼가 넘치지 않게 생산해야, consumer는 버퍼에 뭔가 있을 때만 소비할 수 있어야.
    - 한정 버퍼의 일반적인 구현은 링버퍼: `in == out`일 때 empty, `(in + 1) % SIZE == out`일 때 full.
    - 한 버퍼에 두 producer가 동시에 값을 쓸 때, 두 consumer가 동시에 값을 읽을 때 문제가 생긴다.
    - 뮤텍스 락이나 세마포어로 `in`과 `out`을 비롯한 공유 자원에 접근하는 임계 영역에 락을 걸어주면 해결.
  - Readers and writers problem:
    - 읽기 동작에 대해서는 몇 명이든 동시에 읽어도 문제가 없음. 문제는 동시 쓰기에서 발생.
    - 그래서 reader는 writer가 락을 가지고 있지 않은 이상 락을 얻는 데 제한이 없음.
    - 근데 reader가 끊임없이 들어온다면? writer에게 starvation이 발생하는 문제.
    - 다양한 방법으로 해결할 수 있음.
  - Dining philosopher problem: 잘 아는 그거.
- 리눅스 커널은 동기화를 어떻게 처리하나?
  - 옛날에는... BKL(Big Kernel Lock)이라는 뮤텍스 락을 커널 전체에 걸었다.
  - 그래서 커널에는 무조건 하나씩만 들어올 수 있었음.
  - 이제는 BKL을 잘게 쪼개고 완전 preemptive하게 동작함.
- Deadlock:
  ![](https://wiki.factorio.com/images/thumb/Train-deadlock.png/1000px-Train-deadlock.png)
  - 데드락이 일어나려면 아래 4개 조건을 모두 만족해야:
    - Mutex: 한 폐색에는 하나의 열차만 진입할 수 있음.
    - Hold and wait: 하나의 폐색을 점유한 상태로 다음 폐색에 진입할 수 있을 때까지 기다림.
    - No preemption: 폐색에 진입한 열차를 임의로 제거할 수 없음.
    - Circular wait: 열차가 서로를 기다리며 사이클을 이룸.
  - Prevention: 4개 조건 중 하나를 만족하지 않게 함으로써 데드락 발생을 사전에 방지한다.
    - Mutex: 이건 어쩔 수 없음.
    - Hold and wait:
      - 기다리는 건 어쩔 수 없는데 홀드는 하지 않도록 만들 수 있음.
      - 하지만 리소스 사용률이 떨어지고 리소스를 많이 사용하는 태스크에서 starvation이 일어날 수 있음.
    - No preemption: preemption해서는 안 되는 리소스도 있기 때문에 현실적으로 막기 어려움.
    - Circular wait:
      - 가장 일반적인 접근.
      - 리소스에 순서를 매겨서 total ordering.
      - 2번 리소스를 잡을 수 있다해도 1번 리소스를 아직 못 잡았다면 기다린다.
      - 이렇게 하면 한쪽 방향으로만 리소스를 요구하게 된다. a.k.a. 2PL
      - 리눅스에는 witness가 있어서 리소스 순서를 이상하게 잡으려는 상황을 감지한다.
  - Avoidance:
    - 현재 safe한 상태에서 unsafe한 상태로 전이할 것 같다면 회피한다:
      - Safe state: 모든 태스크에 리소스를 할당할 수 있는 상태.
      - unsafe한 상태에서는 dealock이 발생할 수 있음.
    - 리소스 할당 그래프:
      - 그래프를 그려보고, 사이클이 있으면 데드락 위험이 있으므로 리소스 할당을 제한한다.
      - 미래를 예측해야. 잘못하면 리소스 utilization이 떨어질 수 있다.
    - Banker's algorithm:
      - Available: 사용 가능한 자원 (현재 얼마나 할당할 수 있는지)
      - Max: 각 태스크의 최대 리소스 요구
      - Allocation: 각 태스크에 할당된 자원
      - Need: 각 태스크에 남아있는 리소스 요구 (앞으로 얼마나 요구할지)
      - 이 테이블들을 보고 safe sequence를 찾아 리소스를 할당한다.
    - Ostrich algorithm:
      - 타조는 위험한 상황에서 머리를 땅에 묻어버린다... 데드락을 모르는 척하고 쌩까겠다는 것.
      - 실제로 대부분의 운영체제가 이렇게 한다. 데드락이 일어나는 빈도에 비해 대응하는 오버헤드가 너무 크다.
      - 개발자가 알아서 데드락이 발생하지 않도록 프로그램을 잘 작성해야. 운영체제는 뭘 안해준다.

## Memory Management

- 지금까지 거의 프로세서 얘기만 했음. 이제 메모리 얘기를 해보자.
- 프로세서가 태스크에게 가상화를 제공하듯 메모리도 가상화를 제공한다.
- 메모리를 값이 저장된 배열로 생각해보자:
  - 메모리의 특정 위치를 주소로 가리킬 수 있음.
  - 주소를 여러 다른 형식으로 쓸 수 있음: 물리주소(PA)와 논리주소(LA or VA), 절대주소와 상대주소.
  - 프로세서는 LA를 뿜어내요. CPU 코어의 일부에 있는 Memory Management Unit(MMU)가 LA를 VA로 바꿔줌.
    ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_04_DynamicRelocation.jpg)
  - 님들이 프로그래밍할 때 보는 주소는 모두 LA입니다. MMU가 변환해주는거고, 운영체제가 매핑 테이블을 관리.
- Fixed partition:
  - 메모리를 고정된 크기로 쪼개고, 각 파티션에 프로세스를 하나씩 꽂아 넣는다.
  - 그 파티션이 프로세스의 독립된 가상 공간이 되는 셈.
  - base register에 오프셋 PA를 저장해두면 LA를 base에 더하면 쉽게 PA를 얻을 수 있음.
  - 자신의 주소공간이 아닌 위치를 참조하려하면 MMU가 제한.
  - 프로세스가 스케줄링될 때 base도 그 프로세스의 오프셋에 맞게 변경되어야.
  - 구현하기도 쉽고 빠르게 컨텍스트 스위치 가능하지만...
  - 프로세스마다 메모리 요구량이 다르기 때문에 고정된 파티션 크기가 맞지 않을수도.
  - Internal fragmentation:
    - 할당된 파티션에 비해 프로세스가 사용하는 메모리 양이 적을 수 있음.
    - 하나의 파티션은 하나의 프로세스만 사용할 수 있으므로, 남는 공간이 낭비되는 상황.
- Variable partition:
  - 천편일률적으로 파티션을 나누지 말고 프로세스의 필요에 맞게 할당하자.
  - 운영체제가 프로세스의 메모리 요구량을 얻어서 필요한만큼만 메모리를 할당.
  - LA에 base를 더하는건 fixed partition과 동일, 여기에 limit register가 필요함.
  - 계산된 PA가 limit보다 작을 때만 접근을 허용. 컨텍스트 스위치마다 base와 limit을 함께 변경해야.
  - 여러 빈 공간 중 어느 곳에 새 프로세스를 할당해야 할까?
    - 할당 전략(allocation strategy)에 따라 다름.
    - First fit: 그냥 첫 번째로 맞는 공간에 할당. 빠르지만 내부 단편화가 심해짐.
    - Best fit: 최대한 딱 맞는 공간에 할당. 좋을 것 같지만 오버헤드가 큼.
    - Worst fit: 가장 넓은 공간에 할당. 오버헤드가 큼.
  - External fragmentation:
    - 프로세스가 메모리 사용을 마치고 나가면 빈 공간이 생김.
    - 빈 공간의 총합은 충분히 크지만, 서로 떨어져 있어서 새로운 프로세스를 할당할 공간이 없는 상황.
- Segmentation:
  ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_08_SegmentationHardware.jpg)
  - 프로세스가 미래에 어느정도의 메모리를 사용할지 예측할 수 없음.
  - 주소공간에 힙과 스택 사이에 큰 빈 공간이 있다. fixed/variable 파티션으로는 공간 낭비가 심해짐.
    - 한 파티션에 하나의 프로세스를 할당하지말고, 한 프로세스를 여러 세그먼트로 쪼개서 할당하자.
    - variable partition의 확장으로 볼 수도.
  - code, data, heap, stack 영역을 개별 세그먼트로 나눠서 메모리의 여기저기에 할당할 수 있음.
  - 각 프로세스는 자기만의 세그먼트 테이블을 갖는다:
    - CPU의 segment-table base register(STBR)에 저장할 수 있음. 컨텍스트 스위치가 쉬워짐.
    - 세그먼트에 대한 base, limit을 관리해야. 잘못된 세그먼트에 접근하면 segmentation fault 발생.
  - 세그먼트 테이블이 문제:
    - 레지스터에 넣자니 컨텍스트 스위칭 오버헤드가 큼.
    - 하드웨어로 만들면 세그먼트 개수가 제한됨.
    - 메모리에 두면 MMU가 메모리를 왔다갔다 해야하니 성능 저하.
- Paging:
  - 세그먼트를 써도 결국 단편화가 발생한다. 차라리 아주 작게 파티션을 나눠 놓으면 어떨까?
  - 프로세스의 주소공간을 일정 크기의 페이지로 잘개 쪼개고, 물리메모리도 같은 크기의 프레임으로 쪼갠다.
  - 내부 단편화는 발생할 수 있는데, 외부 단편화는 발생하지 않는다. 모든 페이지를 같은 크기로 쪼개놨으니까.
  - 페이지 사이즈가 작을수록 좋겠지만, 너무 작으면 페이지 테이블이 거대해짐. 요즘에는 보통 4KB 페이지를 사용.
  - Page table:
    ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_10_PagingHardware.jpg)
    - 쪼개는건 둘째치고, 가상 주소공간에서 물리 메모리로 매핑을 어떻게 할 것인지가 중요.
    - VPN(virtual page number)를 PFN(physical frame number)로 바꿔야 한다:
      - Virtual address = <VPN, offset>
      - Physical address = <PFN, offset>
    - 각 프로세스마다 페이지 테이블을 관리:
      - 현재 실행 프로세스에 대한 page table base register(PTBR)가 해당 프로세스의 페이지 테이블을 가리킴.
      - 컨텍스트 스위치할 때 PTBR을 업데이트해줘야. x86에서는 CR3.
    - 페이지 테이블은 운영체제가 관리하고, MMU가 참조한다.
    - e.g., 32비트 시스템을 생각해보자:
      - VA는 32비트(4GB), PA는 20비트(1MB), 페이지 사이즈는 4KB.
      - 오프셋 비트는 $\log_2 4096 = 12b$.
      - VPN = $32 - 12 = 20b$.
      - 페이지 테이블의 최대 엔트리 수는 $2^{20}$개.
      - 페이지 테이블의 각 엔트리 크기: VPN은 인덱스, PFN은 오프셋을 뺀 나머지 $20b - 12b = 8b$.
      - 페이지 테이블 크기는 $2^{20} \times 8b$. $2^{20}B$. 즉, 1MB.
      - VA `00004AFE`가 들어오면, `00004`는 VPN, `AFE`는 오프셋.
      - 페이지 테이블에서 VPN `00004`를 참조한다. 여기에 대응되는 PFN이 `6`이라고 한다면...
      - 최종적인 PA는 `46AFE`. 이때 `46`은 PFN, `AFE`는 오프셋.
    - 사실 페이지 테이블 엔트리에는 추가적인 정보가 있다:
      - Valid bit(1b)
      - Reference bit(1b)
      - Modify bit(1b)
      - Protection bit(3b)
    - 무조건 페이지 테이블을 거쳐야 PFN을 얻을 수 있다:
      - PTBR은 컨텍스트 스위치가 될 때만 변경된다.
      - 따라서 한 프로세스가 다른 프로세스의 페이지를 읽을 수 없음.
  - 페이징을 하면 이론적으로는 외부 단편화가 발생하지 않음:
    - 그런데 물리적으로 연속한 페이지를 요구 한다면?
    - I/O 버퍼나 in-kernel 자료구조가 이렇게 물리적으로 연속한 페이지를 필요로 할 수 있음.
- Buddy system allocator:
  - 외부 단편화를 줄이기 위한 또 다른 매커니즘이 필요하다.
  - 버디 할당기는 처음에는 메모리를 하나의 청크로 간주. $2^n$개의 페이지를 한 청크로 관리.
  - 할당이 필요하면 할당하기에 알맞은 크기가 될 때까지 청크를 반복적으로 절반씩 쪼갬.
  - 할당이 아니라 해제할 때 진가가 드러난다: 자신을 해제할 때 자신의 버디가 비어있다면 병합한다.
  - 청크가 $2^n$개의 단위로 구성되므로 내부 단편화가 일어날 수 있긴 함.
- Hierarchical page tables:
  ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_18_AddressTranslation.jpg)
  - 페이지 테이블 여러 개를 계층적으로 사용해보자. radix 트리가 만들어지는 셈.
  - PTE(page table entry)가 $2^2$개면 MSB 2개가 인덱스가 되고, $2^3$개면 MSB 3개가 인덱스가 될 것.
  - 현재 대부분의 시스템은 hierarchical page table을 쓴다.
  - 장단점:
    - sparse 주소공간을 효과적으로 지원할 수 있음.
    - MMU를 하드웨어로 쉽게 구현할 수 있게 됨.
    - 외부 단편화가 일어나지 않음.
    - 구현이 복잡함.
  - 개념적으로 제시만 되고 쓰이지는 않는 매커니즘:
    - Hashed page table: LA의 VPN 부분을 해시함수에 넣어서 PFN을 얻는다.
      ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_19_HashedPageTable.jpg)
    - Inverted page table: 역으로 PFN에 <VPN, PID>을 매핑. LA의 PID와 VPN으로 PFN을 얻는다.
      ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_20_InvertedPageTable.jpg)
- Translation Look-aside Buffer(TLB):
  ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_14_PagingHardware.jpg)
  - hierarchical page table 아주 좋아보이죠? 근데 큰 문제가 있어요:
    - VA 하나를 변환하려고 메모리를 엄청 읽어야 한다.
    - 페이지 테이블 계층 개수 + 1번이나 메모리를 읽어야 함.
  - VPN 10이 PFN 30이라는 걸 알았다면 다음에 다시 VPN 10을 변환할 때 페이지 테이블을 읽을 필요가 없다.
    - MMU는 페이지 테이블을 보기 전에 먼저 TLB를 확인해본다. TLB는 하드웨어라서 빠르게 참조 가능.
    - TLB에 없으면 페이지 테이블을 본다. 이렇게 PFN을 얻고 나면 TLB에 저장해둔다.
    - 메모리 참조는 locality of reference가 매우 크기 때문에 캐시 효과가 매우 좋다.
  - 컨텍스트 스위치할 때는 TLB를 비워야:
    - 컨텍스트 스위치가 되면 PTBR이 바뀌면서 새 프로세스에 맞는 페이지 테이블을 바라보게 됨.
    - 하지만 TLB는 변경되지 않기 때문에 새 프로세스와 불일치가 일어남. 그래서 싹 비워버리는 것.
    - ASID: 어떤 아키텍처는 TLB를 비우는 대신, 이게 어떤 프로세스에 대한 데이터인지 저장해둔다.
- Swap:
  - 메모리에서 잘 쓰이지 않는 프로세스를 backing store로 swap out.
  - 다시 실행을 재개할 때 backing store에서 메인 메모리로 swap in.
- Demand page:
  - 프로세스 전체를 swap하지말고, 특정 페이지만 swap하는 모델.
  - 필요할 때 특정 페이지만 메모리에 로드하자.
  - PTE의 valid bit에 특정 페이지가 메모리에 있는지 적어둬야.
  - Page fault:
    ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter9/9_06_PageFaultSteps.jpg)
    - valid bit이 0이면 MMU가 page fault를 일으켜서 트랩을 날림.
    - 그럼 운영체제는 디스크에 swap된 페이지를 찾아서 메모리에 올리고 PTE를 업데이트한다.
  - demand paging은 지역성 원칙을 레버리징한다.
  - 하드웨어 지원이 필요:
    - 하드웨어 장치에 valid bit가 있어야 함.
    - 메인 메모리와 보조 기억 장치가 필요.
    - page fault를 일으킨 instruction을 reset하고 재실행할 수 있어야.
  - VM(Virtual Memory):
    - 이렇게 물리 메모리를 가상화해서 사용하는 걸 가상 메모리라고 한다.
    - 논리 메모리와 물리 메모리를 분리해서 프로그램 개발이 쉬워짐.
    - 프로세스의 일부만 메모리에 올릴 수 있고, 메인 메모리의 일부만 점유할 수 있음.
    - 논리 주소공간이 물리 주소공간보다 더 커질 수 있음.
- Shared memory:
  - 서로 다른 프로세스가 shared memory를 사용하는 경우 PTE에 같은 PFN을 써두면 된다.
  - 이 방식을 통해 `fork`가 매우 쉬워짐:
    - `fork`를 하면 부모의 페이지를 복사하는 대신, 자식이 부모와 같은 페이지 프레임을 바라봄.
    - 그런데 write를 할 때는 동작이 다름. 부모와 자식의 PTE에 있는 write bit을 임시로 끈다.
    - 그럼 write를 시도할 때 MMU가 page fault를 날린다.
    - 운영체제가 page fault handler에서 다른 프레임에 내용을 복사한다.
    - 새로 복사된 프레임을 읽도록 PTE를 변경하고 write bit를 켜줌.
    - 이렇게 복사하고 그 위치에 쓰는 방식이 copy-on-write(CoW).
    - 그림을 보자:
      ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter9/9_07_Page_C_Unmodified.jpg)
      - 이그림에서 프로세스2는 프로세스1의 자식임. 모두 같은 PTE를 바라보고 있다.
      - 만약 프로세스1이 페이지C를 수정하면?
      ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter9/9_08_Page_C_Modified.jpg)
      - 페이지C를 복사하고, 복사한 PTE를 바라보고 write한다.
  - `malloc`도 CoW로 동작한다:
    - `malloc`을 하는 시점에는 아무 일이 일어나지 않음.
    - 할당한 위치를 읽을 때는 그냥 0으로 채워진 zero page가 읽혀짐.
    - write할 때 비로소 페이지를 새로 만들어서 바라보게 된다.

## Virtual Memory

- VM Features:
  - 운영체제는 메모리의 어디에 있나?
    - 프로세스는 사실 일정한 사용자 주소공간만을 사용함.
    - 그 아래 운영체제 커널이 shared page를 통해 모든 프로세스에 걸쳐있음. 여기가 커널 주소공간.
    - 유저 주소공간에서 `jmp 0xc0000100`처럼 커널 주소공간으로 점프하면 커널의 시스템 콜을 실행.
    - 그래서 모든 프로세스가 쉽게 공유된 운영체제를 사용할 수 있음.
  - Paging virtual memory:
    - 코드: 파일에서 read-only로 읽음. file-backed pages.
    - 스택과 힙: 파일이 아닌 anonymous page로 시작. 0으로 채워진 zero page.
    - 데이터: 처음에는 file page로 시작, write가 일어나면 페이지가 만들어짐.
  - Frame allocation: 한정된 페이지 프레임을 절절한 정책에 따라 할당해야.
  - Thrashing:
    ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter9/9_18_Thrashing.jpg)
    - working set: 프로세스에서 자주 사용하는 페이지의 집합.
    - working set만 메모리에 잘 올라와 있어도 성능 저하가 크게 일어나지 않는다.
    - 메모리 크기가 working set보다 작다면 페이징이 자주 일어나고 급격한 성능 저하가 발생.
    - 그럴 때는 프로세스를 죽이거나 메모리를 증설해야.
  - Prepaging:
    - 어떤 페이지를 참조하면 지역성 원리에 따라 주변 페이지에도 접근이 일어날 확률이 높음.
    - 그래서 접근이 일어난 페이지의 주변 페이지를 미리 함께 메모리에 올려놓는 것.
    - 리눅스 커널에서는 fault-around scheme이라고 한다.
- Page replacement:
  - 메모리가 가득 차서 페이지를 디스크로 swap해야 할 때 어떤 페이지를 victim으로 선택할 것인가?
  - page fault의 페널티가 너무 크다. 메모리 접근은 200ns인데, 디스크 접근은 8ms나 걸림.
  - $p$ 확률로 페이지 폴트가 발생한다면, $p \times \text{page fault handling time} + (1 - p) \times \text{memory access}$.
  - 최대한 페이지 폴트를 줄여야. 가장 접근이 적을 것 같은 페이지를 잘 골라서 페이징해야 할 것.
  - 하지만 미래를 볼 수는 없음. 페이지 교체 알고리즘 자체가 굉장히 챌린징한 일.
- Page replacement policies:
  - Belady's algorithm(OPT)
    - 가장 나중에 읽힐 페이지를 victim으로 설정.
    - 수학적으로 가장 optimal한 알고리즘.
    - 쩌는 페이지 교체 알고리즘을 만들었다고 가정해봐요:
      - Page Fault Rate(PFR)을 측정.
      - OPT 대비 얼마나 좋은지도 살펴볼 필요가 있음.
  - FIFO(First-In First-Out):
    - 가장 먼저 로드된 페이지를 victim으로 설정.
    - 옛날에 들어온 애가 지금 필요없을 확률이 높겠지.
    - 물론 항상 그렇지는 않음. 언제 참조됐는지를 보지 않으면 locality를 고려하지 못함.
    - Belady's anomaly:
      - 페이지 프레임이 늘어났는데 PFR이 증가하는 현상.
      - FIFO에서 이 현상이 일어남. 투자를 더 했는데 성능이 더 안 좋아짐.
    - 그래서 FIFO는 잘 쓰지 않는다.
  - LRU(Least Recently Used):
    - 가장 과거에 사용된(참조된) 페이지를 victim으로 설정.
    - locality of reference를 활용하는 것. 과거를 보고 미래를 예측한다.
    - 이런 알고리즘을 stack algorithm이라고 한다.
      - Any page in memory with $n$ frames is also in memory with $n + 1$ frames.
      - belady's anomaly가 발생하지 않음.
    - 어떻게 구현할 것인가?
      - 나이브하게 클락이나 카운터를 쓰는 구현:
        - 모든 메모리 참조에 대해 시간이 지날수록 증가하는 카운터를 관리한다.
        - 페이징할 때 카운터가 가장 큰 페이지를 찾으려면 매번 $O(n)$ 시간이 걸리는 문제.
      - 이중 링크드 리스트나 스택을 사용하는 구현:
        - MRU를 head, LRU를 tail로 갖는 링크드 리스트. 관리가 힘든 문제.
        - 페이징할 때 빠르지만, 메모리 참조할 때 참조 관계를 재정렬해야 하므로 느려짐.
  - LRU approximation algorithms:
    - LRU를 실제 구현해보면 성능이 떨어지므로 LRU와 유사한 알고리즘을 쓴다.
    - Additional reference bits algorithm:
      - PTE에는 reference bit가 있음, 페이지에 접근할 때 MMU가 reference bit를 자동으로 설정함.
      - OS가 추가적인 reference bit를 관리하도록 해보자. 참조가 일어나면 right shift하고, MSB를 업데이트한다.
      - 즉, additional reference bit가 참조 이력을 유지하게 되는 것.
      - 따라서 additional reference bit이 가장 작은 페이지를 교체하면 됨.
    - Second-Chance algorithm:
      ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter9/9_17_SecondChance.jpg)
      - clock algorithm이라고도 부름. 페이지로 로지컬한 시계를 만들었다고 생각해보자.
      - 참조가 일어날 때마다 포인터가 시계방향으로 한칸씩 움직인다.
      - 포인터가 가리키는 페이지의 reference bit이 0이면 해당 페이지를 victim으로 설정.
      - reference bit이 1이면 비트를 0으로 클리어하고, 다음 페이지로 넘어간다. (세컨 찬스를 주는 것)
    - Enhanced second-chance algorithm:
      - victim 페이지를 evict하면 파일에 기록된다고 생각해보자:
        - 파일에 기록된 페이지를 메모리로 로드하고, 다시 evict하는 경우.
        - 메모리에서 페이지가 수정이 되지 않았으면 굳이 파일의 내용을 업데이트하지 않아도 된다.
        - 파일에 write하는 건 비용이 많이 드는 일.
      - PTE에 modify bit(또는 dirty bit)가 있다.
      - reference bit(R)과 modify bit(M)을 보고 판단한다:
        - `!R && !M`: 최근에 참조도 안 됐고, 수정도 안 됐으므로 바로 교체 가능.
        - `!R && M`: 참조는 안됐는데 교체 전에 파일에 쓰기가 되어야 함.
        - `R && !M`: 수정은 안 됐는데 조만간 다시 참조될 가능성이 높음.
        - `R && M`: 최근에 참조됐고, 수정도 일어났음.
  - Counting-based algorithm:
    - 최애 페이지 리스트를 관리한다.
    - LFU(Least Frequently Used): reference count가 가장 작은 페이지를 victim으로 설정.
    - MFU(Most Frequently Used): reference count가 가장 큰 페이지를 victim으로 설정.
    - 구현이 어렵고, OPT에 잘 근접하지 않아서 연구는 많이 됐는데 쓰이지 않음.
- Issues in page replacement:
  - Global replacement vs. Local page replacement:
    - Global: 모든 페이지 프레임을 대상으로 victim을 찾는다.
    - Local: 페이지 교체를 요구한 프로세스의 페이지 프레임을 대상으로 victim을 찾는다.
    - local은 성능이 일정하겠지만, 메모리를 덜 쓰게 됨. 결국 local optimal에 가까워지기 때문.
    - global은 다른 프로세스에게 성능 영향을 받음. 하지만 전반적인 처리율이 좋음. 일반적인 접근법.
  - Page pinning:
    - 종종 페이지가 메모리에 고정되어야 하는 경우가 있음.
    - `malloc`으로 공간 할당받고 GPU 작업을 수행하는 상황을 생각해보자.
    - GPU가 열심히 일하고 있는데 페이징이 일어나면 문제가 생길 수 있음.
    - 하드웨어와 일하고 있는 페이지는 victim으로 설정하지 않는게 pinning.
  - Paging virtual memory:
    - 앞에서 대충 얘기한 가상 주소공간 얘기를 다시 해보자.
    - 코드 영역은 거의 write할 일이 없음. 코드 페이지는 모두 modify bit이 모두 0일 것. 쉽게 페이징할 수 있음.
    - 스택과 힙 영역은 read/write가 빈번함. 페이징하려면 swap file에 내용을 백업해둬야 한다.
    - 데이터 영역은 한번이라도 write이 일어나면 anonymous page가 됨. CoW 이후에는 swap file에 백업이 필요.

## File Systems

- 보조 기억 장치가 왜 필요한지는 잘 알거임. 큰 저장 공간과 영속성이 필요하기 때문.
- 프로세스는 여러분이 직접 건드릴 일이 별로 없지만 파일 시스템은 수시로 건드린다.
- 파일:
  - 보조 기억 장치에 저장된 이름 붙여진 정보.
  - Pseudo file: 프로세스나 swap 공간에 대한 정보도 파일 형태로 추상화됨. `/proc`이나 `/tmp` 디렉토리.
  - 파일의 속성:
    - 이름, ID, Type, Location, Size, Permission, Time, etc.
    - 파일에도 타입이 있음. 파일 이름에 확장자라는 이름으로 표시하는 그것.
      - 윈도우즈에서는 `.exe`, `.jpg`처럼 이름에 표시.
      - UNIX는 파일의 첫 문자열에 표시. 셸 스크립트에 `#!/bin/sh`하는 것.
  - File operations:
    - Open:
      - 각 프로세스는 파일 디스크립터(fd) 테이블을 갖고 있음.
      - 테이블을 통해 프로세스가 어떤 파일을 열었는지 추적한다.
      - Open-file table: 열려있는 파일에 대한 테이블. 파일이 열려있다는 사실을 추적.
    - Access:
      - 프로세스는 열린 파일 각각에 대한 파일 포인터를 갖고 있음.
      - 파일 포인터는 마지막으로 읽거나 쓰기한 위치를 가리킴.
  - Directory:
    - 유저 입장에서는 파일을 모아놓은 묶음.
    - 시스템 입장에서는 그냥 특별한 메타데이터를 가진 파일:
      - 디렉토리는 파일 이름과 파일 속성의 집합. 디렉토리에 각 파일과 그 파일의 속성이 쓰여있다는 것.
      - 즉, 디렉토리는 파일과 그 파일에 대한 속성을 매핑시키는 파일.
    - 윈도우즈에서는 폴더라고 부름.
    - Tree-structured: 디렉토리는 트리 구조:
      ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter11/11_11_TreeStructure.jpg)
      - path가 주어지면 트리를 순회하여 파일을 찾을 수 있음.
      - open과 read 인터페이스가 분리되어 있는 이유. read할 때마다 open하려면 매번 트리 순회를 해야해서 느림.
  - Link:
    - 디렉토리 엔트리는 다른 디렉토리나 파일 데이터에 링크되어 있음.
    - 두 디렉토리 엔트리가 같은 파일 데이터를 링크하면 하드링크
    - 파일 아이디가 아니라 파일 경로를 기준으로 링크하면 심볼릭 링크.
    - 파일을 지우는건 링크를 끊는 것. 그래서 시스템 콜에 `rm`이 없고 `unlink`가 있음.
- 저장 장치:
  - HDD: 실린더, 암, 헤드, 트랙, 섹터, 플래터, ..., Seek time, Rotational delay, Transfer time으로 측정.
  - SSD:
    - NAND Flash:
      - 수많은 셀의 배열. 플래시 메모리 원리.
      - Read: 페이지(여러 셀의 집합) 단위로 비트열을 읽음.
      - Write(or Program): 페이지 단위로 특정 비트열을 기록. 쓰기 전에는 반드시 erase를 해야.
      - Erase: 블록(여러 페이지의 집합) 단위로 비트열을 초기화.
    - FTL(File Transition layer):
      - HDD를 위한 파일시스템은 사용하기 편리했음. 그냥 섹터 단위로 생각하면 됐음.
      - 그래서 기존 파일시스템에는 섹터 읽기와 쓰기 인터페이스만 있음.
      - 근데 SSD에는 그지같은 특성이 있다:
        - write과 erase를 많이 하면 oxide 레이어가 마모되면서 wear out이 일어남.
        - 한 번 write하면 바로 overwrite이 불가능함.
        - write하려면 erase를 해야 하는데, erase는 블록 단위로만 할 수 있음.
      - 하드웨어 장치를 위해 파일 시스템을 완전히 뜯어고쳐야 하나?
        - SSD 장치 내부에 FTL이라는 소프트웨어 레이어를 두자.
        - FTL에서 전통적인 블록 장치를 에뮬레이트해서 기존 파일시스템과 인터페이스를 맞춰줌.
      - NAND 플래시는 어차피 다 거기서 거기. 근데 FTL에 따라 SSD의 성능이 달라진다.
- 파일 시스템의 구현:
  - 디스크는 그냥 엄청 큰 어레이. 섹터가 512B 단위로 나뉘어 있음.
    - 하나의 파일을 여러 데이터 블록으로 쪼개서 저장한다.
    - 파일 이름과 파일에 대한 메타데이터도 디스크의 한 블록에 저장될 것.
  - 파일 시스템이라는 논리적인 레이어를 물리적인 리소스 위에 잘 설계하는게 중요:
    - 하나의 파일에 대한 블록을 여기저기 두는 것보다는 일렬로 두는게 좋음.
    - 데이터 블록을 일렬로 모아주는게 옛날에 쓰던 조각모음.
  - FAT:
    - 오래전 플로피 디스크와 HDD를 위해 만들어진 간략한 파일 시스템.
    - 구현하기 쉽고, 파일 시스템 자체를 유지하기 위한 메모리가 작음.
    - 오래된 파일시스템이고, 요즘에는 블랙박스같은 작은 임베디드 시스템에 쓰임.
    - 각각의 딜게토리 엔트리에 대응되는 File Allocation Table(FAT)을 관리:
      - 처음에는 모두 1로 초기화되어 있음.
      - 디렉토리 엔트리에 FAT의 인덱스가 적혀있음. FAT에서 해당 인덱스를 참조.
      - 해당 FAT 엔트리가 다른 엔트리를 가리킬수도. EOF를 가리킬 때까지 탐색을 함.
    - FAT16: 디렉토리 엔트리 하나가 16바이트. 파일 이름 12바이트, 나머지 4바이트는 FAT 인덱스.
    - FAT의 문제는 파일의 연속된 할당에 대한 고려가 부족. 읽기 쓰기를 반복하면 여기저기에 파일이 fragment된다.
  - EXT4:
    - 대표적인 유닉스 표준 파일시스템.
    - 70년대 중반 Fast File System이 유닉스에 도입. 그걸 개선해서 EXT2, EXT3가 나옴. 이제 EXT4.
    - 연속된 파일에 대한 설계가 잘 되어 있어서 fragment가 잘 일어나지 않음.
    - 더 궁금하면 저희 연구실 인턴을...
  - 다른 파일 시스템들:
    - 마소: NTFS (공식적인 구현이 알려져 있지 않음. 리버스 엔지니어링으로 파악)
    - 애플: HFS/HFS+, APFS (플래시 메모리 성능에 집중)
    - Android: F2FS (플래시 메모리에 최적화된 파일시스템, 메인테이너가 우리학교 졸업생이에요)
    - Redhat: XFS (고성능 컴퓨터에 적합한 파일시스템)
    - btrfs, LFS, RAMFS, ...
- Virtual File System:
  ![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter12/12_04_Virtual_FS.jpg)
  - 많은 파일 시스템이 있지만, 대부분의 사람들은 실제 파일 시스템을 모름.
  - 운영체제는 실제 파일 시스템에 상관없이 사용자에게 파일에 접근할 수 있는 인터페이스를 제공해야.
  - 리눅스 VFS는 어떤 파일시스템이든 3개의 정보를 요구한다:
    - superblock: 전체 파일 시스템
    - dentry: 앞에서 계속 얘기한 디렉토리 엔트리.
    - inode: 파일시스템의 오브젝트(파일과 디렉토리)에 대응.
- Page Cache:
  - 우리의 마지막 주제는 메모리와 파일 시스템의 조합.
  - SSD가 아무리 빨라도 DRAM에서 읽는게 빠름.
  - 메모리는 비싼 장치. 안 쓰면 손해다. 그럼 파일을 여유 메모리에 써두면 어떨까?
  - 페이지 캐시는 VFS의 확장.
  - 파일 접근이 일어나면 VFS가 파일 데이터를 비어있는 페이지 프레임에 저장해둔다.
  - 메모리가 더 필요하면? 페이지 캐시는 쉽게 비울 수 있음. clean file-backed 페이지니까.
  - 보통 남는 메모리 공간은 페이지 캐시로 쓰고, 1GB는 진짜 비어있는 free page로 남겨둠.
  - 메모리 정리 프로그램같은 거 있죠? 페이지 캐시를 날려서 메모리를 확보한 것처럼 만드는 것.
