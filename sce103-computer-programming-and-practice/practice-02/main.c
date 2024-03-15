#include <stdio.h>

int main() {
    float meter = 0.0f;
    printf("meter 단위의 길이를 입력하시오: ");
    scanf("%f\n", &meter);
    printf("결과:\n");
    printf("%.2f inches\n", meter * 39.37f);
    printf("%.2f feet\n", meter * 3.281f);

    float celsius = 0.0f;
    printf("섭씨 온도를 입력하시오: ");
    scanf("%f", &celsius);
    printf("섭씨 %.2f도는 화씨 %.2f도이다.\n", celsius, celsius * 1.8f + 32);

    return 0;
}
