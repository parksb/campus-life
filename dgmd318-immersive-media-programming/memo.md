# 몰입형미디어프로그래밍

- 난 핀란드 사람인데 스웨덴에도 살고 한국에도 살았음. VR/AR에 관심있다.
- AR/VR 프로젝트 과제가 2개 있을거고, 유니티 쓸거임.
- 금요일에는 랩 세션을 진행할거임. 개별 실습 과제와 팀플을 하고, 각종 질문받음.
  - 지난주 주제에 대한 실습 과제가 있음. 어렵지 않아요.
  - 팀플은 3-4명, 프로젝트는 결과를 발표하고, 코드나 문서 및 시연영상을 제출.
  - 왠지 모르겠는데 다들 게임을 만들어요. 시연영상은 진짜 게임 예고편처럼 만들어봐.
- 기말고사가 있을거임.
- 교재는 없고, 강의노트와 녹강, 유니티, C#을 쓸거임.
- AR은 안드로이드 디바이스가 있으면 됨. VR은 학교에 오큘러스와 메타퀘스트2가 있음.

## Unity basics

- 유니티는 크로스 플랫폼 게임엔진.
- Game object: scene에 있는 모든 것.
- Mesh: 게임 오브젝트의 모양.
- Colliders: 물체의 물리적 경계. 충돌 판정에 필요.
- Scene: 하나의 게임 화면이며, 여러 게임 오브젝트를 배치할 수 있다.

## Unity scripting

- C# 스크립트를 사용한다. prefab을 만들고, 여기에 스크립트를 추가할 수 있음.
- 스크립트 파일에는 `Start`와 `Update` 함수가 있음:
  - `Start`: 게임이 시작되기 전에 호출됨. 각종 초기화 작업.
  - `Update`: 게임 시작 후 매 프레임마다 호출됨.
- 스크립트에서 게임오브젝트를 참조할 수 있다:
  - `GameObject` 타입 변수를 `public`으로 만들고 유니티에서 연결하면 됨.
  - `private`으로 만들고 스크립트에서 `GameObject.Find("name")`으로 찾을수도.
  - `Instantiate`: 새 게임오브젝트를 생성한다.
  - 언제 스크립트에서 오브젝트를 생성해야 할까?
    - 레벨 시작시 prefab을 여러 다른 장소에 복제해야 할 때.
    - 무기에서 뭔가를 발상할 때, 총알이나 화살 등.
    - 게임오브젝트가 여러 조각으로 분해될 때, 폭발 등.
- 유니티의 벡터:
  - 유니티 좌표계는 왼손법칙을 따름.
  - `Vector3` 타입으로 오브젝트의 위치, 스칼라, 방향, 속도 등을 다룰 수 있음.
  - `MoveTowards`, `Lerp`, `Slerp` 같은 함수들을 유용하게 사용할 수 있음.
  - `Update` 함수 안에 `transform.Translate(transform.forward * Time.deltaTime * 0.5)`을 작성하면 단위 시간마다 0.5씩 앞으로 이동.
- 중요한 클래스들:
  - `GameObject`
  - `Transform`:
    - 게임오브젝트의 위치, 회전, 크기를 표현한다.
    - 유니티는 회전을 나타내는 두 방법이 있음, Euler angles와 quaternions
  - `MonoBehavior`: 스크립트의 베이스 클래스. 게임오브젝트에 대한 각종 정보가 있음.
- 이벤트 함수: 이벤트가 발생하는 특정 시점에 호출되는 함수들. `Update`도 이벤트 함수임.
- 키 입력으로 오브젝트 움직이기:
  - `Input.GetAxis("Horizontal")`, `Input.GetAxis("Vertical")`
  - `transform.Translate(new Vector3(horizontal, 0, vertical) * (5.0f * Time.deltaTime))`
  - 근데 이러면 대각선으로 움직일 때 속도가 빨라짐. 이걸 해결하려면 벡터를 normalize해줘야.
- Coroutines:
  - 스레드 프로그래밍 해봤죠? 유니티에는 코루틴이 있다.
  - 함수 실행을 일시정지하고, 유니티에게 제어권을 넘겨준 다음, 나중에 재개할 수 있음.
  - 가령 함수 안에서 `yield return WaitForSeconds(x)`하면 `x`초 뒤에 함수가 재개됨.
- Rigidbody:
  - 게임오브젝트가 rigidbody 컴포넌트를 갖는다면, 중력에 영향을 받는다. (비활성화하지 않는 이상)
  - 콜라이더를 쓰면 충돌에도 영향을 받음.
- Kinematic:
  - rigidbody 게임 오브젝트가 키네마틱이라면, 물리엔진에 의해 움직이지 않음.
  - 즉, 중력이나 힘, 토크의 영향을 받지 않음.
  - 오직 스크립트나 애니메이션에 의해서만 움직이게 됨.
  - 스크립트로 임의의 force나 torque를 추가해줄 수 있음.
  - 여전히 collisions에 영향을 받기는 한다.
- Collision detection:
  - 다른 게임오브젝트와 콜라이더가 충돌했는지 판단:
    ```cs
    void OnCollisionEnter(Collision collision) {
        if (collision.gameObject.CompareTage("Enemy")) {
            Debug.Log("Collided with an enemy");
        }
    }
    ```
  - `OnCollisionEnter`는 딱 충돌했을 때 한번만 호출됨.
  - `OnCollisionStay`를 쓰면 콜라이더가 맞닿은 내내 반복 호출된다.
- Trigger:
  - 트리거로도 충돌을 판정할 수 있음.
  ```cs
  void OnTriggerEnter(Collider other) {
      if (other.CompareTag("Food")) {
          Debug.Log("Yum");
      }
  }
  ```
  - 트리거를 쓰면 다른 콜라이더를 통과할 수 있다.
- Raycasting:
  - 어떤 점 A부터 B로 향하는 보이지 않는 라인.
  - 레이캐스팅을 하면 ray가 어떤 콜라이더와 충돌하는지 체크할 수 있다.
  - 충돌한 오브젝트가 무엇인지, 그것과의 거리는 얼마인지, 충돌 좌표는 어디인지 알 수 있다.
  - e.g., FPS 게임에서 총쏘면 총알이 어디 착탄했는지 알 수 있음.
  - e.g., 플레이어가 추락하고 있다면 바닥과의 거리를 알 수 있음.
  - e.g., 플레이어와 적 사이에 뭔가가 있는지 체크할 수 있음.
