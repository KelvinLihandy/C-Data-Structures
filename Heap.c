#include <stdio.h>
#define SIZE 999
#define parent(i) (i - 1) / 2
#define left(i) i*2+1
#define right(i) i*2+2

int size = 0;

void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

// Function to heapify the tree (Downheap)
void max_heapify(int array[], int i) {
    // Find the largest among root, left child and right child
    int largest = i;
    int l = left(i);
    int r = right(i);
    if (l < size && array[l] > array[i])
        largest = l;
    if (r < size && array[r] > array[largest])
        largest = r;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        swap(&array[i], &array[largest]);
        max_heapify(array, largest);
    }
}

// void build_heap(int array[], int n){
//     size = n;
//     for(int i=parent(size-1);i>=0;i--){
//         max_heapify(array, i);
//     }
// }

int peek(int array[]){
    return array[0];
}

int extract_max(int array[]){
    int max = peek(array);
    array[0] = array[size-1];
    size--;
    max_heapify(array, 0);
    return max;
}

void max_heap_insert(int array[], int k)
{
    size++;
    int i = size - 1;
    array[i] = k;
    // Upheap
    while (i > 0 && array[parent(i)] < array[i])
    {
        swap(&array[i], &array[parent(i)]);
        i = parent(i);
    }
}

// Print the array
void printArray(int array[], int size) {
    for (int i = 0; i < size; ++i)
        printf("%d ", array[i]);
    printf("\n\n");
}

// Driver code
int main() {
    // int arr[SIZE] = {10, 30, 20, 40, 50};
    // size = 5;
    // printf("Raw Array\n");
    // printArray(arr, size);
    // build_heap(arr, 5);
    // printf("After Build Heap\n");
    // printArray(arr, size);
    int arr[SIZE];
    max_heap_insert(arr, 34);
    max_heap_insert(arr, 64);
    max_heap_insert(arr, 94);
    max_heap_insert(arr, 45);
    max_heap_insert(arr, 21);
    printf("After Insert Heap\n");
    printArray(arr, size);
    printf("jobId %d is done...\n", extract_max(arr));
    printf("jobId %d is done...\n", extract_max(arr));
    printf("jobId %d is done...\n", extract_max(arr));
    printf("jobId %d is done...\n", extract_max(arr));
    printf("\nAfter Extracting Heap\n");
    printArray(arr, size);
    return 0;
}