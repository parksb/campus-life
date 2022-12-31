/*
���� ���� ���α׷� 2017.10.15
�̵�� 201700000 �ڼ���
*/

#include <stdio.h>
#define MAX_DIGIT 11 // �Է� �ִ� ����
#define MAX_SINGLE_DIGIT 9 // �ִ� single-digit ��

int main(void) {
	char chNumber1[MAX_DIGIT] = { 0 };
	char chNumber2[MAX_DIGIT] = { 0 };

	int number1[MAX_DIGIT] = { 0 };
	int number2[MAX_DIGIT] = { 0 };
	int result[MAX_DIGIT] = { 0 };

	int number1Leng = 0;
	int number2Leng = 0;
	int resultLeng = 0;

	int numberSum = 0;

	// �Է�

	printf("Enter number1 >> ");
	scanf_s("%s", chNumber1, sizeof(chNumber1));

	for (int i = 1, j = 0; chNumber1[i] >= 0; i++, j++) {
		number1[i] = chNumber1[j] - '0'; // ������ ��Ҹ� ���������� ��ȯ.
		number1Leng++;
	}

	printf("Enter number2 >> ");
	scanf_s("%s", chNumber2, sizeof(chNumber2));

	for (int i = 1, j = 0; chNumber2[i] >= 0; i++, j++) { 
		number2[i] = chNumber2[j] - '0'; // ������ ��Ҹ� ���������� ��ȯ.
		number2Leng++;
	}

	// ����

	resultLeng = (number1Leng > number2Leng) ? (number1Leng) : (number2Leng);

	for (int i = 0; i <= resultLeng; i++) {
		numberSum = number1[number1Leng] + number2[number2Leng];

		if (numberSum > MAX_SINGLE_DIGIT) { // �ø��ؾ� �ϴ� ���
			if (number1Leng - 1 < 0 || number2Leng - 1 > 0) {
				number2[number2Leng - 1]++;
			} else {
				number1[number1Leng - 1]++;
			}

			numberSum %= 10; // 1�� �ڸ� ���� �Ҵ�.		
		}

		if (--number1Leng < 0) {
			number1Leng = 0;
		} 

		if (--number2Leng < 0) {
			number2Leng = 0;
		}

		result[i] = numberSum;
	}

	// ���

	printf("\n%s + %s = ", chNumber1, chNumber2);

	if (!result[resultLeng]) {
		resultLeng--;
	}

	for (int i = resultLeng; i >= 0; i--) {
		printf("%d", result[i]);
	}

	printf("\n");

	return 0;
}