/*

Advent of Code 2024, day 1, part 2

*/
#include <stdio.h>

#define ARRAY_SIZE 1024

int main() {
    int array1[ARRAY_SIZE];
    int array2[ARRAY_SIZE];

    int *ptr1 = array1;
    int *ptr2 = array2;

    int len = 0;
    int score = 0;
    int match = 0;

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

    for (int i=0; i<len; i++) {
        for(int j=0; j<len; j++) {
            if (array1[i] == array2[j]) {
                match++;
            }
        }
        score += array1[i] * match;
        match = 0;
    }

    printf("Result: %d\n", score);
    score == 23741109 &&  printf("Result is correct\n");
    return 0;
}
