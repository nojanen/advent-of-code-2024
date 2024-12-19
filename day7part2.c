/*

Advent of Code 2024, day 7, part 2

*/
#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define ARRAY_SIZE 20
#define POW(n) (llu)(1<<(n))
#define NTH_BIT(v,i) (((v)>>(i))&1)

typedef unsigned long long int llu;

llu concat(llu a, llu b) {
    for (llu tmp = b; tmp > 0; tmp /= 10) {
        a *= 10;
    }
    return a + b;
}

llu calculate(llu array[], int len) {
    for (llu cc_mask=0; cc_mask < POW(len-2); cc_mask++) {
        for (llu op_mask=0; op_mask < POW(len-2); op_mask++) {
            llu val = array[1];
            for (int i=2; i < len; i++) {
                if (NTH_BIT(cc_mask, i-2)) {
                    val = concat(val, array[i]);
                } else if (NTH_BIT(op_mask, i-2)) {
                    val += array[i];
                } else {
                    val *= array[i];
                } 
            }

            if (val == array[0]) {
                return array[0];
            }
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
    result == 204976636995111 && printf("Result is correct\n");
    return 0;
}
