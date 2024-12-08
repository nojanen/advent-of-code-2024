/*

Advent of Code 2024, day 3, part 1

*/
#include <stdio.h>
#include <ctype.h>

int main() {
    int a = 0;
    int b = 0;
    char chr;
    int matches = 0;

    int result = 0;

    FILE *file = fopen("day3data.txt", "r");
    if (file == NULL) {
        printf("Error reading file");
        return 1;
    }

    while (fscanf(file, "%c", &chr) >= 0) {
        if (chr == 'm') {
            matches = 1;
            continue;
        }
        if (chr == 'u' && matches == 1) {
            matches = 2;
            continue;
        }
        if (chr == 'l' && matches == 2) {
            matches = 3;
            continue;
        }
        if (chr == '(' && matches == 3) {
            matches = 4;
            continue;
        }
        if (isdigit(chr) && (matches == 4 || matches == 5)) {
            matches = 5;
            a = (a * 10) + chr - '0';
            continue;
        }
        if (chr == ',' && matches == 5) {
            matches = 6;
            continue;

        }
        if (isdigit(chr) && (matches == 6 || matches == 7)) {
            matches = 7;
            b = (b * 10) + chr - '0';
            continue;
        }
        if (chr == ')' && matches == 7) {
            result += a * b;
        }
        matches = 0;
        a = 0;
        b = 0;
    }

    printf("Result: %d\n", result);
    result == 161289189 &&  printf("Result is correct\n");

    return 0;
}
