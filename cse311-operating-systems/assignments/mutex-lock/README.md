# Mutex Lock

race condition은 공룡책에서 다루는데, 간단히 말하자면 두 개 이상의 프로세스나 스레드가 하나의 데이터를 공유할 때 데이터가 동기화되지 않는 상황을 말한다. 그리고 코드에서 이러한 문제가 발생할 수 있는 부분을 critical section이라고 하며, 이 문제를 해결하기 위해 한 번에 하나의 스레드만 critical section에 진입할 수 있도록 제어하는 기법을 mutex lock이라고 한다.

CentOS에서 3개의 스레드를 운영하는 프로그램을 짜고, race condition을 발생시킨 뒤 mutex lock을 통해 해결했다.

![race condition](https://t1.daumcdn.net/cfile/tistory/998A64375B2867173C)

race condition이 발생했다면 결과값이 300000이 나오지는 않았을 것이다. 몇 번을 실행해도 좀처럼 race condition이 발생하지 않았다. 생각보다 race condition이 잘 일어나지 않는 것 같다. 그래서 로그를 분석하여 race condition이 발생했다면 발생한 위치를 알려주고, 그렇지 않다면 로그를 삭제한 뒤 다시 프로그램을 실행시키는 checker 프로그램을 만들었다. 이제 처음 한 번만 프로그램을 실행시키면, 프로그램이 작업을 마칠 때 checker를 실행시키고, checker는 로그를 분석해 결과를 알려준다. 완전히 자동화된 것이다.

![checker](https://t1.daumcdn.net/cfile/tistory/99EB2D4D5B2867132F)

몇 번 테스트를 반복하니 반가운 메시지가 출력되었다. 그리고 바로 로그를 열어 31649를 찾았다.

![log](https://t1.daumcdn.net/cfile/tistory/996581425B2866D601)

두 라인에 걸쳐 `counter` 값이 31649로 찍힌 것을 볼 수 있다. 그런데 최종 결과값은 300000에 턱없이 모자른 32750쯤이 나왔다. 스레드 수행도 1, 2, 3 순서대로 딱 맞아 떨어져 아무래도 찝찝했다. 윈도우에서 테스트했던 결과와 비교해봤다.

![windows](https://t1.daumcdn.net/cfile/tistory/994750335B2867593B)

윈도우에서는 한 번에, 그것도 엄청나게 높은 빈도로 race condition이 발생했으며, 최종 결과도 300000에 가까웠다. 왜 리눅스에서는 안된걸까? 교수님을 찾아갔더니 CentOS는 VM 위에서 구동한 것이고, 윈도우는 physical machine에서 구동한 것이라 결과에 차이가 있는 것 같다고 말씀하셨다.

![mutex lock](https://t1.daumcdn.net/cfile/tistory/9909D5415B28676802)

mutex lock을 통해 race condition을 막았다. checker에도 문제 없었고, 최종 값도 299999였다. (`counter`가 0에서 출발하니까 최종 값이 299999이어야 각 스레드가 100000번씩 수행되었다는 의미가 된다.) 아주 잘 작동한다!