//Merge sort uses divide-and-conquer approach to sort the array
//Divide: Divide the n-element sequence to be sorted into two subsequences of 
//n/2 elements each
//Conquer: Sort the two subsequences recursively using merge sort.
//Combine: Merge the two sorted subsequences to produce the sorted answer.
//Time complexity: Θ(n logn) 
//Space complexity: An extra O(n) space is required in the Merge procedure

#include <stdio.h>
#include <stdlib.h>

//Utility function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Utility function
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void Merge(int arr[], int left, int mid, int right) {
    int leftElements = mid - left + 1;
    int rightElements = right - mid; //ie., right - (mid+1) + 1
    int leftArray[leftElements];
    int rightArray[rightElements];
 
    for (int i = 0; i < leftElements; i++)
	leftArray[i] = arr[left+i]; 
    
    for (int j = 0; j < rightElements; j++)
	rightArray[j] = arr[mid+1+j]; 

#if 0
    printf("Left Array\n");
    printArray(leftArray,leftElements);
    printf("Right Array\n");
    printArray(rightArray,rightElements);
#endif

    int i = 0, j = 0, k = left;
    while ((i < leftElements) && (j < rightElements)) {
	if (leftArray[i] <= rightArray[j]) {
	    arr[k] = leftArray[i];
	    i++;
	    k++;
	}
	else {
	    arr[k] = rightArray[j];
	    j++;
            k++;
	}
    }

    while (i < leftElements) { //Elemets are left in leftArray
	    arr[k] = leftArray[i];
	    k++;
	    i++;
    }
    while (j < rightElements) { //Elemets are left in rightArray
	    arr[k] = rightArray[j];
	    k++;
	    j++;
    }

#if 0
    printf("Merged portion :");
    for (int i = left; i <= right; i++) 
	printf("%d ",arr[i]);
    printf("\n");
#endif
}

void MergeSort(int arr[],int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;

#if 0
    //printf("left %d,mid %d, right %d\n",left,mid,right);
#endif
    MergeSort(arr, left, mid);
    MergeSort(arr,mid+1,right);
    Merge(arr,left,mid,right);
}
int main() {
    int array[] = {22, 11, 99, 88, 9, 7, 42};
    int arrSize = 7;
    MergeSort(array,0,arrSize-1);
    printf("Array after sorting :");
    for (int i = 0; i < arrSize; i++) {
	printf("%d ",array[i]);
    }
    printf("\n");

}

