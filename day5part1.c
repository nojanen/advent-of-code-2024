/*

Advent of Code 2024, day 5, part 1

*/
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define MAP_SIZE 100

// Lazy me, cheated with the input data map size.
#define INPUT_MAP_LINES 1176

int g_map[MAP_SIZE][MAP_SIZE];
int g_map_len[MAP_SIZE];

void read_map(FILE *file) {
    int p1, p2;

    memset(g_map_len, 0, MAP_SIZE*sizeof(int));

    for (int i=0; i < INPUT_MAP_LINES; i++) {
        if (fscanf(file, "%d|%d", &p1, &p2) < 2) {
            break;
        }
        g_map[p1][g_map_len[p1]++] = p2;
    };
}

int count_same(int array1[], int len1, int array2[], int len2) {
    int same = 0;
    for (int i=0; i<len1; i++) {
        for (int j=0; j<len2; j++) {
            if (array1[i] == array2[j]) {
                same++;
            }
        }
    }
    return same;
}

int match_to_map(int array[], int len) {
    int matches = 0;
    for (int i=len-1; i > 0; i--) {
        matches += count_same(g_map[array[i]], g_map_len[array[i]], array, i);
    }
    return matches;
}

int main() {
    char chr;
    int p1, p2;
    int result = 0;

    int array[MAP_SIZE];
    int len = 0;

    FILE *file = fopen("day5data.txt", "r");
    if (file == NULL) {
        printf("Error reading file");
        return 1;
    }

    read_map(file);

    while (fscanf(file, "%d%c", &p1, &chr) >= 0) {
        array[len++] = p1;
        if (chr == '\n') {
            if (match_to_map(array, len) == 0) {
                result += array[len/2];
            }
            len = 0;
        }
    };

    printf("Result: %d\n", result);
    result == 4185 && printf("Result is correct\n");

    return 0;
}
