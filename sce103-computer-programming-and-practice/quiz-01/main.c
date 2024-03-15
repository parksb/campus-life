///////////////////////////////////////////////////////////////////////////////////////////
//  학과:
//  학번:
//  이름:
///////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************
 main()을 실행한 결과는 다음과 같은 형태로 출력되어야 함.

    Problem 1
    세 개의 정수를 입력 하시오: 32 50 100
    합계: 32 + 50 + 100 = 182
    평균: (32 + 50 + 100)/3 = 60.7

    Problem 2
    Kor/Eng/Math/Sci: 80.5 95 91.5 75

    Exam Scores
    *****************************
    * Kor  * Eng  * Math * Sci  *
    *****************************
    * 80.5 * 95.0 * 91.5 * 75.0 *
    *****************************
    * Average     *        85.5 *
    *****************************

    Problem 3
    시간을 입력하시오: 2
    분을 입력하시오: 35
    초를 입력하시오: 20
    2 시 35 분 20 초는 9320 초이다.

******************************************************************/


#include <stdio.h>

void threeValuesSumAndMean();
void examScores();
void timeConverter();

int main() {

    printf("\nProblem 1\n");
    threeValuesSumAndMean();

    printf("\nProblem 2\n");
    examScores();

    printf("\nProblem 3\n");
    timeConverter();

    return 0;
}

void threeValuesSumAndMean() {
    int a, b, c;

    printf("세 개의 정수를 입력 하시오: ");
    scanf("%d %d %d", &a, &b, &c);

    printf("합계: %d + %d + %d = %d\n", a, b, c, a + b + c);
    printf("평균: (%d + %d + %d)/3 = %.1lf\n", a, b, c, (a + b + c) / 3.0);
}

void examScores() {
    double kor, eng, math, sci;

    printf("Kor/Eng/Math/Sci: ");
    scanf("%lf %lf %lf %lf", &kor, &eng, &math, &sci);

    printf("Exam Scores\n");
    printf("*****************************\n");
    printf("* Kor  * Eng  * Math * Sci  *\n");
    printf("*****************************\n");
    printf("* %.1lf * %.1lf * %.1lf * %.1lf *\n", kor, eng, math, sci);
    printf("*****************************\n");
    printf("* Average     *        %.1lf *\n", (kor + eng + math + sci) / 4.0);
    printf("*****************************\n");
}

int getHours();
int getMinutes();
int getSeconds();
int convertInSecond(int h, int m, int s);

void timeConverter() {
    int h, m, s, t;
    h = getHours();
    m = getMinutes();
    s = getSeconds();
    t = convertInSecond(h, m, s);
    // printf를 이용한 결과 출력

    printf("%d 시 %d 분 %d 초는 %d 초이다.\n", h, m, s, t);
}

int getHours() {
    int h;
    printf("시간을 입력하시오: ");
    scanf("%d", &h);
    return h;
}

int getMinutes() {
    int m;
    printf("분을 입력하시오: ");
    scanf("%d", &m);
    return m;
}

int getSeconds() {
    int s;
    printf("초를 입력하시오: ");
    scanf("%d", &s);
    return s;
}

int convertInSecond(int h, int m, int s) {
    return h * 3600 + m * 60 + s;
}
