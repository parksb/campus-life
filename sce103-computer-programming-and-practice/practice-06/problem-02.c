#include <stdio.h>

int input_data_n(int n, int k) {
  if (n == 0) return k;

  int data;

  scanf("%d", &data);
  printf("%d ", data);

  if (data < k) {
    return input_data_n(n - 1, data);
  } else {
    return input_data_n(n - 1, k);
  }
}

int main() {
  int n;

  printf("입력할 데이터의 개수: ");
  scanf("%d", &n);

  int init;
  scanf("%d", &init);
  printf("%d ", init);

  int k = input_data_n(n - 1, init);
  printf("\n가장 작은 값은 ");
  printf("%d", k);
}
