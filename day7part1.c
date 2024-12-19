/*

Advent of Code 2024, day 7, part 1

*/
#include <stdio.h>

#define ARRAY_SIZE 20
#define POW(n) (llu)1<<(n)
#define NTH_BIT(v,i) (((v)>>(i))&1)

typedef unsigned long long int llu;

llu calculate(llu array[], int len) {
    for (llu mask=0; mask < POW(len-2); mask++) {
        llu val = array[1];
        for (int i=2; i < len; i++) {
            if (NTH_BIT(mask, i-2)) {
                val += array[i];
            } else {
                val *= array[i];
            } 
        }

        if (val == array[0]) {
            return array[0];
        }
    }
    return 0;
}

int main() {
    llu array[ARRAY_SIZE];
    llu *ptr = array;
    char chr;
    int len = 0;

    llu result = 0;

    FILE *file = fopen("day7data.txt", "r");
    if (file == NULL) {
        printf("Error reading file");
        return 1;
    }

    while (fscanf(file, "%llu%c", ptr++, &chr) >= 0) {
        len++;
        if (len >= ARRAY_SIZE) {
            printf("Buffer overflow!");
            return 2;
        }

        if (chr == '\n') {
            result += calculate(array, len);
            ptr = array;
            len = 0;
        } 
    }

    printf("Result: %llu\n", result);
    result == 3351424677624 && printf("Result is correct\n");
    return 0;
}
