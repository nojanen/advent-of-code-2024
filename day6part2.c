/*

Advent of Code 2024, day 6, part 2

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

#define MAX_MOVES 10000

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

int add_obstruction(int round) {
    for (int row=0; row < DATA_ROWS; row++) {
        for (int col=0; col < DATA_COLS; col++) {
            if (g_data[row][col] == 'O') {
                g_data[row][col] = 'X';
            }
            if (g_data[row][col] == 'X') {
                if(round-- <= 0) {
                    g_data[row][col] = 'O';
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

void turn_right() {
    g_direction += 1;
    g_direction %= 4;
}

int move(int x, int y, int mark) {
    if (g_x+x < 0 || g_y+y < 0 || g_x+x >= DATA_COLS || g_y+y >= DATA_ROWS) {
        return TRUE;
    }

    if (g_data[g_y+y][g_x+x] != '#' && g_data[g_y+y][g_x+x] != 'O') {
        g_x += x;
        g_y += y;
        if (mark == TRUE) {
            g_data[g_y][g_x] = 'X';
        }
    } else {
        turn_right();
    }

    return FALSE;
}

int one_round(int mark) {
    int exit = FALSE;
    int moves = 0;

    find_start();
    g_direction = UP;

    while (!exit && moves++ < 10000) {
        switch (g_direction)
        {
        case UP:
            exit = move(0, -1, mark);
            break;
        case RIGHT:
            exit = move(1, 0, mark);
            break;
        case DOWN:
            exit = move(0, 1, mark);
            break;
        case LEFT:
            exit = move(-1, 0, mark);
            break;
        default:
            printf("Unknown direction: %d", g_direction);
            return 2;
        }
    }
    return exit;
}

int main() {
    char chr;
    int line = 0;
    int result = 0;

    FILE *file = fopen("day6data.txt", "r");
    if (file == NULL) {
        printf("Error reading file");
        return 1;
    }

    while (fscanf(file, "%s", g_data[line++]) >= 0);

    one_round(TRUE);

    for (int round=0; add_obstruction(round); round++) {
        if (!one_round(FALSE)) {
            result++;
        }
    }

    printf("Result: %d\n", result);
    result == 1602 && printf("Result is correct\n");

    return 0;
}
