#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//The DSelect Algorithm
//DSelect(array A, length n, order statistic i)
//1. Break A into groups of 5, sort each group
//2. C = the n/5 “middle elements”
//3. p = DSelect(C,n/5,n/10) [recursively computes median of C]
//4. Partition A around p
//5. If j = i return p
//6. If j > i return DSelect(1st part of A,j-1,i)
//7. [else if j < i] return DSelect(2nd part of A, n-j, i-j)

#define SMALL_ARRAY_SIZE 5

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int arrSize) {
    for (int i = 0; i < arrSize; i++)
        printf("%d ",arr[i]);
    printf("\n");
}

int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int Partition(int arr[], int arrSize) {
    //a[0] is the pivot element
    int j = 1;
    for (int i = 1; i < arrSize; i++) {
        if (arr[i] < arr[0]) {
            swap(&arr[j],&arr[i]);
            j++;
        }
    }
    swap(&arr[j-1],&arr[0]);
    return (j-1);
}

int DSelect(int arr[], int arrSize, int ithOrder) {
    if (arrSize <= 1) 
        return 0;
    int no_of_small_arrays = ceil(arrSize*1.0/SMALL_ARRAY_SIZE);
    int medianElems[no_of_small_arrays];

    int tempArr[SMALL_ARRAY_SIZE];

#if 0
    printf("No of n/5 arrays : %d\n",no_of_small_arrays);
#endif

    if (no_of_small_arrays <= 1) {
        qsort(arr, arrSize, sizeof(*arr),comp);
        //printArray(arr, arrSize);
        return arr[ithOrder];
    }
    int numElemsLastSubArray = arrSize % SMALL_ARRAY_SIZE;
    if (numElemsLastSubArray == 0) //This means last subarray has 5 elements
        numElemsLastSubArray = SMALL_ARRAY_SIZE;

    //Break A into groups of 5, sort each group
    //C = the n/5 “middle elements”
    //p = DSelect(C,n/5,n/10) [recursively computes median of C]
    for (int i = 0; i < no_of_small_arrays-1; i++) { //The last set may contain less than 
        for (int j = 0; j < SMALL_ARRAY_SIZE; j++)
            tempArr[j] = arr[i*SMALL_ARRAY_SIZE+j]; 

        //Use quick sort to sort the elements
        qsort(tempArr, SMALL_ARRAY_SIZE, sizeof(*tempArr),comp);
        
        //The middle element is the median of this small array.
        medianElems[i] = tempArr[SMALL_ARRAY_SIZE/2];
    }

    //We have to exclusively find the number of elements to fill for last small array.
    for (int j = 0; j < numElemsLastSubArray; j++)
        tempArr[j] = arr[(no_of_small_arrays-1)*SMALL_ARRAY_SIZE+j];
    qsort(tempArr, numElemsLastSubArray, sizeof(*tempArr),comp); 
    medianElems[no_of_small_arrays-1] = tempArr[numElemsLastSubArray/2];
#if 0
    printArray(tempArr, numElemsLastSubArray);
    printf("Medians of subarrays : ");
    printArray(medianElems, no_of_small_arrays);
#endif

    int median_of_medians = DSelect(medianElems, no_of_small_arrays, no_of_small_arrays/2-1);
    int index = 0;
    for (index = 0; index < arrSize; index++)
        if (arr[index] == median_of_medians)
            break;
#if 0
    printf("median of medians : %d\n",median_of_medians);
#endif

    //Like we did in RSelect, swap median of medians with first elem of the array
    //and then call Partition() routine
    swap(&arr[0], &arr[index]);
    int pivot_position = Partition(arr,arrSize);

#if 0
    printf("Array after partition : ");
    printArray(arr,arrSize);
    printf("Index is : %d\n",pivot_position);
#endif

    if (pivot_position == ithOrder)  //This is the statistic we are looking for
        return arr[pivot_position];
    if (pivot_position < ithOrder)  //Pivot's position is left to ith order statistic, so recurse right
        return DSelect(arr+pivot_position+1,arrSize-(pivot_position+1),ithOrder-(pivot_position+1));
    else //Pivot's position is right of ith order, so recurse left
        return DSelect(arr,pivot_position,ithOrder);
}
int main() {
    /*
    int arr[] = {6,5,3,4,2,1};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    */

    /*
    int arr[] = {10,8,9,6,7,5,3,4,2,1};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    */

    /*
    int arr[] = {10,8,9,6,7,5,3,4,2,1,1,1,1,1,1};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    */

    /*
    int arr[] = {10};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    */

    int arr[] = {10,8,9,6,1,10,4,100,7,5,3,4,2,1,1,1,1,1,1,35,46,23,41,76,12,89,98,65,91};
    int arrSize = sizeof(arr)/sizeof(arr[0]);

    int order_statistic = 1;
    int statistic_elem;
    time_t t;

    printf("Array size : %d\n",arrSize);
    //Note that since array index in C is zero based, the value (ith statistic - 1) is
    //passed to RSelect()
    for (int i = 0; i < arrSize; i++) {
        statistic_elem =  DSelect(arr,arrSize,i);
        printf("%d order statistic is %d\n",i+1,statistic_elem);
        getchar();
        //printArray(arr,arrSize);
    }
    printArray(arr,arrSize);
}
