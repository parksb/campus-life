#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

void* performThread(void* data);

int counter = 0;
FILE* file;	

int main(int argc, char* argv[]) {
	pthread_t threads[3];
	char threadNames[3][128] = {
		{"thread1"},
		{"thread2"},
		{"thread3"}
	};
	int i = 0;

	file = fopen("event.log", "a");

	for (i = 0; i < 100000; i++) {
		pthread_create(&threads[0], NULL, performThread, (void*)threadNames[0]);
		pthread_create(&threads[1], NULL, performThread, (void*)threadNames[1]);
		pthread_create(&threads[2], NULL, performThread, (void*)threadNames[2]);	
	}

	printf("Done: %d\n", counter);
	
	fclose(file);

	return 0;
}

void* performThread(void* data) {
	time_t currentTime;
	struct tm* timeInfo;
	char currentTimeString[128];
	char* threadName = (char*)data;

	time(&currentTime);
	timeInfo = localtime(&currentTime);
	strftime(currentTimeString, 128, "%Y-%m-%d %H:%M:%S", timeInfo);

	fprintf(file, "%s\t%s\t%d\n", currentTimeString, threadName, counter);

	counter++;
}
