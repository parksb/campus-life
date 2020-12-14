/*
�ǽ�1-2: ���� �̵ �ﰢ�� �׸���
�̵�201700000 �ڼ���
scanf�� ���� �̽� ������ scanf_s�� ��ü��.
*/

#include <stdio.h>

int main (void) {
	int length;

	printf("Input size >> ");
	scanf_s("%d", &length);

	if (length < 0) {
		printf("The value must be greater than zero.\n");
	} else {
		for (int i = 0; i <= length; i++) {
			for (int j = 0; j < i; j++) {
				printf("*");
			}
			printf("\n");
		}
	}

	return 0;
}