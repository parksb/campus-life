# Hexdump

[Hexadecimal dump in C by grapsus](http://grapsus.net/blog/post/Hexadecimal-dump-in-C)를 개선했다. 운영체제 분야라기 보다는 리눅스 개발 환경에 익숙해지라는 의도로 나온 과제같다. 변경 사항은 다음과 같다:

- 텍스트 입력 방식 변경: 파일에 저장된 텍스트를 읽어 16진수 ASCII코드로 변환.
- 한 줄에 출력되는 문자 수 변경: 한 줄에 4바이트씩 출력.
- 출력 형식 개선: 프로그램 이름은 변환에서 제외, 대신 텍스트 파일 이름을 출력.
