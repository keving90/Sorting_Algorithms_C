/*****************************************************************************************
Prologue

UCSC Extension: Advanced C Programming

Instructor: Rajainder A. Yeldandi

Author: Kevin Geiszler

Assignment Number: 12, Sorting

Topics: Sorting Algorithms

File Name: assignment12_KevinGeiszler.c

Date: 3/9/2017

Objective: This program reads numbers from a file into an array and gives the user the
		   ability to implement one of seven sorting methods to sort the array in
		   ascending order.
		   
Comments:  Four of the seven sorting methods are simple sorting methods. These methods
		   include bubble sort, shell sort, insertion sort, and selection sort. The other
		   three sorting methods are more advanced sorting methods. They are quick sort,
		   heap sort, and merge sort. It's also important to note that after the user has
		   chosen one sorting method, the array must be re-shuffled so it can be sorted
		   once again if the user decides to implement other sorting methods. The array is
		   re-shuffled automatically.

*****************************************************************************************/

//Preprocessor directives
#include <stdio.h>
#include <stdlib.h>

#define ASIZE 40

/****************************************************************************************/

//Function prototypes
void displayMenu(void);
void initializeArray(FILE *, int []);
void swap(int *, int *);
void printArray(FILE *, int *, int);
void bubbleSort(FILE *, int *, int);
void shellSort(FILE *, int x[], int n, int incrmnts[], int numinc);
void insertSort(FILE *, int [], int);
void selectionSort(FILE *, int *, int);
void partition(int [], int, int, int *);
void myQuickSort(FILE *, int [], int, int);
void myHeapSort(FILE *, int [], int);
void myMergeSort(FILE *, int [], int);

/****************************************************************************************/

