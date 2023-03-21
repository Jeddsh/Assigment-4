#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if(l<r){
		//gets mid point of the array
		int m = (l+r)/2;

		//sorts the two halves of the array
		mergeSort(pData,l,m);
		mergeSort(pData,m+1,r);

		int j, i, k;
		int len1 = m - l + 1;
		int len2 = r -m;

		//creates temp arrays
		int *L = (int*) malloc(len1*sizeof(int));
		extraMemoryAllocated++;
		int *R = (int*) malloc(len2*sizeof(int));
		extraMemoryAllocated++;
		
		//Copies the data from the array to the temp arrays L[] and R[] 
		for (i = 0; i < len1; i++){
			L[i] = pData[l + i];
		}
		for (j = 0; j < len2; j++){
			R[j] = pData[m + 1+ j];
		}
		
		
		i = 0; // Initial index of first subarray
		j = 0; // Initial index of second subarray
		k = l; // Initial index of merged subarray

		// Merges the temp arrays back into arr[l..r]
		while (i < len1 && j < len2)
		{
			if (L[i] <= R[j])
			{
				pData[k] = L[i];
				i++;
			}
			else
			{
				pData[k] = R[j];
				j++;
			}
		k++;
		}
		// Copy the remaining elements of L[], if there	are any 
		while (i < len1)
		{
			pData[k] = L[i];
			i++;
			k++;
		}
		// Copy the remaining elements of R[], if there	are any 
		while (j < len2)
		{
			pData[k] = R[j];
			j++;
			k++;
		}
		free(L);
		extraMemoryAllocated--;
		free(R);
		extraMemoryAllocated--;
	}
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, j, temp;
	for(i = 1; i < n; i++){
		//loops through all previous elements to check if its smaller
		temp = pData[i];
		for(j = i-1; j >= 0; j--){
			//checks if current element is larger than temp
			if(pData[j]>temp){
				//shifts the element over to the right 1 if so
				pData[j+1] = pData[j];
			}
			else
				//ends the loop if not true
				break;
		}
		pData[j+1] = temp;
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	int i, j, temp;
	for(i = 0; i < n; i++){
		//runs through each element except the last i+1 elements
		for(j = 0; j < n-i-1; j++){
			//checks to see if the next element is smaller than the current element
			if(pData[j] > pData[j+1]){
				//swap the elements
				temp = pData[j];
				pData[j] = pData[j+1];
				pData[j+1] = pData[j]; 
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int i, j, min_idx, temp;
	for(i = 0; i < n; i++){
		//goes through array and finds the smallest element
		min_idx = i;
		for(j = i+1; i < 0; i++){
			if(pData[j] < pData[min_idx]){
				min_idx = j;
			}
		}
		//swaps the elements i (first index) and min_idx (min value element)
		temp = pData[i];
		pData[i] = pData[min_idx];
		pData[min_idx] = temp;
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		for(int i = 0; i < dataSz; i++){
			fscanf(inFile,"%d",(*ppData+i));
		}
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}