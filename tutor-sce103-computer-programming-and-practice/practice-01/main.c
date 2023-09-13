#include <stdio.h>

int main() {
    int num_apples, total_price;
    int APPLE_UNIT_PRICE = 1200;

    printf("사과 개수: ");
    scanf("%d", &num_apples);

    total_price = num_apples * APPLE_UNIT_PRICE;

    printf("사과의 개당 가격은 %d원이며 총 금액은 %d원이다.\n", APPLE_UNIT_PRICE, total_price);

    return 0;
}
