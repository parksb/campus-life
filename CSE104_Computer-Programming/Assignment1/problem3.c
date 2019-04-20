/*
Assignment 1: Problem 3
�������� ���� ��ȭ�ϴ� ������� �µ��� ����ϴ� ���α׷�.

2017.09.18
�̵���а� 201700000 �ڼ���

scanf�� �����̽� ������ scanf_s�� ��ü��.
*/

#include<stdio.h>

int main(void) {
	int hour;
	int minute;
	double elapseTime; // �ð��� �ð� ������ ��ȯ�� ��� �ð�
	double temperature; // ���� �µ�

	printf("��� �ð��� �Է��Ͻÿ� (�ð� ��): ");
	scanf_s("%d %d", &hour, &minute);

	elapseTime = (double)minute / 60 + hour;
	temperature = ((4 * (elapseTime * elapseTime)) / (elapseTime + 2)) - 20;

	printf("�������κ��� %d�ð� %d��(%.1f �ð�)�� ���� ���� ������� �µ��� ���� %.2f���̴�.\n", hour, minute, elapseTime, temperature);

	return 0;
}