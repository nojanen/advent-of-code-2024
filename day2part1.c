/*

Advent of Code 2024, day 2, part 1

*/
#include <stdio.h>

#define ARRAY_SIZE 1024

int main() {
    int array[ARRAY_SIZE];
    int len = 0;

    int total = 0;
    int unsafe = 0;

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
            total++;
            if (len > 1) {
                int asc = array[0] < array[1];
                for (int i=0; i<len-1; i++) {
                    int diff = asc ? array[i+1] - array[i] : array[i] - array[i+1];
                    if (diff < 1 || diff > 3) {
                        unsafe++;
                        break;
                    }
                }
            }
            len = 0;
        } 
    }

    if (len > ARRAY_SIZE) {
        printf("Buffer overflow!");
        return 2;
    }


    printf("Result: %d\n", total - unsafe);
    (total - unsafe) == 572 && printf("Result is correct");
    return 0;
}
