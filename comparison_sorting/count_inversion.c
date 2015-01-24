
//Application of Merge sort
//
#include <stdio.h>
#include <stdlib.h>

/*
Input : array A containing the numbers 1,2,3,..,n in some arbitrary order
Output : number of inversions = number of pairs (i,j) of array indices with i<j
 and A[i] > A[j]

Motivation : numerical similarity measure between two ranked lists (or sorted arrays.

Application: Collaborative filtering

Maximum number of inversions that an n element array can have is nC2 ie., 
n/(2 * (n-2)) = n(n-1) / 2

Algorithm:
It is similar to Mergesort. While merging the two sorted subarrays, keep running
total of number of split inversions. Wwhen element of 2nd subarray gets copied
to output, increment total(total no of inversions)  by number of elements remaining in 1st subarray.

Time complexity: O(n log n)
*/


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

unsigned long MergeInversions(int arr[], int left, int mid, int right) {
    int leftElements = mid - left + 1;
    int rightElements = right - mid; //ie., right - (mid+1) + 1
    int leftArray[leftElements];
    int rightArray[rightElements];
    unsigned long inversions = 0;
 
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
	}
	else {
	    arr[k] = rightArray[j];
	    j++;
	    inversions = inversions + leftElements - i; //Elements from i to end form inversions with rightArray[j]
#if 0
	    printf("%d inversions while adding %d\n",(leftElements - i) , arr[k]);
#endif
	}
        k++;
    }

    while (i < leftElements) { //Elemets left in leftArray (if any) should be copied
	    arr[k] = leftArray[i];
	    k++;
	    i++;
    }
    while (j < rightElements) { //Elemets are left in rightArray(if any) should be copied
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
    return inversions;
}
unsigned long CountInversions(int arr[],int left, int right) {
    unsigned long inversions = 0;
    if (left >= right) return inversions;

    int mid = (left + right) / 2;
    inversions = inversions + CountInversions(arr, left, mid);
    inversions = inversions + CountInversions(arr,mid+1,right);
    inversions = inversions + MergeInversions(arr,left,mid,right);
    return inversions;
}
int main() {
    //int array[] = {22, 11, 99, 88, 9, 7, 42};
    //int arrSize = 7;
    int array[] = {2,3,8,6,1};
    int arrSize = 5;
    
    unsigned long inv = CountInversions(array,0,arrSize-1);
    printf("Array after sorting :");
    for (int i = 0; i < arrSize; i++) {
	printf("%d   %d\n ",i,array[i]);
    }
    printf("\n");
    printf("No of inversions %lu\n",inv);

}

