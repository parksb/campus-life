/*
Assignment 3: Problem 3
�迭�� �ִ� ���ڰ� ���� �� ���� �ִ��� ����ϴ� ���α׷�.

Written by: �̵���а� 201700000 �ڼ���
Date: 2017.11.14
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_LENG 40 // �迭 ����

#define RAND_MAX 20 // ���� �ִ� ����
#define LINE_ITEM_NUM 10 // �� ���ο� ����� ��� ����

void createArrayElements(int arr[], int arrLeng);
void printArrayElements(int arr[], int arrLeng);
void sortArrayElements(int arr[], int arrLeng);
void countNumber(int arr[], int arrLeng);

int main(void) {
	int arr[ARR_LENG] = {0};

	createArrayElements(arr, ARR_LENG);
	printArrayElements(arr, ARR_LENG);
	countNumber(arr, ARR_LENG);

	return 0;
}

// �迭�� ��� ��ҿ� ������ �����Ѵ�.
void createArrayElements(int arr[], int arrLeng) {
	srand(time(NULL));
	int num = 0;

	for (int i = 0; i < arrLeng; i++) {
		num = (rand() % RAND_MAX) + 1;
		arr[i] = num;
	}
} // createArrayElements

// �迭�� ��Ҹ� ��� ����Ѵ�.
void printArrayElements(int arr[], int arrLeng) {
	int index = 0;

	for (int i = 0; i < arrLeng / LINE_ITEM_NUM; i++) {
		for (int j = 0; j < LINE_ITEM_NUM; j++) { // �� ���ο� LINE_NUM���� ���
			printf("%-5d", arr[index]);
			index++;
		}
		printf("\n");
	}
	printf("\n");
} // printArrayElements

// selection sort�� �̿��� �迭�� ��Ҹ� �������� �����Ѵ�. (countNumber���� ȣ��)
void sortArrayElements(int arr[], int arrLeng) {
	int temp;

	for (int i = 0; i < (arrLeng - 1); i++) {
		for (int j = (i + 1); j < arrLeng; j++) {
			if (arr[i] > arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
} // sortArrayElements

// �迭�� �ִ� ���ڰ� ���� �� ���� �ִ��� ����, ����Ѵ�.
void countNumber(int arr[], int arrLeng) {
	int count = 0;
	int target; // ã�� ����

	sortArrayElements(arr, arrLeng); // �迭�� ����

	printf("%2s %7s\n", "N", "Count");

	target = arr[0];
	for (int i = 0; i <= arrLeng; i++) {
		if (target == arr[i]) {
			count++;
		} else {
			printf("%2d %7d\n", target, count);

			count = 1;
			target = arr[i];
		}
	}
} // countNumber