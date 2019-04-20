/*
Assignment 2: Problem 1
���� ��뷮�� ���� ��� ��� ���α׷�

2017.10.11
�̵���а� 201700000 �ڼ���
*/

#include <stdio.h>
#define MIN_CHARGE 100.0 // �ּ� ���

int main(void) {
	double usage; // ������� ���� ��뷮
	double totalCharge;

	printf("Enter the number of units: ");
	scanf_s("%lf", &usage);

	// ��뷮�� ���� ��� �ΰ�
	if (usage <= 200) {
		totalCharge = usage * 0.8;
	} else if (usage <= 300) {
		totalCharge = usage * 0.9;
	} else if (usage > 300) {
		totalCharge = usage;
	}

	// �ּ� ��� �� �߰� ��� �ΰ�
	if (totalCharge < 100) {
		totalCharge = MIN_CHARGE; 
	} else if (totalCharge > 400) {
		totalCharge += totalCharge * 0.15;
	}

	printf("Charges: %.1f\n", totalCharge);

	return 0;
}