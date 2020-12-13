/*
�ǽ�2: Up & Down
�̵�201700000 �ڼ���
scanf�� ���� �̽� ������ scanf_s�� ��ü��.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	srand(time(NULL));
	int correct = (rand() % 100) + 1;
	int input;

	do {
		printf("Input number >> ");
		scanf_s("%d", &input);

		if (input < 0) {
			printf("The number must be greater than zero\n");
			break;
		} else if (input > correct) {
			printf("Down\n\n");
		} else if (input < correct) {
			printf("Up\n\n");
		} else { // input == correct
			printf("Correct!\n");
		}
	} while (input != correct);

	return 0;
}