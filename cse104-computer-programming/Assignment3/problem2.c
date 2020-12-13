/*
Assignment 3: Problem 2
������ ���� ä���� �迭�� �ٷ�� ���α׷�.

Written by: �̵���а� 201700000 �ڼ���
Date: 2017.11.14
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR1_LENG 30 // arr1 ����
#define ARR2_LENG 50 // arr2 ����

#define RAND_MAX 20 // ���� �ִ� ����
#define LINE_ITEM_NUM 10 // �� ���ο� ����� ��� ����

void createArrayElements(int arr[], int arrLeng);
void printArrayElements(int arr[], int arrLeng);
int sumArrayElements(int arr[], int arrLeng);
void changeArrayElements(int arr[], int arrLeng);

int main(void) {
	int arr1[ARR1_LENG];
	int arr2[ARR2_LENG];

	createArrayElements(arr1, ARR1_LENG);
	createArrayElements(arr2, ARR2_LENG);

	printArrayElements(arr1, ARR1_LENG);
	printArrayElements(arr2, ARR2_LENG);
 
	printf("sum of arr1: %d\n", sumArrayElements(arr1, ARR1_LENG));
	printf("sum of arr2: %d\n\n", sumArrayElements(arr2, ARR2_LENG));

	changeArrayElements(arr1, ARR1_LENG);
	changeArrayElements(arr2, ARR2_LENG);

	printArrayElements(arr1, ARR1_LENG);
	printArrayElements(arr2, ARR2_LENG);

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

// �迭�� ��� ��Ҹ� ���� ��ȯ�Ѵ�.
int sumArrayElements(int arr[], int arrLeng) {
	int sum = 0;

	for (int i = 0; i < arrLeng; i++) {
		sum += arr[i];
	}

	return sum;
} // sumArrayElements

// �迭�� ù ��° ��ҿ� ������ ��Ҹ� �ٲ۴�.
void changeArrayElements(int arr[], int arrLeng) {
	int temp = arr[0];

	arr[0] = arr[arrLeng - 1];
	arr[arrLeng - 1] = temp;
} // changeArrayElements