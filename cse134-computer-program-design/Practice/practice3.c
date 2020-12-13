/*
�ǽ�3: �Ǻ���ġ ���� ����
�̵�201700000 �ڼ���
scanf�� ���� �̽� ������ scanf_s�� ��ü��.
*/

#include <stdio.h>

int main(void) {
	int input;
	int currentNumber = 0;
	int firstNumber = 0;
	int secondNumber = 1;

	printf("Input number >> ");
	scanf_s("%d", &input);

	if (input < 0) {
		printf("The number must be greater than zero.\n");
	} else if (input == 0) {
		printf("%d\n", firstNumber);
	} else {
		printf("%d\n%d\n", firstNumber, secondNumber);
	}

	while (1) {
		currentNumber = firstNumber + secondNumber;

		if (currentNumber > input) {
			break;
		}

		printf("%d\n", currentNumber);

		firstNumber = secondNumber;
		secondNumber = currentNumber;
	}

	return 0;
}