//The main function
int main(int argc, char *argv[])
{
	int iar[ASIZE];
	int increments[] = {5, 3, 1};
	int numinc = 3;
	int choice = 1;
	int index = 0;
	int fileInt;
	FILE *pInFile, *pOutFile;
	
	//check command line arguments
	if (argc != 3)
	{
		printf("Error, need the following file usage: %s inputFile outputFile\n", argv[0]);
		exit(1);
	}
	
	//open input file
	if ((pInFile = fopen(argv[1], "r")) == NULL)
	{
		printf("Error opening input file (%s).\n", argv[1]);
		exit(1);
	}
	
	//open output file
	if ((pOutFile = fopen(argv[2], "w")) == NULL)
	{
		printf("Error opening output file (%s).\n", argv[2]);
		exit(1);
	}
	
	initializeArray(pInFile, iar);

	printf("\nHere is the data in its original order:\n\n");
	fprintf(pOutFile, "\nHere is the data in its original order:\n\n");
	printArray(pOutFile, iar, ASIZE);
	printf("\n**************************\n");
	fprintf(pOutFile, "\n**************************\n");

	//prompt user to choose the desired sorting method
	//loop until the user decides to quit
	while(choice >= 1 && choice <= 7)
	{
		displayMenu();
		scanf(" %d", &choice);
		
		switch (choice)
		{
			//Bubble Sort
			case 1:
					fprintf(pOutFile, "\nThe user entered 1 for Bubble Sort.\n");
					
					bubbleSort(pOutFile, iar, ASIZE);
					
					printf("\n**************************\n");
					printf("\nBubble Sort has completed. Here is the data in ascending order:\n\n");
					fprintf(pOutFile, "\n**************************\n");
					fprintf(pOutFile, "\nBubble Sort has completed. Here is the data in ascending order:\n\n");
					
					printArray(pOutFile, iar, ASIZE);
					break;
					
			//Shell Sort
			case 2:
					fprintf(pOutFile, "\nThe user entered 2 for Shell Sort.\n");
					
					shellSort(pOutFile, iar, ASIZE, increments, numinc);
					
					printf("\n*************************\n");
					printf("\nShell Sort has completed. Here is the data in ascending order:\n\n");
					fprintf(pOutFile, "\n*************************\n");
					fprintf(pOutFile, "\nShell Sort has completed. Here is the data in ascending order:\n\n");
					
					printArray(pOutFile, iar, ASIZE);
					break;
					
			//Insertion Sort
			case 3:
					fprintf(pOutFile, "\nThe user entered 3 for Insertion Sort.\n");
					
					insertSort(pOutFile, iar, ASIZE);
					
					printf("\n*****************************\n");
					printf("\nInsertion Sort has completed. Here is the data in ascending order:\n\n");
					fprintf(pOutFile, "\n*****************************\n");
					fprintf(pOutFile, "\nInsertion Sort has completed. Here is the data in ascending order:\n\n");
					
					printArray(pOutFile, iar, ASIZE);
					break;
					
			//Selection Sort
			case 4:
					fprintf(pOutFile, "\nThe user entered 4 for Selection Sort.\n");
					
					selectionSort(pOutFile, iar, ASIZE);
					
					printf("\n*****************************\n");
					printf("\nSelection Sort has completed. Here is the data in ascending order:\n\n");
					fprintf(pOutFile, "\n*****************************\n");
					fprintf(pOutFile, "\nSelection Sort has completed. Here is the data in ascending order:\n\n");
					
					printArray(pOutFile, iar, ASIZE);
					break;
			
			//Quick Sort
			case 5:
					fprintf(pOutFile, "\nThe user entered 5 for Quick Sort.\n\n");
					printf("\nCalling Quick Sort\n");
					printf("******************\n\n");
					
					myQuickSort(pOutFile, iar, 0, ASIZE - 1);
					
					printf("*************************\n");
					printf("\nQuick Sort has completed. Here is the data in ascending order:\n\n");
					fprintf(pOutFile, "*************************\n");
					fprintf(pOutFile, "\nQuick Sort has completed. Here is the data in ascending order:\n\n");
					
					printArray(pOutFile, iar, ASIZE);
					break;
					
			//Heap Sort
			case 6:
					fprintf(pOutFile, "\nThe user entered 6 for Heap Sort.\n");
					
					myHeapSort(pOutFile, iar, ASIZE);
					
					printf("\n***************************\n");
					printf("\nHeap Sort has completed. Here is the data in ascending order:\n\n");
					fprintf(pOutFile, "\n***************************\n");
					fprintf(pOutFile, "\nHeap Sort has completed. Here is the data in ascending order:\n\n");
					
					printArray(pOutFile, iar, ASIZE);
					break;
					
			//Merge Sort
			case 7:
					fprintf(pOutFile, "\nThe user entered 7 for Merge Sort.\n");
					
					myMergeSort(pOutFile, iar, ASIZE);
					
					printf("\n*************************\n");
					printf("\nMerge Sort has completed. Here is the data in ascending order:\n\n");
					fprintf(pOutFile, "\n*************************\n");
					fprintf(pOutFile, "\nMerge Sort has completed. Here is the data in ascending order:\n\n");
					
					printArray(pOutFile, iar, ASIZE);
					break;
					
		   //Quit
		   default:
		   			printf("\n************************\n\n");
		   			printf("The program is quitting.\n");
		   			fprintf(pOutFile, "\nThe user chose to quit the program.\n");
		   			
		   			break;
					
		}
		
		printf("\n*************************\n");
		fprintf(pOutFile, "\n*************************\n");
		
		//Re-shuffle the array
		initializeArray(pInFile, iar);
	}
	
	printf("\nGood bye!\n");
	
	fclose(pInFile);
	fclose(pOutFile);

	return 0;
}

/****************************************************************************************/

//shows the main menu so the user can be prompted

void displayMenu(void)
{
	printf("\nEnter a number between 1 and 7 to select the desired sorting method. ");
	printf("Enter 8 to exit.\n\n");

	printf("1 - Bubble Sort\n");
	printf("2 - Shell Sort\n");
	printf("3 - Insertion Sort\n");
	printf("4 - Selection Sort\n");
	printf("5 - Quick Sort\n");
	printf("6 - Heap Sort\n");
	printf("7 - Merge Sort\n");
	printf("8 - Exit\n");

	printf("\nEnter your selection: ");
}

/****************************************************************************************/

//This function reads the input file and places the information into an array.

//It is also used to re-shuffle the array after it has been sorted so the user
//can choose another sorting method and successfully sort the array once again.

void initializeArray(FILE *pIn, int array[])
{
	int fileInt;
	int index = 0;
	
	rewind(pIn);

	while (fscanf(pIn, "%d,", &fileInt) == 1)
	{
		array[index] = fileInt;
		index++;
	}
}

/****************************************************************************************/

//This function is used in the bubblesort() and selectionsort() functions to swap two
//element in an array.

void swap(int *elem1ptr, int *elem2ptr)
{
	int temp;
	
	temp      = *elem1ptr;
	*elem1ptr = *elem2ptr;
	*elem2ptr =  temp;
	
	return;
}

/****************************************************************************************/

//This function prints the array to the screen and to an output file.

void printArray(FILE *pOut, int *pap, int size)
{
	int count;
	
	for (count = 0; count <= size - 1; count++)
	{
		printf("%4d", pap[count]);
		fprintf(pOut, "%4d", pap[count]);
	}
		
	printf("\n");
	fprintf(pOut, "\n");
		
	return;
}

