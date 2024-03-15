// #include <stdio.h>
// #include <string.h>
//
// int main() {
//   char str[30];
//   char output[30];
//
//   printf("input: ");
//   gets(str);
//
//   int len = strlen(str);
//   if (len <= 2) return 0;
//
//   int i = 1;
//   for (i; i < strlen(str) - 1; i++) {
//     output[i - 1] = str[i];
//   }
//   output[i] = '\0';
//
//   printf("\n");
//   printf("result: %s\n", output);
//
//   return 0;
// }

#include <stdio.h>
#include <string.h>

void processString(char input[]) {
    // 입력된 문자열의 길이가 2 이하인 경우 종료
    if (strlen(input) <= 2) {
        printf("입력된 문자열의 길이가 2 이하입니다. 프로그램을 종료합니다.\n");
        return;
    }

    // 문자열의 첫 번째 글자와 마지막 글자를 제외한 문자열을 만듭니다.
    char result[strlen(input) - 2];
    strcpy(result, input + 1);
    result[strlen(input) - 2] = '\0';

    // 결과 출력
    printf("첫 번째 글자와 마지막 글자를 제외한 문자열: %s\n", result);
}

int main() {
    // 입력 받을 문자열을 저장할 배열
    char input[100];

    // 사용자로부터 문자열 입력 받기
    printf("문자열을 입력하세요: ");
    gets(input);

    // 처리 함수 호출
    processString(input);

    return 0;
}
