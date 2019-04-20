/*
Assignment 1: Problem 2
�������� ���ϴ� ������ �ޱ� ���� �ʿ��� �⸻���� �ּ� ������ ����ϴ� ���α׷�.

2017.09.18
�̵���а� 201700000 �ڼ���

scanf�� �����̽� ������ scanf_s�� ��ü��.
*/

#include <stdio.h>

int main(void) {
	char expectGrade; // ��� ����
	double minAvgPoint; // �ʿ��� �ּ� ��� ����
	double currentAvgPoint; // ���� ��� ����
	double examMinScore; // �ʿ��� �⸻���� �ּ� ���� 
	int examRatio; // �⸻���� ������ �ݿ� ����

	printf("�� �������� ����ϴ� ������ �Է��Ͻÿ�: ");
	scanf_s("%c", &expectGrade);
	printf("������ ��� ���� �ʿ��� �ּ� ��� ������ �Է��Ͻÿ�: ");
	scanf_s("%lf", &minAvgPoint);
	printf("���� ��� ������ �Է��Ͻÿ�: ");
	scanf_s("%lf", &currentAvgPoint);
	printf("�⸻���� ������ ��ü �������� �����ϴ� ������ �Է��Ͻÿ�: ");
	scanf_s("%d", &examRatio);

	examMinScore = (minAvgPoint - currentAvgPoint) * (100 / examRatio) + currentAvgPoint;

	printf("�� �������� %c�� ��� ���ؼ��� �⸻���迡�� %.2f���� �޾ƾ� �մϴ�.\n", expectGrade, examMinScore);

	return 0;
}