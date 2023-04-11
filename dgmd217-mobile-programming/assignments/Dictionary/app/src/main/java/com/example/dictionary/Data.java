package com.example.dictionary;

public class Data {

    static String[] words = {
            "Fragment",
            "Activity",
            "ListView",
            "Adapter",
            "View",
            "TextView",
            "ListAdapter",
            "ImageView",
            "LayoutInflater",
            "MenuInflater",
            "Window",
            "Log",
            "Property",
            "ArraySet",
            "TimeUtils"
    };

    static String[] definitions = {
            "프래그먼트(fragment)는 하니콤 버전(API 버전 11)부터 추가된 기능이다. 프래그먼트는 태블릿과 같은 넓은 화면을 가지는 모바일 장치를 위한 		매카니즘이다.",
            "액티비티(activity)는 사용자 인터페이스 화면을 가지는 하나의 작업을 담당하는 		컴포넌트이다.",
            "ListView는 스크롤 가능한 항목의 목록을 표시하는 뷰 그룹입니다.",
            "Adapter 객체는 AdapterView해당 뷰에 대한 기본 데이터와 해당 뷰 간의 연결 역할을합니다. 어댑터는 데이터 항목에 대한 액세스를 제공합니다.",
            "이 클래스는 사용자 인터페이스 구성 요소의 기본 구성 요소를 나타냅니다. 뷰는 화면의 직사각형 영역을 차지하며 그리기 및 이벤트 처리를 담당합니다.",
            "사용자에게 텍스트를 표시하는 사용자 인터페이스 요소이다.",
            "확장 Adapter은 a ListView 와 목록을 백업하는 데이터 사이의 다리 입니다. 종종 데이터는 커서에서 가져 오지만 필수는 아닙니다. ListView는 ListAdapter에 래핑 된 모든 데이터를 표시 할 수 있습니다.",
            "이미지 리소스를 표시 Bitmap 또는 Drawable자원. ImageView도 일반적으로 사용 apply tints to an image되며 처리 image scaling됩니다.",
            "레이아웃 XML 파일을 해당 View 객체로 인스턴스화합니다. 직접적으로 사용되지 않습니다. 대신에 getLayoutInflater () 또는 getSystemService (Class)를 사용하여 이미 현재 컨텍스트에 연결되어 있다",
            "이 클래스는 메뉴 XML 파일을 Menu 객체로 인스턴스화하는 데 사용됩니다.",
            "톱 레벨의 윈도우의 외관과 동작 정책의 추상 기본 클래스입니다. 이 클래스의 인스턴스는 창 관리자에 추가 된 최상위보기로 사용해야합니다. 배경, 제목 영역, 기본 키 처리 등과 같은 표준 UI 정책을 제공합니다.",
            "로그 출력을 보내기위한 API. 일반적으로 로그를 작성하려면 Log.v (), Log.d (), Log.i (), Log.w () 및 Log.e () 메서드를 사용해야합니다. 그런 다음 logcat에서 로그를 볼 수 있습니다.",
            "속성은 호스트 개체에 보관되는 변경 가능한 값을 나타내는 데 사용할 수있는 추상화입니다. 속성의 set (Object, Object) 또는 get (Object) 메서드는 호스트 객체의 비공개 필드 또는 \"setter\"및 \"getter\"메서드를 통해 구현하거나 다른 메커니즘을 통해 구현할 수 있습니다.",
            "ArraySet은 전통적인 HashSet보다 메모리 효율이 높도록 설계된 일반적인 세트 데이터 구조입니다. 이 디자인은 ArrayMap과 매우 유사하며 모든 문제점이 설명되어 있습니다. 그러나이 구현은 ArrayMap과 별개이므로 Object 배열에는 매핑의 쌍 대신에 집합의 각 항목에 대해 하나의 항목 만 포함됩니다.",
            "표준 시간대와 관련된 유틸리티 메서드가 포함 된 클래스입니다."
    };
}

