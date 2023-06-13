# 모바일 프로그래밍

## 안드로이드

- 애플리케이션 마켓은 개발자와 소비자가 만나는 공간.
- 안드로이드의 특징:
  - 재사용 가능한 애플리케이션 프레임워크.
  - 최적화된 ART(Android Run Time) 가상 머신:
    - Ahead-of-time(AOT) 컴파일: 달빅의 JIT과 달리 미리 앱을 커파일해둔다.
    - GC, 디버깅 개선.
    - 메모리 사용량, 설치 시간 증가.
  - WebKit, OpenGL, SQLite 지원.

## 애플리케이션의 기본 구조

- 앱 개발 단계: 자바 소스 파일 > 컴파일러 > DEX 파일 > apkbuilder > APK 파일 > 사용자
- 앱은 4개의 컴포넌트로 구성되어 있음.
  - 액티비티:
    - 사용자 인터페이스 화면을 가지는 하나의 작업. (하나의 액티비티는 하나의 UI 화면)
    - 액티비티가 모여 앱이 된다.
  - 서비스: 백그라운드에서 실행되는 컴포넌트.
  - 방송 수신자: 화면 꺼짐, 사진 촬영 등 이벤트 발생을 수신하고 반응하는 컴포넌트.
  - 콘텐츠 제공자: 데이터를 관리하고 다른 앱에 제공하는 컴포넌트.
- PC 앱과 달리 모바일 앱은 다른 앱의 컴포넌트를 사용할 수 있음:
  - 인텐트:
    - 다른 앱의 컴포넌트를 사용하기 위해 인텐트를 전송.
    - 안드로이드가 인텐트를 받으면 적절한 컴포넌트를 찾아 활성화.
    - 앱 내에서 컴포넌트간 상호작용할 때도 인텐트를 사용해야 함.
- 기본적인 메인 액티비티:
  ```java
  public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.activity_main);
    }
  }
  ```
- 리소스: 레이아웃, 이미지, 문자열 등.
  - 코드와 리소스를 분리함으로써 언어, 화면 크기에 따라 리소스를 다르게 선택할 수 있음.
  - 문자열 리소스가 분리되어 있어 i18n 대응 가능.

## 기본 위젯

- View(컨트롤/위젯): 사용자 인터페이스를 구성하는 기초적인 블록.
- ViewGroup(레이아웃): 다른 뷰를 담는 컨테이너.
- View 클래스는 모든 뷰의 부모 클래스.
- UI를 작성하는 세 가지 방법:
  - XML
  - 자바 코드
  - 비주얼 도구

## 레이아웃

- Layout: UI의 시각적 구조를 정의하는 요소. ViewGroup의 서브클래스.
- 선형 레이아웃
- 테이블 레이아웃
- 상대적 레이아웃
- 프레임 레이아웃
- Constraint 레이아웃:
  - 유연하게 자식 뷰의 위치와 크기를 조정.
  - 중첩 없이 복잡한 레이아웃 구성 가능.

## 고급 위젯 다루기

- 커스텀 컴포넌트
- 화면 터치 이벤트:
  - ACTION_DOWN: 화면을 터치하는 첫 번째 포인터.
  - ACTION_POINTER_DOWN: 첫 번째 포인터 이후의 포인터.
  - ACTION_MOVE: 화면을 누르고 이동.
  - ACTION_POINTER_UP: 마지막 포인터가 아닌 포인터가 화면을 떠남.
  - ACTION_UP: 화면을 떠나는 마지막 포인터.

## 그래픽과 이미지

- Canvas 클래스는 그림을 그리는 캔버스.
- Paint 클래스는 선의 스타일이나 색상 등.
- 이미지:
  - res/drawable 디렉토리에 이미지 파일 배치.
  - View에 이미지를 그린다:
    ```java
    class MyView extends View {
      public MyView(Context context) {
        super(context);
        setBackgroundColor(Color.YELLOW);
      }

      @Override
      protected void onDraw(Canvas canvas) {
        Paint paint = new Paint();
        Bitmap b = BitmapFactory.decodeResource(getResources(), R.drawable.cat);
        canvas.drawBitmap(b, 0, 0, null);
      }
    }
    ```
- 애니메이션:
  - ValueAnimator:
    ```java
    ValueAnimator animator = ValueAnimator.ofFloat(100, 1000);
    animator.setDuration(2000);
    animator.setInterpolator(new LinearInterpolator());
    animator.addUpdateListener((animation) -> {
      x = (float) animation.getAnimatedValue();
      invalidate();
    });
    animator.start();
    ```
- 서피스 뷰:
  - `View.onDraw()`: UI 스레드가 실행, 복잡한 그림을 그리는 경우 ANR 발생.
  - 서피스뷰는 UI와 별도로 애플리케이션에게 그림을 그릴 수 있는 화면 제공.

## 메뉴, 대화상자 알림

- 메뉴의 종류:
  - Option menu: 액션 바의 오버플로우 아이콘(...)을 클릭했을 때 표시.
  - Context menu: 화면 요소를 롱터치했을 때 표시.
  - Popup menu: 특정 뷰에 붙어서 노출.
