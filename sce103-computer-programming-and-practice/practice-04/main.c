#include <stdio.h>

int converterFromFtoC();
int computeRefrigeratorTemp();

int main() {
    converterFromFtoC();
    computeRefrigeratorTemp();

    return 0;
}

double getF();
double convertFtoC(double F);
void printConversionResult(double F, double C);

int converterFromFtoC() {
    double F, C;

    F = getF();
    C = convertFtoC(F);

    printConversionResult(F, C);

    return 1;
}

double getF() {
    double F;

    printf("화씨 온도를 입력하시오: ");
    scanf("%lf", &F);

    return F;
}

double convertFtoC(double F) {
    return (F - 32) / 1.8;
}

void printConversionResult(double F, double C) {
    printf("화씨 %.2lf도는 섭씨 %.2lf이다.\n", F, C);
}

double convertTime(int h, int m);
double getTemperature(double t);

int computeRefrigeratorTemp() {
    int hour, min;
    double t, T;

    printf("경과 시간을 입력하시오(시간 분): ");
    scanf("%d %d", &hour, &min);

    t = convertTime(hour, min);
    T = getTemperature(t);

    printf("정전으로부터 %d시간 %d분(%.2lf 시간)이 지나 현재 냉장고의 온도는 섭씨 %.2lf도이다.", hour, min, t, T);

    return 0;
}

double convertTime(int h, int m) {
    return h + m / 60.0;
}

double getTemperature(double t) {
    return (4 * t * t) / (t + 2)  - 20;
}
