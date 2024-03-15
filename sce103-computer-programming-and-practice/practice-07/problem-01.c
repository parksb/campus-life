#include <stdio.h>

int main() {
  double arr[5], target;

  printf("배열의 값: ");
  scanf("%lf %lf %lf %lf %lf", &arr[0], &arr[1], &arr[2], &arr[3], &arr[4]);

  printf("비교할 값: ");
  scanf("%lf", &target);

  printf("%.1lf보다 큰 값: ", target);
  for (int i = 0; i < 5; i += 1) {
    if (arr[i] > target) {
      printf("%.1lf ", arr[i]);
    }
  }

  return 0;
}
