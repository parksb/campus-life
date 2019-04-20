/*
Problem 1: ���ڿ��� �����ϴ� ���α׷�
Author: �̵�� 201700000 �ڼ���
Date: 2017.12.6
*/

#define _CRT_SECURE_NO_WARNINGS // Visual Studio�� ���� ��� ����

#include <stdio.h>
#include <string.h>

void reverse_string(char *str);
void display_num_of_vowels_and_consonants(char *str);
void display_past_tense(char *str);

int main(void) {
	char str[128];
	char repeat;
	int cmd;

	do {
		printf("Please enter a string: ");
		scanf(" %s", str);

		printf("-------------------------------------------------------------\n");

		printf("Menu\n");
		printf("1) reverse the string and display it\n");
		printf("2) display the total number of vowels and consonants\n");
		printf("3) display the past tense of the verb\n");

		printf("-------------------------------------------------------------\n");

		printf("Enter the number: ");
		scanf("%d", &cmd);

		switch (cmd) {
		case 1:
			reverse_string(str);
			printf("%s\n", str);
			break;
		case 2:
			display_num_of_vowels_and_consonants(str);
			break;
		case 3:
			display_past_tense(str);
			break;
		}

		printf("Try again? ");
		scanf(" %c", &repeat);
	} while (repeat == 'y');

	return 0;
}

// ���ڿ��� ���� ������ �ٲ۴�.
void reverse_string(char *str) {
	int str_len = strlen(str) - 1;
	char temp;

	for (int i = 0, j = str_len; i < str_len / 2; i++, j--) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
} // reverse_string

// ���ڿ����� ������ ������ ������ ����Ѵ�.
void display_num_of_vowels_and_consonants(char *str) {
	int str_len = strlen(str);
	int vowel = 0;
	int consonant = 0;

	for (int i = 0; i < str_len; i++) {
		if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u') {
			vowel++;
		} else {
			consonant++;
		}
	}

	printf("The total number of vowels: %d\n", vowel);
	printf("Thetotal number of consonants: %d\n", consonant);
} // display_num_of_vowels_and_consonants

// ������ �������� ����Ѵ�.
void display_past_tense(char *str) {
	int str_len = strlen(str) - 1;

	if (str[str_len] == 'e') { // �ܾ e�� ������ ���
		strncat(str, "d", 128);
	} else if (str[str_len - 1] == 's' && str[str_len] == 's') { // �ܾ ss�� ������ ���
		strncat(str, "ed", 128);
	} else if (str[str_len - 1] == 'g' && str[str_len] == 'h') { // �ܾ gh�� ������ ���
		strncat(str, "ed", 128);
	} else {
		strncpy(str, "The verb may have an irregular past tense", 128);
	}

	printf("%s\n", str);
} // display_past_tense