- 옵션메뉴:
  1. 옵션 메뉴 생성(XML)
  1. 메뉴 파일 등록: `onCreateOptionsMenu`
  1. 메뉴 아이템 이벤트 처리: `onOptionsItemSelected`
- 플로팅 컨텍스트 메뉴:
  1. 컨텍스트 메뉴 등록: `registerForContextMenu()`
  1. 컨텍스트 메뉴 생성: `onCreateContextMenu()`
  1. 메뉴 아이템 이벤트 처리: `onContextItemSelected()`
- Notification:
  1. 알림 채널 생성
  1. 알림 빌더 생성: `new NotificaitonCompat.Builder(this, channel)`
  1. 알림 속성 설정
  1. 탭, 버튼 액션 첨부
  1. 알림 생성

## 어댑터뷰와 프래그먼트

- 어댑터 뷰:
  - 배열이나 파일, DB에 저장된 데이터를 화면에 표시할 때 유용한 뷰.
  - 화면에 노출되는 많은 항목을 스크롤하며 이용.
- RecyclerView:
  - 아이템 뷰를 재활용하는 뷰.
  - 리스트뷰는 항목이 변경될 때마다 매번 뷰를 새로 생성, 성능 저하.
  - 뷰를 재활용하기 위해 내부에 뷰를 가진 View Holder 클래스를 정의.
  - Adapter 클래스는 RecyclerView.Adapter를 상속하며 아래 3개 메소드를 오버라이드해야:
    - 아이템 개수 반환: `getItemCount()`
    - 뷰에 데이터를 바인딩: `onBindViewHolder()`
    - 아이템을 보여주는 뷰가 들어있는 뷰 홀더 반환: `onCreateViewHolder()`
  - RecyclerView 구현 단계:
    1. LinearLayout과 GridLayout 중 하나를 선택.
    1. 각 아이템의 모양과 동작을 설계, ViewHolder 클래스를 상속받아 작성.
    1. 데이터와 ViewHolder를 연결하는 Adapter 정의.
