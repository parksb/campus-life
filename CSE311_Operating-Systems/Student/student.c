// Dept of Digital Media 201700000 Park Seong-beom

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0

#define READ_END 0
#define WRITE_END 1

#define MAXLEN 255
#define MAXSTU 255
#define FAIL_MSG "Failed"
#define WAIT_TIME 100

void printClientMenu(int* cmd);
void printClientSearch(char* id);
void printClientAdd(char* id, char* name);
void openServerFile(FILE** file, char* mode);
const char* findData(FILE* file, char* id);
void updateData(FILE* file, char* id);

int main(int argc, char* argv[]) {
	int cmd;
	char id[MAXLEN]; // Student ID number
	char name[MAXLEN]; // Student name
	char result[MAXLEN];
	int p[2]; // Pipes

	// Create the pipes.
	printf("[CLIENT] Create pipes.\n");
	pipe(p);

	// Fork a child process.
	printf("[CLIENT] Execute fork.\n");
	pid_t pid  = fork();

	if (pid < 0) { // Fork error occured.
		printf("[CLIENT] Fork failed.\n");
		return 1;
	} else if (pid == 0) { // Child (Server)
		FILE* file;

		printf("[SERVER] Child created.\n");

		while(1) {
			read(p[READ_END], &cmd, sizeof(cmd));	

			switch (cmd) {
				case 1: // Search
					// Recieve id from client.
					read(p[READ_END], id, sizeof(id));
					printf("[SERVER] Request recieved: (%d, %s)\n", cmd, id);

					openServerFile(&file, "r");
					strncpy(result, findData(file, id), MAXLEN); // Search the data.

					// Print logs
					if (strcmp(result, FAIL_MSG) != 0) { // Data searched.
						printf("[SERVER] Response: (%d, %s, %s)\n", cmd, id, result);
					} else {
						printf("[SERVER] Response: The student %s does not exist.\n", id);
					}

					write(p[WRITE_END], result, sizeof(result)); // Send name or failure message to client.

					fclose(file);
					break;
				case 2: // Add
					// Recieve id and name from the client.
					read(p[READ_END], id, sizeof(id));
					read(p[READ_END], name, sizeof(name));
					printf("[SERVER] Request recieved: (%d, %s, %s)\n", cmd, id, name);

					openServerFile(&file, "r");
					strncpy(result, findData(file, id), MAXLEN); // Search the data.

					if (strcmp(result, FAIL_MSG) != 0) { // Same id searched.
						updateData(file, id); // Update current student data.
					}

					// Write id and name on the file.
					openServerFile(&file, "a");
					fprintf(file, "%s\t%s\n", id, name);
					printf("[SERVER] Write on file: Succeeded.\n");

					write(p[WRITE_END], id, sizeof(id)); // Send id as response data to client.

					fclose(file);
					break;
				default:
					printf("[SERVER] Undefined option.\n", cmd);
					write(p[WRITE_END], FAIL_MSG, sizeof(FAIL_MSG));
			}
			usleep(WAIT_TIME);
		}
		exit(0);
	} else { // Parent (Client)
		while(1) {
			usleep(WAIT_TIME);
			printClientMenu(&cmd);

			switch (cmd) {
				case 1: // Search
					printClientSearch(id);

					// Send data to server.
					printf("[CLIENT] Send request: (%d, %s)\n", cmd, id);
					write(p[WRITE_END], &cmd, sizeof(cmd));
					write(p[WRITE_END], id, sizeof(id));

					break;
				case 2: // Add
					printClientAdd(id, name);

					// Send data to server.
					printf("[CLIENT] Send request: (%d, %s, %s)\n", cmd, id, name);
					write(p[WRITE_END], &cmd, sizeof(cmd));
					write(p[WRITE_END], id, sizeof(id));
					write(p[WRITE_END], name, sizeof(name));

					break;
				default:
					write(p[WRITE_END], &cmd, sizeof(cmd));
			}

			usleep(WAIT_TIME);
			read(p[READ_END], result, sizeof(result));
			printf("[CLIENT] Operation completed: %s\n", result);
		}
		wait(NULL);
	}
	return 0;
}

// Print a main menu that showed on client.
void printClientMenu(int* cmd) {
	char input[MAXLEN];

	printf("[CLIENT] Print menu.\n");
	printf("--------------------\n");

	printf("[1] search\n");
	printf("[2] add\n");
	printf("> ");
	scanf("%s", input);

	printf("--------------------\n");

	if (strcmp(input, "1") == 0) { // Search
		*cmd = 1;
	} else if (strcmp(input, "2") == 0) { // Add
		*cmd = 2;
	} else { // Undefined operation
		*cmd = -1;
	}
}

// Print a search menu that showed on client.
void printClientSearch(char* id) {
	printf("id > ");
	scanf("%s", id);

	printf("--------------------\n");
}

// Print a add menu that showed on client.
void printClientAdd(char* id, char* name) {
	printf("id > ");
	scanf("%s", id);

	getchar();

	printf("name > ");
	scanf("%[^\n]s", name);

	printf("--------------------\n");
}

// Open the student data file and print logs.
void openServerFile(FILE** file, char* mode) {
	char* path = "student.data";

	*file = fopen(path, mode);

	if (*file == NULL) { // Error occured.
		printf("[SERVER] Open file in '%s' mode: Failed.\n", mode);
		exit(0);
	} else {
		printf("[SERVER] Open file in '%s' mode: Succeeded.\n", mode);
	}
}

// Find the student name that matched the id.
const char* findData(FILE* file, char* id) {
	char resId[MAXLEN];
	static char resName[MAXLEN];

	rewind(file);
	while (!feof(file)) {
		fscanf(file, "%s\t%[^\n]s\n", resId, resName);	
		if (strcmp(id, resId) == 0) { // Gotcha!
			printf("[SERVER] Search succeeded.\n");
			return resName;
		}
	}

	return FAIL_MSG;
}

// Update old data.
void updateData(FILE* file, char* id) {
	char resId[MAXSTU][MAXLEN];
	char resName[MAXSTU][MAXLEN];
	char newId[MAXSTU][MAXLEN];
	char newName[MAXSTU][MAXLEN];
	FILE* newFile; 
	int i = 0; 
	int j = 0;

	// Copy all data.
	rewind(file);
	for(i = 0, j = 0; !feof(file); i++) {
		fscanf(file, "%s\t%[^\n]s\n", resId[i], resName[i]);

		if (strcmp(resId[i], id) != 0) { // Exclude the data that matched the id.
			strncpy(newId[j], resId[i], sizeof(resId[i]));
			strncpy(newName[j], resName[i], sizeof(resName[i]));
			j++;
		}
	}

	// Write a new file includes the copied data. 
	openServerFile(&newFile, "w");
	for (i = 0; i < j; i++) {
		fprintf(newFile, "%s\t%s\n", newId[i], newName[i]);
	}

	fclose(newFile);
}
