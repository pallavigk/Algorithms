#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//The RSelect Algorithm
//RSelect(array A, length n, order statistic i)
//1. If n = 1, return A[1]
//2. Choose pivot p from A uniformly at random
//3. Partition A around p
//4. If j = i return p
//5. If j > i return RSelect(1st part of A,j-1,i)
//6. [else if j < i] return RSelect(2nd part of A, n-j, i-j)


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


//The functions Partition() and RSelect() can also be implemented by sending
//left and right index of the array instead of arrSize. left and right index
//logic is used in quick_sort.c. Refer to that program for details.

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

int RSelect(int arr[], int arrSize, int ithOrder) {
    if (arrSize <= 1) 
        return arr[0];
    //Step 2: Choose a pivot  from array uniformly at random 
    int random_index =  rand() % arrSize; 
 
    //As in quick sort, swap the pivot element with a[0] and
    //then partition the array wrt to a[0]
    swap(&arr[0],&arr[random_index]);
    int pivot_position = Partition(arr,arrSize);


    if (pivot_position == ithOrder)  //This is the statistic we are looking for
        return arr[pivot_position];
    
    if (pivot_position < ithOrder)  //Pivot's position is left to ith order statistic, so recurse right
        return RSelect(arr+pivot_position+1,arrSize-(pivot_position+1),ithOrder-(pivot_position+1));
    else //Pivot's position is right of ith order, so recurse left
        return RSelect(arr,pivot_position,ithOrder);
    
}
int main() {
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

    int arr[] = {10,8,9,6,1,10,4,100,7,5,3,4,2,1,1,1,1,1,1};
    int arrSize = sizeof(arr)/sizeof(arr[0]);

    int order_statistic = 1;
    int statistic_value;
    time_t t;

    //To get a different seed on each execution
    srand((unsigned) time(&t));

    //Note that since array index in C is zero based, the value (ith statistic - 1) is
    //passed to RSelect()
    for (int i = 0; i < arrSize; i++) {
        statistic_value =  RSelect(arr,arrSize,i);
        printf("%d order statistic is %d\n",i+1,statistic_value);
        //printArray(arr,arrSize);
    }
    printArray(arr,arrSize);
}
