/*
�ǽ�4: ������ ���ϱ�
�̵�� 201700000 �ڼ���
scanf�� ���� �̽� ������ scanf_s�� ��ü��.
*/

#include <stdio.h>

int main(void) {
	int input;
	int divisorSum = 0;

	printf("Input number >> ");
	scanf_s("%d", &input);

	if (input < 0) {
		printf("The number must be greater than zero.\n");
	} else {
		for (int i = 1; i <= input; i++) {
			for (int j = 1; j < i; j++) {
				if (i % j == 0) {
					divisorSum += j;
				}
			}

			if (divisorSum == i) {
				printf("%d\n", i);
			}

			divisorSum = 0;
		}
	}

	return 0;
}