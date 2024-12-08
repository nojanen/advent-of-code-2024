/*

Advent of Code 2024, day 2, part 1

*/
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define ARRAY_SIZE 1024

int is_safe(int array[], int len) {
    if (len > 1) {
        int asc = array[0] < array[1];
        for (int i=0; i<len-1; i++) {
            int diff = asc ? array[i+1] - array[i] : array[i] - array[i+1];
            if (diff < 1 || diff > 3) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

int* new_without_elem(int array[], int len, int skip) {
    int* new_array = malloc((len-1) * sizeof(int));
    for (int i=0, j=0; i<len; i++, j++) {
        if (i==skip) {
            j--;
        } else {
            new_array[j] = array[i];
        }
    }
    return new_array;
}

int main() {
    int array[ARRAY_SIZE];
    int len = 0;

    int safe = 0;

    int num = 0;
    char chr = ' ';
    
    FILE *file = fopen("day2data.txt", "r");
    if (file == NULL) {
        printf("Error reading file");
        return 1;
    }

    while (fscanf(file, "%d%c", &num, &chr) >= 0 && len < ARRAY_SIZE) {
        array[len++] = num;
        if (chr == '\n') {
            for(int i=0; i<len; i++) {
                int* arr = new_without_elem(array, len, i);
                int res = is_safe(arr, len-1);
                free(arr);
                if (res == TRUE) {
                    safe++;
                    break;
                }
            }
            len = 0;
        } 
    }

    if (len > ARRAY_SIZE) {
        printf("Buffer overflow!");
        return 2;
    }


    printf("Result: %d\n", safe);
    safe == 612 && printf("Result is correct");
    return 0;
}
