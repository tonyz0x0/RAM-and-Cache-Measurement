#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MB 1 << 20
#define SIZE 80
#define BLOCK (SIZE * (MB))

unsigned int ramSize = 0;
void estimate();

/*
 * The main method is to continuously call malloc() and memset()
 * to ask memory from operating system. When the physical memory is
 * nearly occupied, the thrashing will occur and we will detect it by compare
 * the time we spend on memset() between last time and this time. The total allocate memory is
 * the approximated size of RAM.
 */

int main() {
    estimate();
    printf("The approximate RAM size is: %.2f GB | %d MB\n", ((double)ramSize / 1024.0), ramSize);
}

void estimate() {
    double currentTime = 0, prevTime = 0;
    int i = 0, j = 0;
    clock_t begin;
    void *arr[1000];


    for (i = 0 ; i < 1000; i++) {
        arr[i] = malloc(BLOCK);
        if (arr[i] == NULL)
        {
            printf("\nOut of Memory!\n");
            return;
        }
        prevTime = currentTime;
        begin = clock();
        for(j = 0; j < i; j++) {
            memset(arr[j], 0, BLOCK);
        }
        currentTime = (double)(clock() - begin)/CLOCKS_PER_SEC;
        ramSize += SIZE;
        printf("Calculating...... RAM： %d MB, Previous Time : %lf, Current Time : %lf\n", ramSize, prevTime, currentTime);
        if ((prevTime != 0) && ((2 * prevTime) < currentTime)) {
            for (j = 0; j < i; j++) {
                free(arr[j]);
            }
            break;
        }
    }
}