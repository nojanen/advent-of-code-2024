/*

Advent of Code 2024, day 6, part 1

*/
#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define DATA_ROWS 130
#define DATA_COLS 130

char g_data[DATA_ROWS][DATA_COLS];
int g_x, g_y;
int g_direction = UP;

void find_start() {
    for (int row=0; row < DATA_ROWS; row++) {
        for (int col=0; col < DATA_COLS; col++) {
            if (g_data[row][col] == '^') {
                g_y = row;
                g_x = col;
                return;
            }
        }
    }
}

void turn_right() {
    g_direction = ++g_direction % 4;
}

int move(int x, int y) {
    if (g_x+x < 0 || g_y+y < 0 || g_x+x >= DATA_COLS || g_y+y >= DATA_ROWS) {
        return TRUE;
    }

    if (g_data[g_y+y][g_x+x] != '#') {
        g_x += x;
        g_y += y;
        g_data[g_y][g_x] = 'X';
    } else {
        turn_right();
    }

    return FALSE;
}

int main() {
    char chr;
    int line = 0;
    int result = 0;
    int exit = FALSE;
    int moves = 0;

    FILE *file = fopen("day6data.txt", "r");
    if (file == NULL) {
        printf("Error reading file");
        return 1;
    }

    while (fscanf(file, "%s", g_data[line++]) >= 0);

    find_start();

    while (!exit) {
        moves++;
        switch (g_direction)
        {
        case UP:
            exit = move(0, -1);
            break;
        case RIGHT:
            exit = move(1, 0);
            break;
        case DOWN:
            exit = move(0, 1);
            break;
        case LEFT:
            exit = move(-1, 0);
            break;
        default:
            printf("Unknown direction: %d", g_direction);
            return 2;
        }
    }

    for (int row=0; row < DATA_ROWS; row++) {
        for(int col=0; col < DATA_COLS; col++) {
            if (g_data[row][col] == 'X' || g_data[row][col] == '^') {
                result++;
            }
        }
    }

    printf("Result: %d\n", result);
    result == 4722 && printf("Result is correct\n");

    return 0;
}
