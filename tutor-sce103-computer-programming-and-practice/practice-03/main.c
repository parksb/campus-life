#include <stdio.h>

int main() {
    int amount = 0;
    int coin500 = 0, coin100 = 0, coin50 = 0, coin10 = 0;

    printf("Enter the amount of change: ");
    scanf("%d", &amount);

    coin500 = amount / 500;
    amount = amount - coin500 * 500;

    if (amount >= 100) {
        coin100 = amount / 100;
        amount = amount - coin100 * 100;
    }

    if (amount >= 50) {
        coin50 = amount / 50;
        amount = amount - coin50 * 50;
    }

    if (amount >= 10) {
        coin10 = amount / 10;
        amount = amount - coin10 * 10;
    }

    printf("500: %d, 100: %d, 50: %d, 10: %d\n", coin500, coin100, coin50, coin10);
    printf("남은 돈 = %d원\n", amount);
    printf("검산 = %d원\n", coin500 * 500 + coin100 * 100 + coin50 * 50 + coin10 * 10 + amount);

    return 0;
}