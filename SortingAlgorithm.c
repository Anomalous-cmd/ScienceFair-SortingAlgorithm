#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void display(int arr[], int size);
void rdidxsorting(int arr[], int size);
void mergesort(int arr[], int size);
void mergesortrecursion(int arr[], int l, int r);
void merge_sortedarrays(int arr[], int l, int m, int r);

void swap(int *i, int *j){
    int temp = *i;
    *i = *j;
    *j = temp;
}

void merge_sortedarrays(int arr[], int l, int m, int r){
    int left_length = m-l+1;
    int right_length = r-m;

    int temp_left[left_length];
    int temp_right[right_length];

    int i,j,k;

    for (int i=0; i<left_length; i++){
        temp_left[i] = arr[l+i];
    }
    for (int i=0; i<right_length; i++){
        temp_right[i] = arr[m+1+i];
    }

    for (i=0, j=0, k=l; k<=r;k++){
        if ((i<left_length) && (j >= right_length || temp_left[i] <= temp_right[j])){
            arr[k] = temp_left[i];
            i++;
        }
        else{
            arr[k] = temp_right[j];
            j++;
        }
    }
}

void mergesortrecursion(int arr[], int l, int r){
    if (l<r){
        int m = l+(r-l)/2;

        mergesortrecursion(arr, l, m);
        mergesortrecursion(arr, m+1, r);

        merge_sortedarrays(arr, l, m, r);
    }
}

void mergesort(int arr[], int size){
    mergesortrecursion(arr, 0, size-1);
}

int partition(int arr[], int low, int high){
    int pivot_value = arr[high];
    int i = low;

    for (int j = low; j < high; j++){
        if (arr[j] <= pivot_value){
            swap(&arr[i],&arr[j]);
            i++;
        }
    }

    swap(&arr[i],&arr[high]);
    return i;
}

void quicksortrecursion(int arr[], int low, int high){
    if (low < high){
        int pivot_index = partition(arr, low, high);
        quicksortrecursion(arr, low, pivot_index-1);
        quicksortrecursion(arr, pivot_index+1, high);
    }
}

void quicksort(int arr[], int size){
    quicksortrecursion(arr, 0, size-1);
}

void heapMax(int arr[], int size, int i){
    int largest = i;         // root index
    int left = 2 * i + 1;    // left child
    int right = 2 * i + 2;   // right child

    // If left child is larger than root
    if (left < size && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than the current largest
    if (right < size && arr[right] > arr[largest])
        largest = right;

    // If the largest isn't the root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        // Recursively heap the affected subtree
        heapMax(arr, size, largest);
    }
}

void heapSortMax(int arr[], int size){
    // Step 1: Build Max Heap
    for (int i = size / 2 - 1; i >= 0; i--)
        heapMax(arr, size, i);

    // Step 2: Extract elements one by one
    for (int i = size - 1; i > 0; i--) {
        // Move current root (largest) to end
        swap(&arr[0], &arr[i]);
        // Heap reduced heap
        heapMax(arr, i, 0);
    }
}

int getmaxelement(int arr[], int n){
    int i;
    int maxelement = arr[0];
    for (i = 1; i < n; i++){
        if (arr[i] > maxelement)
            maxelement = arr[i];
    }
    return maxelement;
}

void counting_sort(int arr[], int size, int place){
    int i;
    int output[size+1];
    int max = (arr[0] / place) % 10;

    for (i=1; i < size; i++){
        if (((arr[i] / place) % 10) > max){
            max = (arr[i] / place) % 10;
        }
    }
    int count[10] = {0};

    for (i=0; i < 10; ++i){
        count[i] = 0;
    }

    for (i=0; i < size; i++){
        count[(arr[i] / place) % 10]++;
    }
    
    for (i=1; i < 10; i++){
        count[i] += count[i-1];
    }
    for (i=size - 1; i >= 0; i--){
        output[count[(arr[i] / place) % 10] - 1] = arr[i];
        count[(arr[i] / place) % 10]--;
    }
    for (i=0; i < size; i++){
        arr[i] = output[i];
    }
}

