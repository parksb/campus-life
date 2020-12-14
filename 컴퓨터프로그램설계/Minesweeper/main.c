/*
Computer Program Design Assignment: Minesweeper 
Author: Park Seong-beom (Media 201700000)
Date: 2017.11.24
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_COL 101
#define MAX_ROW 101

void getBoardSize(int * col, int * row);
void getBoard(char board[][MAX_ROW], int col, int row);
int checkBoardSize(int col, int row);
void printBoard(char board[][MAX_ROW], int col, int row);
void fillNumber(char board[][MAX_ROW], int col, int row);

int main(int argc, char *argv[]) {
	int col = 0;
	int row = 0;
	char board[MAX_COL][MAX_ROW] = {{0}};
	
	getBoardSize(&col, &row);
	getBoard(board, col, row);
	
	fillNumber(board, col, row);
	
	printBoard(board, col, row);
	
	return 0;
}

void getBoardSize(int * col, int * row) {
	do {
		scanf("%d %d", col, row);		
	} while((checkBoardSize(*col, *row)));	
} // getBoardSize

int checkBoardSize(int col, int row) {
	if((col < 0 || row < 0) || (col >= MAX_COL || row >= MAX_ROW)) {
		printf("Invalid value.\n");
		return 1;
	} else {
		return 0;
	}
} // checkBoardSize

void getBoard(char board[][MAX_ROW], int col, int row) {
	int i;
	
	for(i = 0; i < col; i ++) {
		scanf("%s", board[i]);
	}
} // getBoard

void printBoard(char board[][MAX_ROW], int col, int row) {
	int i, j;
	
	printf("\n");
	
	for(i = 0; i < col; i++) {
		for(j = 0; j <row; j++) {
			printf("%-2c", board[i][j]);
		}
		printf("\n");
	}
} // printBoard

void fillNumber(char board[][MAX_ROW], int col, int row) {
	int compass[8] = {0};
	int number = 0x30; // '0'
	int i, j, k;
	
	for(i = 0; i < col; i++) {
		for(j = 0; j < row; j++) {
			number = 0x30; // '0'
			
			if(board[i][j] == '.') {
				compass[0] = board[i][j + 1];     // East (E)
				compass[1] = board[i + 1][j + 1]; // South East (SE) 
				compass[2] = board[i + 1][j];     // South (S)
				compass[3] = board[i - 1][j];     // North (N)
				compass[4] = board[i - 1][j + 1]; // North East (NE)     
				compass[5] = board[i + 1][j - 1]; // South West (SW)
				compass[6] = board[i][j - 1];     // West (W)
				compass[7] = board[i - 1][j - 1]; // North West (NW)
					 
				for(k = 0; k < 8; k++) {
					if(k == 7) { // Nw
						if((compass[k] == '*') && ((i - 1) >= 0) && ((j - 1) >= 0)) {
							number++;
						}
					} else if(k >= 5) { // SW, W, NW
						if((compass[k] == '*') && ((j - 1) >= 0)) {
							number++;
						}
					} else if(k >= 3) { // N, NE, SW, W, NW
						if((compass[k] == '*') && ((i - 1) >= 0)) {
							number++;
						}		
					} else {
						if(compass[k] == '*') {
							number++;
						}		
					}
				}
				board[i][j] = number;
			}
		}
	}
} // fillNumber
