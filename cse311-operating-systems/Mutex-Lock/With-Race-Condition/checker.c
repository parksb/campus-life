#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	FILE* file;
	char time[128];
	char time2[128];

	char thread[128];
	char thread2[128];

	int counter1 = 0;
	int counter2 = 0;

	int flag = 0;

	file = fopen("eventt.log", "r");

	while (!feof(file)) {
		fscanf(file, "%*s %*s\t%*s\t%d\n", &counter1);
		
		if (feof(file)) {
			break;
		}

		fscanf(file, "%*s %*s\t%*s\t%d\n", &counter2);

		if (counter1 + 1 != counter2) {
			printf("A race condition occurs between %d and %d\n", counter1, counter2);
			flag = 1;
			break;
		}
	}

	fclose(file);
	
	if (!flag) {
		printf("A race condition does not occur.\n");
		system("rm event.log");
		system("ls");
		system("./debug");
	}
}
