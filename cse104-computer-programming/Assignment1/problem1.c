/*
Assignment 1: Problem 1
���� ����� �Է��ϸ� �ý� ����� ����ϴ� ���α׷�

2017.09.18 
�̵���а� 201700000 �ڼ���

scanf�� �����̽� ������ scanf_s�� ��ü��.
*/

#include <stdio.h>
#define COST_PER_MILE 1.5

int main(void) {
	double mileAtDepart;
	double mileAtArrive;
	double runMile; // �� ���� �Ÿ�
	double runCost; // �� ���

	printf("�ý� ��� ����\n");
	printf("��� ���� ���� ��ϰ� ��ġ: ");
	scanf_s("%lf", &mileAtDepart);
	printf("���� ���� ���� ��ϰ� ��ġ: ");
	scanf_s("%lf", &mileAtArrive);

	runMile = mileAtArrive - mileAtDepart;
	runCost = runMile * COST_PER_MILE;
	
	printf("�� %.1f ������ ���������� ����� ���� �� $%.2f����, �� ����� $%.2f�Դϴ�.\n", runMile, COST_PER_MILE, runCost);
	
	return 0;
}