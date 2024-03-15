/*
�ǽ�1-3: �̵ �ﰢ�� �׸���
�̵�201700000 �ڼ���
scanf�� ���� �̽� ������ scanf_s�� ��ü��.
*/

#include <stdio.h>

int main(void) {
	int length, highest;
	int i, j;

	printf("Input size >> ");
	scanf_s("%d", &length);

	if (length <= 0) {
		printf("The value must be greater than zero.\n");
	} else {
		highest = length / 2;

		for (i = 0; i <= highest; i++) {
			for (j = 0; j <= i; j++) {
				printf("*");
			}
			printf("\n");
		}

		for (i = 0; i < highest; i++) {
			for (j = highest; j > i; j--) {
				printf("*", j);
			}
			printf("\n");
		}
	}

	return 0;
}