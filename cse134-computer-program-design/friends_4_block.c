/*
Computer Program Design Assignment: Friends4Block 
Author: Park Seong-beom (Media 201700000)
Date: 2017.11.16
*/

#include <stdio.h>
#include <stdlib.h>

#define EMPTY_BLOCK 'X'

void getBoardSize(int *m, int *n);
void getBoardElement(char **board, int m, int n);
void findBlock(char **board, int m, int n, int **removeBlockStack, int *stackNum);
void removeBlock(char **board, int m, int n, int **removeBlockStack, int *stackNum);
void fillBlock(char **board, int m, int n);
void printBoard(char **board, int m, int n);
int countEmptyBlock(char **board, int m, int n);

int main(int argc, char *argv[]) {
	char **board; // Game board.
	int m = 0; // Height of the board. (row)
	int n = 0; // Width of the board. (col)
	
	int **removeBlockStack; // Array of blocks' locations that should be removed.
	int removeBlockStackNum = 0; // Number of the removeBlockStack's elements.
	
	int i = 0;
	
	// Input and memory allocation.
	
	getBoardSize(&m, &n);
	printf("\n");
	
	board = (char **)malloc(sizeof(char *) * m);
	removeBlockStack = (int **)malloc(sizeof(int *) * ((m - 1) * (n - 1)));

	for(i = 0; i < m; i++) {
		board[i] = (char *)malloc(sizeof(char) * n);
	}
	
	for(i = 0; i < ((m - 1) * (n - 1)); i++) {
		removeBlockStack[i] = (int *)malloc(sizeof(int) * 2);
	}
	
	getBoardElement(board, m, n);
	printBoard(board, m, n);
	
	// Operation.
	
	findBlock(board, m, n, removeBlockStack, &removeBlockStackNum);
	
	while (removeBlockStackNum > 0) {
		removeBlock(board, m, n, removeBlockStack, &removeBlockStackNum);
		fillBlock(board, m, n);
		findBlock(board, m, n, removeBlockStack, &removeBlockStackNum);
	}
	
	// Output.
	
	printf("answer: %d\n", countEmptyBlock(board, m, n));
	
	// Freeing memory.
	
	for(i = 0; i < m; i++) {
		free(board[i]);
	}
	
	for(i = 0; i < ((m - 1) * (n - 1)); i++) {
		free(removeBlockStack[i]);
	}
	
	free(board);
	free(removeBlockStack);
	
	return 0;
}

// Get board size from user.
void getBoardSize(int *m, int *n) {
	printf("m >> ");
	scanf("%d", m);
	
	printf("n >> ");
	scanf("%d", n);
} // getBoardSize

// Get board's elements from user.
void getBoardElement(char **board, int m, int n) {
	int i = 0;
	int j = 0;
	
	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++) {
			printf("board[%d][%d] >> ", i, j);
			scanf(" %c", &board[i][j]);
		}
		printf("\n");
	}
} // getBoardElement

// Find the blocks around four same blocks.
void findBlock(char **board, int m, int n, int **removeBlockStack, int *stackNum) {
	char tBlock; // Target block.
	char tNxtBlock;
	char tBlwBlock;
	char tBlwNxtBlock;
	
	int i = 0;
	int j = 0;
	
	*stackNum = 0; 
	
	// Find the blocks to remove.
	for(i = 0; i < (m - 1); i++) {
		for(j = 0; j < (n - 1); j++) {
			tBlock = board[i][j];
			tNxtBlock = board[i][j + 1];
			tBlwBlock = board[i + 1][j];
			tBlwNxtBlock = board[i + 1][j + 1];

			if(tBlock != EMPTY_BLOCK) {
				if((tBlock == tNxtBlock) && (tBlock == tBlwBlock) && (tBlock == tBlwNxtBlock)) {
					removeBlockStack[*stackNum][0] = i;
					removeBlockStack[*stackNum][1] = j;
					
					*stackNum += 1;
				}
			}
		}			
	}
} // findBlock

// Remove blocks with four same blocks.
void removeBlock(char **board, int m, int n, int **removeBlockStack, int *stackNum) {
	char tBlock; // Target block.
	char tNxtBlock;
	char tBlwBlock;
	char tBlwNxtBlock;
	
	int row = 0;
	int col = 0;	
	
	int i = 0;
	int j = 0;
	
	// Remove the same blocks.
	for(i = 0; i < *stackNum; i++) {		
		row = removeBlockStack[i][0];
		col = removeBlockStack[i][1];
			
		board[row][col] = EMPTY_BLOCK;
		board[row][col + 1] = EMPTY_BLOCK;
		board[row + 1][col] = EMPTY_BLOCK;
		board[row + 1][col + 1] = EMPTY_BLOCK;
	}
} // removeBlock

// To fill the empty blocks with the above blocks.
void fillBlock(char **board, int m, int n) {
	char tBlock; // Target block.
	char tBlwBlock;
	char tAbvBlock;
	
	int i = 0;
	int j = 0;
	
	// Find the blocks that should be fallen.
	for(i = 0; i < (m - 1); i++) {
		for(j = 0; j < n; j++) {
			tBlock = board[i][j];
			tBlwBlock = board[i + 1][j];
		 
			if((i - 1) >= 0) {
				tAbvBlock = board[i - 1][j];
			} else {
				tAbvBlock = EMPTY_BLOCK;
			}

			if((tBlock != EMPTY_BLOCK) && (tBlwBlock == EMPTY_BLOCK)) {
				board[i][j] = EMPTY_BLOCK;
				board[i + 1][j] = tBlock; // Fill the empty block.

				if(tAbvBlock != EMPTY_BLOCK) { 
					fillBlock(board, m, n);	
				}
			} 
		}
	}
} // fillBlock

// Print the board.
void printBoard(char **board, int m, int n) {
	int i = 0;
	int j = 0;
	
	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++) {
			printf("%-2c", board[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
} // printBoard

// Count the empty blocks in the board.
int countEmptyBlock(char **board, int m, int n) {
	int emptyBlockNum = 0; // Number of the empty blocks.
	
	int i = 0;
	int j = 0;
	
	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++) {
			if(board[i][j] == EMPTY_BLOCK) {
				emptyBlockNum++;
			}
 		}
	}
	
	return emptyBlockNum;
} // countEmptyBlock
