#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define REF_STRING_LEN 1000
#define FRAME_LEN 10

void initializeRefStringUni(int *refString, int max);
void initializeRefStringNorm(int *refString);
void initializeFrame(int *frame);
double generateNormalDistRand(void);

void printRefString(int *refString);
void printFrame(int *frame);

void testFifo(int *refString, int *frame);
void testOptimal(int *refString, int *frame);
void testLruRefCount(int *refString, int *frame);
void testSecondChance(int *refString, int *frame);

FILE* file;

int main(int argc, char *argv[]) {
	int refString[REF_STRING_LEN];
	int frame[FRAME_LEN];
	int max = 50;
	int i = 0;
	
	file = fopen("event.log", "a");
	
	// Algorithm simulations

	while (max <= REF_STRING_LEN) {
		printf("======= %d ======\n", max);
		
		/* Uniform distribution */
		// initializeRefStringUni(refString, REF_STRING_LEN);
		
		/* Normal distribution */
		initializeRefStringNorm(refString);
		
		initializeFrame(frame);	
			
		testFifo(refString, frame);
		printFrame(frame);
		initializeFrame(frame);
			
		testOptimal(refString, frame);
		printFrame(frame);
		initializeFrame(frame);
			
		testLruRefCount(refString, frame);
		printFrame(frame);
		initializeFrame(frame);
			
		testSecondChance(refString, frame);
		printFrame(frame);
		initializeFrame(frame);
		
		max += 50;
	}
	
	return 0;
}

/**
 * Generate a random number based on normal distribution.
 * The function made by pinko_liberal.
 * https://bit.ly/2yagLCO (Cprogramming.com, 2001)
 */
double generateNormalDistRand(void) {
	static int i = 0;
	double x, y, s;
	static double r1, r2;
	
	if(i == 1) {
		i = 0;
		return r2;
	}
	
	do {
		x = 2. * ((double) rand() / (RAND_MAX + 1.0)) - 1.;
		y = 2. * ((double) rand() / (RAND_MAX + 1.0)) - 1.;
		s = x * x + y * y;
	} while (s > 1.);
	
	r1 = x * sqrt(-2. * log(s) / s);
	r2 = y * sqrt(-2. * log(s) / s);
	i = 0;
	
	return abs(r1 * 100.0);
}

/**
 * Initialize a reference string based on
 * normal distribution random number.
 */
void initializeRefStringNorm(int *refString) {
	int i = 0;

	for (i = 0; i < REF_STRING_LEN; i++) {
		refString[i] = (int)generateNormalDistRand();
	}
}

/**
 * Initialize a reference string based on
 * uniform random number.
 */
void initializeRefStringUni(int *refString, int max) {    
	int i = 0;
		
	srand(time(NULL));
	for (i = 0; i < REF_STRING_LEN; i++) {
		refString[i] = (rand() % max);
	}
}

void initializeFrame(int *frame) {
	int i = 0;
	
	for (i = 0; i < FRAME_LEN; i++) {
		frame[i] = -1;
	}
}

void printRefString(int *refString) {
	int i = 0;
	
	printf("RefString: [ ");
	for (i = 0; i < REF_STRING_LEN; i++) {
		printf("%d ", refString[i]);
	}
	printf("]\n");
}

void printFrame(int *frame) {
	int i = 0;
	
	printf("frame: [ ");
	for (i = 0; i < FRAME_LEN; i++) {
		printf("%d ", frame[i]);
	}
	printf("]\n");	
}

void testFifo(int *refString, int *frame) {
	int freeFrame = -1;
	int curr = 0;
	int pageFault = 0;
	
	int i = 0;
	int j = 0;
	
	for (i = 0; i < REF_STRING_LEN; i++) {		
		// Find a same page or free frames.
		for (j = 0; j < FRAME_LEN; j++) {
			if (frame[j] == refString[i] || frame[j] == -1) {
				freeFrame = j;
				break;
			}
		}
		
		if (freeFrame != -1) {
			frame[freeFrame] = refString[i];
			freeFrame = -1;
		} else { // A page fault has occurred.	
			if (curr == FRAME_LEN) {
				curr = 0;
			}
			
			frame[curr] = refString[i];
			curr++;
			pageFault++;	
			
			fprintf(file, "[FIFO] Page fault has occurred at %d\n", i);		
		}
	}
	
	printf("[FIFO] Page fault occurring %d times.\n", pageFault);
	fprintf(file, "[FIFO] Page fault occurring %d times.\n", pageFault);
}

