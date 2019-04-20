/*
Assignment 3: Problem 1
9�� ���������� ������ �Ǻ��ϴ� ���α׷�.

Written by: �̵���а� 201700000 �ڼ���
Date: 2017.11.14
*/

#include <stdio.h>

int sum_of_digits(int input);

int main(void) {
	int input;
	char repeat; // �ݺ� ����

	do {
		printf("Please enter the number: ");
		scanf_s("%d", &input);

		printf("The sum of digits is %d\n", sum_of_digits(input));

		if (sum_of_digits(input) % 9) {
			printf("It is not divisible by 9\n");
		}
		else { // (sum_of_digits(input) % 9) == 0
			printf("It is divisible by 9\n");
		}

		printf("Try again? ");
		scanf_s(" %c", &repeat);
	} while (repeat == 'y');

	return 0;
}

// ������ �� �ڸ����� ���� ��ȯ�Ѵ�.
int sum_of_digits(int input) {
	int sum = 0;

	while (input > 0) {
		sum += input % 10;
		input /= 10;
	}

	return sum;
} // sum_of_digits