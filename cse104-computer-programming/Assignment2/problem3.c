/*
Assignment 2: Problem 3
����ڰ� 1~100������ �� n�� �Է��ϸ� 
6���� ���������鼭 4�δ� ���������� �ʴ� 
1���� n������ ������ ������ ����ϴ� ���α׷�

2017.10.11
�̵���а� 201700000 �ڼ���
*/

#include <stdio.h>

int main(void) {
	int input;
	int sumOfResult = 0;
	int numOfResult = 0;

	printf("Enter a number: ");
	scanf_s("%d", &input);

	while (input <= 0 || input > 100) { // �Է°��� 1���� 100������ ���� �ƴ� ���
		printf("Error!\n");
		
		printf("Enter a number: ");
		scanf_s("%d", &input);
	}

	printf("Result:\n");
	printf("List: ");

	for (int i = 0; i <= input; i++) {
		if (!(i % 6) && (i % 4)) { // 6���� ��������, 4�� �������� �ʴ� ���
			printf("%d ", i);
			sumOfResult += i;
			numOfResult++;
		}
	}

	printf("\nSum: %d\n", sumOfResult);
	printf("Total number: %d\n", numOfResult);

	return 0;
}