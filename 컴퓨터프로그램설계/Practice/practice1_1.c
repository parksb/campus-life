/*
�ǽ�1-1: �簢�� �׸���
�̵�201700000 �ڼ���
scanf�� ���� �̽� ������ scanf_s�� ��ü��.
*/

#include <stdio.h>

int main (void) {
	int width, height;

	printf("Input width and height >> ");
	scanf_s("%d %d", &width, &height);

	if(width < 0 || height < 0) {
		printf("The values must be greater than zero.\n");
	} else {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				printf("*");
			}
			printf("\n");
		}
	}

	return 0;
}