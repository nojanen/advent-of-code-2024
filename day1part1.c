/*

Advent of Code 2024, day 1, part 1

*/
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1024

int comp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int array1[ARRAY_SIZE];
    int array2[ARRAY_SIZE];

    int *ptr1 = array1;
    int *ptr2 = array2;

    int len = 0;
    int dist = 0;

    FILE *file = fopen("day1data.txt", "r");
    if (file == NULL) {
        printf("Error reading file");
        return 1;
    }

    while (fscanf(file, "%d %d", ptr1++, ptr2++) >= 0 && len <= ARRAY_SIZE) {
        len++;
    }

    if (len > ARRAY_SIZE) {
        printf("Buffer overflow!");
        return 2;
    }

    qsort(array1, len, sizeof(int), comp);
    qsort(array2, len, sizeof(int), comp);

    for (int i=0; i<len; i++) {
        int sub = array1[i] - array2[i];
        dist += sub<0 ? -sub : sub;
    }

    printf("Result: %d\n", dist);
    dist == 2166959 &&  printf("Result is correct\n");

    return 0;
}
