//"Greatest hit" algorithm
//Time complexity: O(n logn) to n^2 (worst case)
//Minimal extra memory needed
//
//Logic:
//  Partition array around a pivot point. 
//  Rearrange the array so that
//      - Left of pivot -> less than pivot
//      - Right of pivot -> greater than pivot
//Cool facts:
//  The pivot is put in its "rightful position"
//  Linear O(n) in time, no extra memory
//  Reduces problem size
//
//Pseudocode for QuickSort
//QuickSort(Array A, length n)
//  If n == 1, return
//  p = ChoosePivot(A,n) 
//  Partition A around p
//  Recursively sort 1st part
//  Recursively sory 2nd part
//
//Pseudocode for Partition
//Partition (A,l,r) (input corresponds to A[l..r])
//  p = A[l] //Here we are choosing the Pivot element as A[l]
//  i = l+1
//  for j = l+1 to r
//      if A[j] < p   [If A[j] > p, do nothing]
//          swap A[j] and A[i]
//          i = i+1
//  Swap A[l] and A[i-1]

#include <stdio.h>
#include <stdlib.h>

void PrintArray(int arr[], int size) {
    for (int i = 0; i < size; i++) 
        printf("%d ",arr[i]);
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int arr[], int left, int right) {
    int pivot = arr[left];
    int i = left + 1;
    for (int j = left+1; j <= right; j++) {
       if (arr[j] < pivot) {
            swap(&arr[j], &arr[i]);
            i++;
       }
    }
    //At this point, arr[left+1..i-1] contain elements less than arr[left] ie., pivot
    //               arr[i..right] contain elemnts greater than or equal to pivot
    swap(&arr[left],&arr[i-1]);
    return (i-1);
}
void QuickSort(int arr[], int left, int right) {
    if (left >= right) return;

    //For the time being, arr[left] is chosen as the pivot element 
    int partitionIndex = Partition(arr,left,right);
    QuickSort(arr,left, partitionIndex-1);
    QuickSort(arr,partitionIndex+1,right);
}
int main() {
    //int array[] = {7,6,8,1,2,3,9,0,12,5,6,1,0,0,8};
    int array[] = {5,4,3,2,1,0};
    int arrSize = sizeof(array)/sizeof(array[0]);
    QuickSort(array,0,arrSize-1);
    PrintArray(array,arrSize);
}