void testOptimal(int *refString, int *frame) {
	int pageFreq[REF_STRING_LEN];
	int freeFrame = -1;
	int pageFault = 0;
	int curr = 0;
	
	int i = 0;
	int j = 0;

	for (i = 0; i < REF_STRING_LEN; i++) {					
		// Find a same page or free frames.
		for (j = 0; j < FRAME_LEN; j++) {
			if (frame[j] == refString[i] || frame[j] == -1) {
				freeFrame = j;
				break;
			}
		}
		
		if (freeFrame != -1) {
			frame[freeFrame] = refString[i];
			freeFrame = -1;
		} else { // A page fault has occurred.
			int minIdx = 0;
			
			// Initialize pageFreq.
			for (j = 0; j < REF_STRING_LEN; j++) {
				pageFreq[j] = 0;
			}
			
			// Get pageFreq data.
			for (j = curr; j < REF_STRING_LEN; j++) {
				pageFreq[refString[j]]++;
			}
				
			for (j = 0; j < FRAME_LEN; j++) {
				if (pageFreq[frame[minIdx]] > pageFreq[frame[j]]) {
					minIdx = j;
				}
			}
			
			frame[minIdx] = refString[i];
			pageFault++;
			curr++;
			
			fprintf(file, "[Optimal] Page fault has occurred at %d\n", i);
		}
	}
	
	printf("[Optimal] Page fault occurring %d times.\n", pageFault);	
	fprintf(file, "[Optimal] Page fault occurring %d times.\n", pageFault);
}

void testLruRefCount(int *refString, int *frame) {
	int freeFrame = -1;
	int pageFault = 0;
	int refCounter[FRAME_LEN];
	int tick = 0;
	int minIdx = 0;
	
	int i = 0;
	int j = 0;
	
	for (i = 0; i < REF_STRING_LEN; i++) {		
		// Find a same page or free frames.
		for (j = 0; j < FRAME_LEN; j++) {
			if (frame[j] == refString[i] || frame[j] == -1) {
				freeFrame = j;
				break;
			}
		}
		
		if (freeFrame != -1) {
			frame[freeFrame] = refString[i];
			refCounter[freeFrame] = tick;
			freeFrame = -1;
		} else { // A page fault has occurred.
			minIdx = 0;
				
			for (j = 0; j < FRAME_LEN; j++) {
				if (refCounter[minIdx] > refCounter[j]) {
					minIdx = j;
				}		
			}
			
			frame[minIdx] = refString[i];
			refCounter[minIdx] = tick;
			pageFault++;			
			
			fprintf(file, "[LRU Reference Count] Page fault has occurred at %d\n", i);		
		}
		
		tick++;
	}

	printf("[LRU Reference Count] Page fault occurring %d times.\n", pageFault);	
	fprintf(file, "[LRU Reference Count] Page fault occurring %d times.\n", pageFault);	
}

void testSecondChance(int *refString, int *frame) {
	int freeFrame = -1;
	int curr = 0;
	int pageFault = 0;
	int frameRefBit[FRAME_LEN];
	int isChanged = 0;
	
	int i = 0;
	int j = 0;
	
	for (i = 0; i < FRAME_LEN; i++) {
		frameRefBit[i] = 0;
	}
	
	for (i = 0; i < REF_STRING_LEN; i++) {							
		// Find a same page or free frames.
		for (j = 0; j < FRAME_LEN; j++) {
			if (frame[j] == refString[i]) {
				freeFrame = j;
				frameRefBit[freeFrame] = 1;
				break;
			} else if (frame[j] == -1) {
				freeFrame = j;
				frameRefBit[freeFrame] = 0;
				break;
			}
		}
		
		if (freeFrame != -1) {
			frame[freeFrame] = refString[i];
			freeFrame = -1;
		} else { // A page fault has occurred.	
			while (!isChanged) {				
				if (frameRefBit[curr] == 0) {
					frame[curr] = refString[i];
					isChanged = 1;
				} else {
					frameRefBit[curr] = 0;
					isChanged = 0;
				}
				
				curr++;
				if (curr == FRAME_LEN) {
					curr = 0;
				}
			}
			
			pageFault++;
			
			fprintf(file, "[Second Chance] Page fault has occurred at %d\n", i);		
		}
	}
	
	printf("[Second Chance] Page fault occurring %d times.\n", pageFault);
	fprintf(file, "[Second Chance] Page fault occurring %d times.\n", pageFault);
}