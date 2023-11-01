#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

void area_perimeter(float radius, float *area, float *perimeter);

int main() {
  float radius;
  float area, perimeter;

  printf("원의 반지름을 입력하시오: ");
  scanf("%f", &radius);

  area_perimeter(radius, &area, &perimeter);

  printf("원의 면적은 %.3f, 둘레는 %.3f 입니다.\n", area, perimeter);

  return 0;
}

void area_perimeter(float radius, float* area, float* perimeter) {
  *area = M_PI * radius * radius;
  *perimeter = 2 * M_PI * radius;
}