void rdidxsorting(int arr[], int size){
    int place;
    int max = getmaxelement(arr, size);
    for (place = 1; max / place > 0; place *= 10)
        counting_sort(arr, size, place);
}

void insertion_sort(int arr[], int length){

    for (int i = 1; i < length; i++){
        int key = arr[i];
        int j = i-1;
        
        while (j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }

}

void intgenerator(int arr[], int size){

    srand(time(0));

    // Generate a array from 1 to the size max
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    // Shuffle
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1); // random index 0..i
        swap(&arr[i], &arr[j]);
    }
}

void display(int arr[], int size){
    for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
}

void intchoice(){
    printf("Chose size of data (25000 / 50000):");
}

int main(){
    
    clock_t start, end;
    double cpu_time_used;

    int size = 0;
    char choice[30] = "";

    printf("Choose Sorting Algorithm\n1.Insertion Sort 2.Radix Sort 3.Heap Sort 4.Quick Sort 5.Merge Sort\nNo caps, example: insertion sort\n");

    getchar;
    printf("Enter the sorting algorithm want to use: ");
    fgets(choice, sizeof(choice), stdin);
    choice[strlen(choice) -1] = '\0';

    if(!strcmp(choice, "insertion sort")){
        //Insertion Sort
        intchoice();
        scanf("%d", &size);

        int arr[size];

        intgenerator(arr, size);

        clock_t t; 
        t = clock(); 

        //Code For algorithm
        insertion_sort(arr, size);
        display(arr, size);

        t = clock() - t; 
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 

        printf("\nsorting algorithm took %f seconds to execute \n", time_taken);

        printf("\nPress Enter to exit...");
        getchar();
        getchar();
        return 0;
    }
    else if(!strcmp(choice, "radix sort")){
        //Radix Sort
        intchoice();
        scanf("%d", &size);

        int arr[size];

        intgenerator(arr, size);

        clock_t t; 
        t = clock(); 

        //Code For algorithm
        rdidxsorting(arr, size);
        display(arr, size);

        t = clock() - t; 
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 

        printf("\nsorting algorithm took %f seconds to execute \n", time_taken); 
        
        printf("\nPress Enter to exit...");
        getchar();
        getchar();
        return 0;
    }
    else if(!strcmp(choice, "heap sort")){
        //Heap Sort
        intchoice();
        scanf("%d", &size);

        int arr[size];

        intgenerator(arr, size);

        clock_t t; 
        t = clock(); 

        //Code For algorithm
        heapSortMax(arr, size);
        display(arr, size);

        t = clock() - t; 
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 

        printf("\nsorting algorithm took %f seconds to execute \n", time_taken);
        
        printf("\nPress Enter to exit...");
        getchar();
        getchar();
        return 0;
    }
    else if(!strcmp(choice, "quick sort")){
        //Quick Sort
        intchoice();
        scanf("%d", &size);

        int arr[size];

        intgenerator(arr, size);

        clock_t t; 
        t = clock(); 

        //Code For algorithm
        quicksort(arr, size);
        display(arr, size);

        t = clock() - t; 
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 

        printf("\nsorting algorithm took %f seconds to execute \n", time_taken);

        printf("\nPress Enter to exit...");
        getchar();
        getchar();
        return 0;
    }
    else if(!strcmp(choice, "merge sort")){
        //Merge Sort
        intchoice();
        scanf("%d", &size);

        int arr[size];

        intgenerator(arr, size);

        clock_t t; 
        t = clock(); 

        //Code For algorithm
        mergesort(arr, size);
        display(arr, size);

        t = clock() - t; 
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 

        printf("\nsorting algorithm took %f seconds to execute \n", time_taken);

        printf("\nPress Enter to exit...");
        getchar();
        getchar();
        return 0;
    }
    else{
        printf("Invalid format");
        printf("\nPress Enter to exit...");
        getchar();
        return 0;
    }
    return 0;
}