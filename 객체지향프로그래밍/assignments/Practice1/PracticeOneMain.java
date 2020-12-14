/**
 * CSE231 Object Oriented Programming Assignment 1
 * Author: Department of Digital Media 201700000 박성범
 * Date: 2018.3.9
 */

public class PracticeOneMain {
	public static void main(String[] args) {
		// lab practice
		printReversedTriangle();
		
		// assignment 1
		int[] seq = { 10, 20, 3, -10, -5, 21, 18, 30 };
		selectionSort(seq);
		for (int i = 0; i < seq.length; i++) {
			System.out.println(seq[i]);	
		}
	}
	
	static void printReversedTriangle() {
		int rowCount = 5;
		int starCount = 9; // the number of stars in each row.
		
		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < i; j++) {
				System.out.print(" ");
			}
			
			for (int k = starCount; k > 0; k--) {
				System.out.print("*");
			}
			
			starCount -= 2;
			System.out.println();
		}
	} // printReversedTriangle
	
	static void selectionSort(int[] seq) {
		int minIndex = 0;
		int temp = 0; // temporary variable to swap the values.
		int seqLen = seq.length;
		
		for (int i = 0; i < seqLen; i++) {
			minIndex = i;
			for (int j = i; j < seqLen; j++) {
				if (seq[minIndex] > seq[j]) {
					minIndex = j;
				}
			}
			
			temp = seq[i];
			seq[i] = seq[minIndex];
			seq[minIndex] = temp;
		}
	} // selectionSort
}