- Fragment:
  - 액티비티 안에 배치할 수 있는 UI 조각.
  - 라이프사이클:
    ![](https://user-images.githubusercontent.com/6410412/244278156-f6696a57-091b-40b8-9576-4a099c9748e8.png)
    - 프래그먼트는 자신만의 라이프사이클 콜백 메서드를 가질 수 있음.
    - 하나의 액티비티에 여러 개의 프래그먼트를 결합할 수 있음.
    - 하나의 프래그먼트를 여러 액티비티에 사용 가능.
    - 프래그먼트의 라이프사이클은 호스트 액티비티에 종속.
  - 프래그먼트를 추가, 삭제, 대체할 때는 반드시 FragmentTransaction을 사용해야.

## 액티비티와 인텐트

- 애플리케이션:
  - 한 개 이상의 액티비티로 구성.
  - 시스템의 Application launcher로 구동.
- 태스크:
  - 사용자가 상호작용하기 위해 액티비티 스택에 쌓여있는 액티비티의 집합.
  - 하나의 태스크는 스택에 있는 액티비티들로 구성됨.
- 액티비티 스택:
  - 사용자가 방문한 액티비티가 스택에 push (백 버튼으로 돌아가면 pop)
  - 스택에 들어간 액티비티의 순서는 바뀌지 않음.
  - 이미 스택에 있는 액티비티가 중복 추가될 수 있음.
  - last 액티비티가 현재 실행되고 있는 액티비티.
- 인텐트:
  - 명시적 인텐트:
    - 명시적으로 지정된 인텐트, 동일 앱 내의 액티비티를 구동.
    - `new Intent(this, NextActivity.class)`
  - 암시적 인텐트:
    - 어떤 작업을 원하지만 그 작업을 담당하는 컴포넌트의 이름을 모를 때.
    - 시스템이 다른 앱들의 매니페스트에 있는 인텐트 필터와 비교, 일치하는 컴포넌트 선택.
    - 인텐트 필터는 컴포넌트가 처리할 수 있는 인텐트를 적어놓은 목록.
- 인텐트 필터링:
  1. 액션 비교: 인텐트에 지정된 하나의 액션과 일치해야.
  1. 카테고리 비교: 인텐트에 지정된 카테고리가 모두 필터에 있어야.
  1. 데이터 비교: 데이터 URI, MIME 유형이 지정된 경우 모두 일치해야.
- 액티비티 라이프사이클:
  ![](https://developer.android.com/guide/components/images/activity_lifecycle.png)
  - 실행: 액티비티가 포그라운드에 있고 사용자의 포커스를 가짐.
  - 일시정지: 다른 액티비티가 포그라운드에 있으나, 현재 액티비티 일부가 화면에 있음. (dialog 노출)
  - 정지: 액티비티가 백그라운드에 있음.
  - `onCreate()`: 액티비티 생성 시 호출, 구성요소 초기화.
  - `onPause()`: 사용자가 액티비티를 잠시 떠날 때 호출, 상태 저장 및 리소스 반납.
  - `onStart()`, `onResume` 사이에서 상태를 불러오는 `onRestoreInstanceState()` 콜백.
  - `onPause()`, `onStop` 사이에서 상태를 저장하는 `onSaveInstanceState()` 콜백.
- 액티비티가 백그라운드에서 running하는 것은 아님. (그건 백그라운드 서비스의 역할)
- 홈 버튼을 누르면 현재 태스크를 백그라운드로 보낼 수 있음.

## 리소스와 보안

- 리소스: 이미지, 문자열, 레아아웃 등.
- 각 앱은 각자의 프로세스에서 실행, 커널 수준에서 메모리 공간 독립 보장.
- 매스페스트에 필요한 권한을 작성하면 런타임에 사용자에게 승인 요청.
- 권한 요청: `onRequestPermissionsResult`

## 서비스, 방송 수신자, 콘텐츠 제공자

- 서비스: UI 없이 실행되는 컴포넌트.
- `startService()`
- `bindService()`
- 서비스 라이프사이클:
  ![](https://user-images.githubusercontent.com/6410412/244278182-8db2db71-ccea-4992-950f-b818abfef9f6.png)
- 백그라운드 서비스: 사용자가 인지하지 못하는 상태로 실행되는 서비스.
- 포그라운드 서비스: 사용자가 능동적으로 인식하는 서비스.
  - 메모리 부족에서 시스템이 중단되지 않음.
  - 상태 표시줄에 알림 제공 필요.
- IntentService:
  - Service는 메인 스레스에서 실행, 서비스 내에서 새로운 스레드를 생성해 작업을 수행해야 함.
  - IntentService는 시작 요청이 들어올 때마다 스레드를 별도로 생성.
- 서비스와의 인터페이스:
  - Binder 클래스 확장:
    ```java
    public class MyBinder extends Binder { ... }

    public IBinder onBind(Intent intent) {
      return new MyBinder();
    }
    ```
  - Messenger
  - AIDL
- 방송 수신자:
  - 장치에서 발생하는 다양한 이벤트를 받는 컴포넌트.
  - `BroadcastReceiver`를 상속하는 클래스에서 `onReceive` 오버라이드.
  - 디바이스 상태:
    - Sleep: 스크린 Off.
    - WakeLock: 방송 수신 시 sleep을 깨움.
- 콘텐츠 제공자:
  - 애플리케이션 간 데이터를 공유하는 수단.
  - 데이터 캡슐화, 보안 정의에 필요한 매커니즘 제공.

## 파일과 데이터베이스

- 내부 저장소:
  - 내부 저장소의 디렉토리를 얻을 수 있음: `getFilesDir()`
  - 파일 읽기: `openFileInput`, 쓰기: `openFileOutput`
- 외부 저장소:
  - 내부 저장소와 달리 외부 저장소는 누구나 읽을 수 있음.
  - 공개 공유 디렉토리 (앱을 제거해도 삭제되지 않음): `getExternalStoragePublicDirectory`
  - 사적 데이터를 저장하는 디렉토리: `getExternalFilesDir`

## 스레드

- 메인 스레드는 UI 스레드.
- 그 외는 작업 스레드(WorkerThread).
- UI 스레드는 블록시키면 안 된다. ANR이 일어날 수 있음.
- UI 스레드 외에서 안드로이드 UI 툴킷을 조작해서는 안 된다. 툴킷은 thread-safe하지 않음.
- 작업 스레드 내에서 UI 스레드를 사용하고 싶다면: `runOnUiThread`
- 다른 스레드와 상호작용하는 경우 핸들러를 통해 메시지를 주고받는다.
- ExecutorService:
  1. Create ExecutorService
  1. Define Runnable and Callable tasks
  1. Assign tasks to the ExecutorService

## 네트워크

- `ConnectivityManager`: 네트워크 연결 상태를 감시, 상태가 변경되면 방송.
- `ACCESS_NETWORK_STATE` 권한이 필요함.
- 모바일 애플리케이션 분류:
  - 안드로이드 SDK 기반(네이티브)
  - 웹 표준 기반(웹앱): 브라우저에 전적으로 의존.
  - 하이브리드(네이티브 + 웹): 웹뷰 사용.
- 웹에서 받은 DOM(Document Object Model)을 처리해야.

## Room

- SQLite DB를 다루기 위한 추상 레이어를 제공.
- 주요 컴포넌트:
  - 데이터베이스 클래스
  - 데이터 엔티티
  - 데이터 접근 객체(DAO)
- 각 레코드는 데이터 엔티티로 표현.
- 태스크를 submit하면 Executor Service의 큐에 쌓이고, 스레드에서 실행됨.

## Jetpack Compose

- Model-View-Intent 디자인.
- `@Composable`: 구성 가능한 함수를 호출해 데이터를 UI 요소로 반환.
- Recomposition: Comopse가 데이터 변경에 따라 Composable을 재실행해 업데이트.
- State (read-only) / MutableState: 앱 상태를 Compose에서 관찰 가능, 추적 가능 상태로 설정.
