/*
Problem 2: ���Ͽ��� �л� ������ �а� ����ϴ� ���α׷�
Author: �̵�� 201700000 �ڼ���
Date: 2017.12.6
*/

#define _CRT_SECURE_NO_WARNINGS // Visual Studio�� ���� ��� ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stu_record { // �л� ����
	char first_name[20];
	char last_name[20];
	int id;
	int quiz[3]; // [0]: Quiz1, [1]: Quiz2, [2]: Quiz3
	int exam[2]; // [0]: Midterm, [1]: Final
	double total;
	char grade;
};

int main(void) {
	FILE *data;

	int row_num = 0; // �л� ��
	double quiz_total;
	double exam_total;
	double quiz_avg[3] = {0}; // ���� ���
	double exam_avg[2] = {0}; // ���� ���
	char stu_fullname[40];

	data = fopen("stu_record.txt", "r");
	fscanf(data, "%d\n", &row_num);

	struct stu_record *stu = (struct stu_record *)malloc(sizeof(struct stu_record) * row_num);

	// ���Ͽ��� ��� �л� ������ ��ȸ�ϰ� ����
	for (int i = 0; i < row_num; i++) {
		fscanf(
			data, "%s %s\t%d\t%d\t%d\t%d\t%d\t%d",
			stu[i].first_name,
			stu[i].last_name,
			&stu[i].id,
			&stu[i].quiz[0],
			&stu[i].quiz[1],
			&stu[i].quiz[2],
			&stu[i].exam[0],
			&stu[i].exam[1]
		);

		// ���� ����� ���� �ջ�
		quiz_avg[0] += stu[i].quiz[0] / (double)row_num;
		quiz_avg[1] += stu[i].quiz[1] / (double)row_num;
		quiz_avg[2] += stu[i].quiz[2] / (double)row_num;

		// ���� ����� ���� �ջ�
		exam_avg[0] += stu[i].exam[0] / (double)row_num;
		exam_avg[1] += stu[i].exam[1] / (double)row_num;

		// �ش� �л� ���� ���
		quiz_total = (stu[i].quiz[0] + stu[i].quiz[1] + stu[i].quiz[2]) / 15.0;
		exam_total = (stu[i].exam[0] + stu[i].exam[1]) * 0.4;
		stu[i].total = quiz_total + exam_total;

		// �ش� �л� grade ����
		if (stu[i].total >= 90) {
			stu[i].grade = 'A';
		} else if (stu[i].total >= 80) {
			stu[i].grade = 'B';
		} else if (stu[i].total >= 70) {
			stu[i].grade = 'C';
		} else if (stu[i].total >= 60) {
			stu[i].grade = 'D';
		} else {
			stu[i].grade = 'F';
		}
	}
	
	fclose(data);

	// ���
	printf("%-20s\t%10s%10s%10s%10s%10s%10s%10s%10s\n", "Name", "ID", "Quiz 1", "Quiz 2", "Quiz 3", "Midterm", "Final", "Total", "Grade");
	printf("------------------------------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < row_num; i++) {
		// �ٸ����� ���� �̸� ����
		strncpy(stu_fullname, stu[i].first_name, 20);
		strncat(stu_fullname, " ", 1);
		strncat(stu_fullname, stu[i].last_name, 20);
		
		printf(
			"%-20s\t%10d%10d%10d%10d%10d%10d%10.2f%10c\n",
			stu_fullname,
			stu[i].id,
			stu[i].quiz[0],
			stu[i].quiz[1],
			stu[i].quiz[2],
			stu[i].exam[0],
			stu[i].exam[1],
			stu[i].total,
			stu[i].grade
		);
	}

	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("%-20s\t\t%12.1f%10.1f%10.1f%10.1f%10.1f\n", "Average scores", quiz_avg[0], quiz_avg[1], quiz_avg[2], exam_avg[0], exam_avg[1]);
	printf("------------------------------------------------------------------------------------------------------------------------\n");

	free(stu);
	return 0;
}

