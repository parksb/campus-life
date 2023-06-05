# FOSS2023-1_final

- 주제: Command Line Applications in Rust 번역
- 저장소: https://github.com/parksb/rust-cli-book-ko-kr
- 번역 결과물: https://parksb.github.io/rust-cli-book-ko-kr/

## 주제 선정 동기

Command Line Applications in Rust는 범용 프로그래밍 언어 러스트(Rust)를 이용해 커맨드라인 애플리케이션을 개발하는 방법에 대해 소개하는 책이다. 독자는 간단한 CLI 애플리케이션을 만들며 러스트의 핵심 개념과 타입 시스템, 툴 체인, 에코시스템을 익히게 된다.

러스트는 높은 성능과 안전성을 확보하기 위한 정적 컴파일 언어로, 모질라 재단에서 독립한 Rust Foundation이 메인테이닝하는 [오픈소스](https://github.com/rust-lang/rust) 프로젝트이다. 러스트는 [Stackoverflow Survey](https://survey.stackoverflow.co/2022/#most-loved-dreaded-and-wanted-language-love-dread)에서 매년 연속으로 "가장 사랑받는 언어"이자, "가장 배우고 싶은 언어" 1위로 선정되고 있다. 이처럼 러스트의 가능성은 충분히 인정받고 있지만, 오너십(Ownership)이라는 특유의 메모리 관리 방식이 큰 러닝커브로 작용하여 배우기 어려운 언어로도 알려져 있다. 이 때문인지 실제 업무에 러스트를 사용하고 있다고 응답한 비율은 순위권에 든 적이 없다.

하지만 러스트는 확실히 실용적인 언어다. 러스트의 메모리 관리 방식은 코드 레벨에서 메모리 세이프티를 강제하기 때문에 런타임에 발생할 수 있는 세그먼트 폴트 등의 문제를 컴파일 타임에 방지할 수 있다. 또한 러스트에는 GC가 없기 때문에 C/C++에 상당하는 성능을 달성할 수 있으며, 이러한 측면에서 C/C++로 작성된 코드베이스를 메모리 세이프하게 개선하기 위한 가장 현실적인 방안으로 주목받고 있다. 실제로 마이크로소프트, 구글, 애플, 클라우드플레어, 삼성 등 많은 기업이 이미 러스트를 후원, 사용하고 있다. 최근에는 리눅스 커널에 러스트 코드가 포함되기도 했고, 많은 CLI 도구가 러스트로 다시 작성되고 있다. (`cat`→`bat`, `find`→`fd`, etc.)

나는 러스트의 문제의식과 철학을 강력히 지지하는 사용자로서 러스트 생태계에 기여하고 싶었다. 그러던 중 Command Line Applications in Rust 책을 찾게 되었고, 러스트로 CLI 도구를 만드는 책의 내용이 오픈소스SW입문 수업에서 배운 내용과도 일맥상통하는 부분이 있는 것 같아서 주제로 선정하게 되었다.

Command Line Applications in Rust는 러스트 코어팀의 CLI Working Group에서 공식적으로 작성한 책이기 때문에 매우 정확한 설명을 포함하고 있고, 그 내용도 상당한 공신력이 있다. 하지만 책의 훌륭한 내용에 비해 사람들에게 잘 알려지지는 않았고, 언어도 영문과 중문으로만 제공되고 있다. 따라서 이를 한국어로 번역했을 때 러스트에 관심 있는 사람들에게 큰 도움이 될 수 있을 것으로 생각한다.

## 상세

번역을 진행하며 겪은 어려움과 그 어려움을 극복한 방법, 높은 품질의 번역을 위해 노력한 점에 대해 설명하고자 한다.

- 번역해야 할 텍스트가 생각보다 많은 편이었고, 러스트와 리눅스에 대한 이해가 필요했다.
- 문체와 각종 기술 용어, 고유 명사 등은 이제 막 러스트를 공부하기 시작할 때 가장 먼저 보게 되는 책 The Rust Programming Language(TRPL)의 번역을 최대한 따랐다. TRPL은 이 책에서도 자주 인용하는 책이기 때문에 일관된 톤앤매너를 따르는 것이 중요하다고 판단했다. 어색한 번역투를 지양하고, 원어로 통용되는 용어(shell, panic 등)는 직역하는 대신 음차했다.
  - 콜론으로 이어진 문장을 번역했을 때 어색한 경우에는 자연스러운 방식으로 문장을 재구성했다: `It has one problem, though: We don’t store the original error, only its string representation.`→ `그러나 원본 에러를 저장하지 않고 문자열만 보여준다는 문제가 있습니다.`
  - 가주어를 '그것은'과 같이 번역하지 않고 단어를 반복 언급하여 한국어로 자연스럽게 읽히도록 번역했다.
  - 외부 문서(위키피디아, MS Docs 등) 인용에 한국어로 번역된 문서가 있는 경우, 번역된 문서를 인용했다.
- 원본 저장소에 [PR](https://github.com/rust-cli/book/pull/219)을 보내 내 번역본으로 향하는 링크를 추가했다.
- mdBook으로 빌드해 누구나 웹으로 책을 읽을 수 있도록 했다. 이를 위해 푸시할 때마다 자동으로 문서를 빌드, GitHub Pages로 배포하는 [워크플로우](https://github.com/parksb/rust-cli-book-ko-kr/blob/master/.github/workflows/deploy.yml)를 작성했다.
- 러스트의 문법이나 개념, 입문자를 위한 튜토리얼 자료는 많지만, 러스트를 이용한 애플리케이션 개발에 대해 밀도 높게 다루는 문서는 많지 않다. 심지어 한국어 문서는 더더욱 찾기 어렵기 때문에, 러스트 문서를 한국어로 번역하는 기여에 큰 가치가 있다고 생각한다.

## 감상

Command Line Applications in Rust를 통해 더 많은 한국 개발자들이 러스트를 접하고, 러스트의 문제의식과 철학에 공감할 수 있다면 좋겠다. 특히 러스트의 대략적인 문법과 개념은 살펴봤지만, 아직 완결된 프로그램을 만들어 보지 못한 사람들이 Command Line Applications in Rust로 시작해 보면 좋을 것 같다.

## 부록

- [원본 저장소와의 차이](diffs): `git diff upstream/master origin/master > diffs`
- [변경 내역](changelog): `git log b121539.. > changelog`
- 번역 저장소: https://github.com/parksb/rust-cli-book-ko-kr
- 번역 결과물: https://parksb.github.io/rust-cli-book-ko-kr/
- 원본 저장소: https://github.com/rust-cli/book
