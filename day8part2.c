/*

Advent of Code 2024, day 8, part 2

*/
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define ANY '.'

#define MAP_SIZE 50

char g_map[MAP_SIZE][MAP_SIZE];
char g_result[MAP_SIZE][MAP_SIZE];

int find_next(int *x, int *y, char chr, int skip) {
    for (; *y < MAP_SIZE; (*y)++) {
        for (;*x < MAP_SIZE; (*x)++) {
            if (skip == FALSE 
                && ((chr != ANY && g_map[*y][*x] == chr) 
                || (chr == ANY && g_map[*y][*x] != ANY))) {
                return TRUE;
            }
            skip = FALSE;
        }
        *x = 0;
    }
    return FALSE;
}

void mark_antinodes(int x1, int y1, int x2, int y2) {
    int dx = x1-x2;
    int dy = y1-y2;
    int harmonics = 0;
    int node_in_map = TRUE;

    while (node_in_map) {
        int hx = dx * harmonics;
        int hy = dy * harmonics;

        node_in_map = FALSE;

        if (x1+hx >= 0 && x1+hx < MAP_SIZE && y1+hy >= 0 && y1+hy < MAP_SIZE) {
            g_result[y1+hy][x1+hx] = '#';
            node_in_map = TRUE;
        }

        if (x2-hx >= 0 && x2-hx < MAP_SIZE && y2-hy >= 0 && y2-hy < MAP_SIZE) {
            g_result[y2-hy][x2-hx] = '#';
            node_in_map = TRUE;
        }
        harmonics++;
    }
}


int sum_antinodes() {
    int result = 0;
    for (int y=0; y < MAP_SIZE; y++) {
        for (int x=0; x < MAP_SIZE; x++) {
            // printf("%c ", g_result[y][x]);
            if (g_result[y][x] == '#') {
                result++;
            }
        }
        // printf("\n");
    }
    return result;
}

int main() {
    int line = 0;
    int result = 0;

    memset(g_result, '.', MAP_SIZE * MAP_SIZE * sizeof(char));

    FILE *file = fopen("day8data.txt", "r");
    if (file == NULL) {
        printf("Error reading file");
        return 1;
    }

    while (fscanf(file, "%s", g_map[line++]) >= 0);

    int x=0, y=0;
    while (find_next(&x, &y, ANY, TRUE) == TRUE) {
        int nx = x;
        int ny = y;
        while (find_next(&nx, &ny, g_map[ny][nx], TRUE) == TRUE) {
            mark_antinodes(x, y, nx, ny);
        }
    }
 
    result = sum_antinodes();
    printf("Result: %d\n", result);
    result == 1019 && printf("Result is correct\n");

    return 0;
}
