/*
Assignment 2: Problem 2
��꼭 ��� ���α׷�

2017.10.11
�̵���а� 201700000 �ڼ���
*/

#include <stdio.h>
#define STUDENT_DISCOUNT_RATE 0.2 // �л� ������
#define TAX_RATE 0.05 // ����

int main(void) {
	double totalPurchase; // �� ���� �ݾ�
	double totalDiscount; // �� ���� �ݾ� (�� ���� �ݾ� - �л� ���� �ݾ�)
	double totalTax; // �� ���� (�� ���� �ݾ� * ����)
	double studentDiscount; // �л� ���� �ݾ� (�� ���� �ݾ� * �л� ������)
	
	char isStudent;
	char isRepeat;

	do {
		printf("Please enter the purchase total: ");
		scanf_s("%lf", &totalPurchase);

		printf("Are you a student? ");
		scanf_s(" %c", &isStudent);

		printf("---------------------------------------------------\n");
		printf("%-25s %18s %6.2f\n", "Total purchases", "$", totalPurchase);

		if (isStudent == 'y') {
			studentDiscount = totalPurchase * STUDENT_DISCOUNT_RATE;
			totalDiscount = totalPurchase - studentDiscount;
			totalPurchase -= studentDiscount; // �л� ���� ����

			printf("%-25s %25.2f\n", "Student's discount (20%)", studentDiscount);
			printf("%-25s %25.2f\n", "Discounted total", totalDiscount);
		}

		totalTax = totalPurchase * TAX_RATE;
		totalPurchase += totalTax; // ���� �ΰ�

		printf("%-25s %25.2f\n", "Sales tax (5%)", totalTax);
		printf("%-25s %18s %6.2f\n", "Total", "$", totalPurchase);
		printf("---------------------------------------------------\n");

		printf("Try again? ");
		scanf_s(" %c", &isRepeat);
	} while (isRepeat == 'y');

	return 0;
}