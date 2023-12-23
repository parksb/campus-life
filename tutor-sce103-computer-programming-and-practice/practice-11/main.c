#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fp;
  FILE *fp1;

  int vals[300], vals2[300];

  for (int i = 0; i < 300; i++) {
    vals[i] = rand() % 1001;
  }

  for (int i = 0; i < 30; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%d\t", vals[i * 10 + j]);
    }
    printf("\n");
  }

  fp = fopen("data.txt", "wt");
  for (int i = 0; i < 30; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(fp, "%d\t", vals);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);

  fp1 = fopen("data.txt", "r");
  for (int i = 0; i < 30; i++) {
    for (int j = 0; j < 10; j++) {
      fscanf(fp1, "%d", &vals2[i * 10 + j]);
    }
  }
  fclose(fp1);

  for (int i = 0; i < 300; i++) {
    if (vals[i] != vals2[i]) {
      printf("NO!\n");
      return 0;
    }
  }

  printf("DONE!\n");

  return 0;
}
