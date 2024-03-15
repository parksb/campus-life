#include <stdio.h>

int sum_n(int n);

int main(void) {
  int n = 0;

  printf("n을 입력하시오: ");
  scanf("%d", &n);
  printf("sum_n(%d) = %d\n", n, sum_n(n));

  return 0;
}

int sum_n(int n) {
  if (n <= 0) return 0;
  return sum_n(n - 1) + (2 * n + 1);
}