/****************************************************************************************/

//Bubble Sort sorting method

void bubbleSort(FILE *pOut, int *iap, int size)
{
	int pass, i;
	
	printf("\nCalling Bubble Sort\n");
	printf("\n*******************\n");
	
	for (pass = 1; pass <= size - 1; pass++)
	{
		for (i = 0; i <= size - 2; i++)
			if (iap[i] > iap[i+1])
				swap(&iap[i], &iap[i+1]);
				
		printf("\nAfter Bubble sort Pass %d:\n", pass);
		fprintf(pOut, "\nAfter Bubble sort Pass %d:\n", pass);
		printArray(pOut, iap, size);	
	}
	
	return;
}

/****************************************************************************************/

//Shell Sort sorting method

void shellSort(FILE *pOut, int x[], int n, int incrmnts[], int numinc)
{
	int incr, j, k, span, y;
	
	printf("\nCalling Shell Sort\n");
	printf("******************\n");
	
	for (incr = 0; incr < numinc; incr++)
	{
		span = incrmnts[incr];
		
		for (j = span; j < n; j++)
		{
			y = x[j];
			
			for (k = j - span; k >= 0 && y < x[k]; k -= span)
				x[k+span] = x[k];
				
			x[k+span] = y;
		}
		
		printf("\nShell Sort Increment %d and Span %d:\n", incr + 1, span);
		fprintf(pOut, "\nShell Sort Increment %d and Span %d:\n", incr + 1, span);
		printArray(pOut, x, n);
	}
}

/****************************************************************************************/

//Insertion Sort sorting method

void insertSort(FILE *pOut, int x[], int n)
{
	int i, k, y;
	
	printf("\nCalling Insertion Sort\n");
	printf("**********************\n");
	
	for (k = 1; k < n; k++)
	{
		y = x[k];
		
		for (i = k - 1; i >= 0 && y < x[i]; i--)
			x[i+1] = x[i];
			
		printf("\nInsertion Sort Pass %d:\n", k);
		fprintf(pOut, "\nInsertion Sort Pass %d:\n", k);
		
		x[i+1] = y;
		
		printArray(pOut, x, n);
	}
}

/****************************************************************************************/

//Selection Sort sorting method

void selectionSort(FILE *pOut, int *iap, int size)
{
	int i, j;
	int min, temp;
	
	printf("\nCalling Selection Sort\n");
	printf("**********************\n");
	
	for (i = 0; i < size - 1; i++)
	{
		min = i;
		
		for (j = i + 1; j < size; j++)
		{
			if (iap[j] < iap[min])
				min = j;
		}
		
		swap(&iap[i], &iap[min]);
		
		printf("\nSelection Sort Pass %d:\n", i+1);
		fprintf(pOut, "\nSelection Sort Pass %d:\n", i+1);
		
		printArray(pOut, iap, ASIZE);
	}
}

/****************************************************************************************/

//This function is used inside of myQuickSort(). It allows a specific element to find its
//proper position with respect to the others in a sub-array.

void partition(int x[], int lb, int ub, int *pj)
{
	int a, down, temp, up;
	a    = x[lb]; //final position is sought for a
	up   = ub;
	down = lb;
		
	while (down < up)
	{
		while ((x[down] <= a) && (down < ub))
			down++; //move up the array
		
		while (x[up] > a)
			up--; //move down the array
			
		if (down < up)
		{
			//swap
			temp    = x[down];
			x[down] = x[up];
			x[up]   = temp;
		} //end if (down < up)
	} //end while (down < up)
		
	x[lb] = x[up];
	x[up] = a;
	*pj   = up;	
}

/****************************************************************************************/

//Quick Sort sorting method. The stdlib.h header file already has a function called
//quicksort(), so this function is called myQuickSort() instead.

void myQuickSort(FILE *pOut, int x[], int lb, int ub)
{
	static int i = 0;
	int part = 0;
	int *j;

	j = &part;

	if (lb >= ub)
		return;
	
	partition(x, lb, ub, j);
	myQuickSort(pOut, x, lb, *j - 1);
	myQuickSort(pOut, x, *j + 1, ub);
	
	printf("Quick Sort Pass %d:\n", i+1);
	fprintf(pOut, "Quick Sort Pass %d:\n", i+1);
	printArray(pOut, x, ASIZE);
	printf("\n");
	fprintf(pOut, "\n");
	i++;
	
	return;
}

/****************************************************************************************/

