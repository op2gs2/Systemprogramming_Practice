#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(void) {

    int size = 10; // Size of *arr
    int n = 0; // Number of int data in *arr
    int* arr, * temp_arr; // Array that store data
    int sum = 0; // Sum of numbers stored in *arr

    arr = (int*)malloc(sizeof(int) * size);
    printf("n: %d, size: %d, sum: %d\n", n, size, sum);

    int i = 0, j = 0;

    // Store 1 to 100
    for (i = 1; i <= 100; i++) {
        if (n == size) {
            #ifdef DEBUG
            printf("Size up: %d => %d\n", size, size * 2);
            #endif

            // make a *temp_arr, move value from *arr to *temp_arr
            temp_arr = (int*)malloc(sizeof(int) * size * 2);
            for (j = 0; j < size; j++) {
                temp_arr[j] = arr[j];
            }

            // Organize array and size variable.
            arr = temp_arr;
            free(temp_arr);
            size = size * 2;

            // Include result of this period.
            arr[i - 1] = i;
            n++; sum += i;
        }
        else if (n < size) {
            arr[i - 1] = i;
            n++; sum += i;
        }
        else {
            assert(0);
        }
    }

    printf("n: %d, size: %d, sum: %d\n", n, size, sum);

    // Delete 100 to 11
    for (i = 100; i > 10; i--) {
        if (n <= size / 4) {
            #ifdef DEBUG
            printf("Size down: %d => %d\n", size, size / 2);
            #endif

            // make a *temp_arr, move value from *arr to *temp_arr
            temp_arr = (int*)malloc(sizeof(int) * size / 2);
            for (j = 0; j < size; j++) {
                temp_arr[j] = arr[j];
            }

            // Organize array and size variable.
            arr = temp_arr;
            free(temp_arr);
            size = size / 2;

            // Include result of this period.
            arr[i] = 0;
            n--; sum -= i;
        }
        else if (n < size) {
            arr[i] = 0;
            n--; sum -= i;
        }
        else {
            assert(0);
        }
    }

    printf("n: %d, size: %d, sum: %d\n", n, size, sum);

    free(0);
    return 0;
}
