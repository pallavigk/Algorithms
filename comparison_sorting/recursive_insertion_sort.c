#include <stdio.h>
#include <stdlib.h>

void recInsertionSort(int position, int arr[] ){
   if (position == 0) return;
	
   recInsertionSort(position-1, arr);
   //Now elements are sorted from 0 ... position-1 
   int value = arr[position];
   int i;
   for (i = position-1; i >= 0 && arr[i] > value; i--) {
	arr[i+1] = arr[i];
   }
   arr[i+1] = value;
}

int main() {
    //int array[] = {22, 11, 99, 88, 9, 7, 42};
    //int arrSize = 7;
    int array[] = {0,-1,-1,0};
    int arrSize = 4;
    recInsertionSort(arrSize-1,array);
    printf("Array after sorting :");
    for (int i = 0; i < arrSize; i++) {
	printf("%d ",array[i]);
    }
    printf("\n");
}