//Head Sort sorting method. The stdlib.h header file already has a function called
//heapsort(), so this function is called myHeapSort() instead.

void myHeapSort(FILE *pOut, int x[], int n)
{
	int i, elt, ch, pa, ivalue;
	
	printf("Calling Heap sort\n");
	printf("*****************\n");
	printf("\nCreating initial heap:\n");
	fprintf(pOut, "\nCreating initial heap:\n\n");
	
	//preprocessing phase; create initial heap
	for (i = 1; i < n; i++)
	{
		printf("\nIteration %d:\n", i);
		fprintf(pOut, "\nIteration %d:\n", i);
		
		elt = x[i];
		//pqinsert(x, i, elt);
		ch = i;
		pa = (ch - 1) / 2;
		
		while ((ch > 0) && (x[pa] < elt))
		{
			x[ch] = x[pa];
			ch = pa;
			pa = (ch - 1) / 2;
		} // end while
		
		x[ch] = elt;
		
		printArray(pOut, x, n);
	} //end for
	
	printf("\nThe initial heap has been created.\n");
	printf("**********************************\n");
	printf("\nProcessing the sort operation for Heap Sort:\n");
	fprintf(pOut, "\nThe initial heap has been created.\n");
	fprintf(pOut, "**********************************\n");
	fprintf(pOut, "\nProcessing the sort operation for Heap Sort:\n");
	
	//selection phase
	//repeatedly remove x[0], and insert it in its proper position and adjust the heap
	for (i = n - 1; i > 0; i--)
	{
		printf("\nIteration %d:\n", n - i);
		fprintf(pOut, "\nIteration %d:\n", n - i);
		
		//pqmaxdelete(x, i + 1)
		ivalue = x[i];
		x[i] = x[0];
		pa = 0;
		
		//ch = largechild(0, i - 1)
		if (i == 1)
			ch = -1;
		else
			ch = 1;
		
		if ((i > 2) && (x[2] > x[1]))
			ch = 2;
		
		while ((ch >= 0) && (ivalue < x[ch]))
		{
			x[pa] = x[ch];
			pa = ch;
			//ch = largechild(pa, i - 1)
			ch = 2 * pa + 1;
			
			if ((ch + 1 <= i - 1) && (x[ch] < x[ch+1]))
				ch = ch + 1;
				
			if (ch > i - 1)
				ch = -1;
		} //end while
		
		x[pa] = ivalue;
		
		printArray(pOut, x, ASIZE);
	} //end for
	
	printf("\nThe heap sort has finished.");
	fprintf(pOut, "\nThe heap sort has finished.");
}

/****************************************************************************************/

//Merge Sort sorting method. The stdlib.h header file already has a function called
//mergesort(), so this function is called myMergeSort() instead.

void myMergeSort(FILE *pOut, int x[], int n)
{
	int aux[ASIZE], i, j, k, L1, L2, size, u1, u2;
	int pass = 1;
	size = 1; //merge files of size 1
	
	printf("\nCalling Merge Sort\n");
	printf("******************\n");
	
	while (size < n)
	{
		L1 = 0; //lower bounds of the first file
		k = 0; //k is the index for the auxiliary array
		
		while (L1 + size < n) //if there are 2 files
		{
			//compute remaining indices
			L2 = L1 + size;
			u1 = L2 - 1;
			u2 = (L2 + size - 1 < n) ? (L2 + size - 1) : (n - 1);
			
			//proceed through the two sub-files
			u1 = L2 - 1;
			
			for (i = L1, j = L2; i <= u1 && j <= u2; k++)
			{
				if (x[i] <= x[j])
					aux[k] = x[i++];
				else
					aux[k] = x[j++];
			}
			
			//at this point, one of the subfiles has been exhausted
			//insert any remaining portions of the other file
			while (i <= u1)
			{
				aux[k] = x[i++];
				k++;
			}
			
			while (j <= u2)
			{
				aux[k] = x[j++];
				k++;
			}
			
			//advance L1 to the start of the net pair of files
			L1 = u2 + 1;
		} //end while (L1 + size < n)
		
		//copy any remaining single file
		for (i = L1; k < n; i++)
			aux[k++] = x[i];
			
		//copy aux into x and adjust size
		for (i = 0; i < n; i++)
			x[i] = aux[i];
		
		size *= 2;
		
		printf("\nAfter Merge Sort Pass %d:\n", pass);
		fprintf(pOut, "\nAfter Merge Sort Pass %d:\n", pass++);
		printArray(pOut, x, ASIZE);
	} //while (size < n)
}

/****************************************************************************************/






































