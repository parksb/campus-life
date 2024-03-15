#include <stdio.h>
#include <stdlib.h>

#define NUM_DATA 20

void swap(double *a, double *b) {
  double temp = *a;
  *a = *b;
  *b = temp;
}

void smallest_ten_numbers(double data[], int n, double *result) {
  for (int i = 0; i < n; i++) {
    data[i] = (rand() % 11) / 10.0;
  }

  for (int pos = 0; pos < n-1; pos++) {
    for (int i = n-2; i >= pos; i--) {
      if (data[i] > data[i+1]) {
        swap(&(data[i]), &(data[i+1]));
      }
    }
  }

  for (int i = 0; i < n; i++) {
    result[i] = data[i];
  }
}


int main() {
  double arr[NUM_DATA], i;
  double smten[10];

  smallest_ten_numbers(arr, NUM_DATA, smten);

  for (int i = 0; i < 10; i++) {
    printf("%d: %lf\n", i, smten[i]);
  }

  return 0;
}
