#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_DATA 50

int main()
{
  int arr[NUM_DATA], i, j, num;
  int* odds;

  srand(time(NULL));

  // 1~200 범위 난수 저장
  for(i = 0; i < NUM_DATA; i++) {
    arr[i] = 1 + (rand() % 200);
  }

  // 배열에 저장된 전체 난수 출력
  for(i = 0; i < NUM_DATA; i++) {
    printf("%9d", arr[i]);
    if(i % 10 == 9) printf("\n");
  }

  // 홀수의 개수 세기
  num = 0;
  for(i = 0; i < NUM_DATA; i++) {
    if(arr[i] % 2 != 0) {
      num++;
    }
  }

  // 동적 배열 생성, malloc 사용
  odds = malloc(num * sizeof(int));

  // arr로부터 동적 배열에 홀수를 옮기기
  for(i = 0; i < NUM_DATA; i++) {
    if(arr[i] % 2 != 0) {
      odds[j] = arr[i];
      j++;
    }
  }

  printf("==================\n");

  // 동적 배열에 저장된 홀수 출력하기
  for(i = 0; i < num; i++) {
    printf("%d ", odds[i]);
    if(i % 10 == 9) printf("\n");
  }

  // 동적 배열의 메모리 해제, free 사용
  free(odds);

  return 0;
}
