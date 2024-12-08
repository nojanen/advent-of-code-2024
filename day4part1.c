/*

Advent of Code 2024, day 4, part 1

*/
#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define DATA_ROWS 140
#define DATA_COLS 140

typedef struct {
    char matrix[4][4];
    int rows;
    int cols;
} matrix_t;

char g_data[DATA_ROWS][DATA_COLS];

matrix_t g_matrix1 = {{
    {'X','M','A','S'},
    {' ',' ',' ',' '},
    {' ',' ',' ',' '},
    {' ',' ',' ',' '}
}, 1, 4};
matrix_t g_matrix2 = {{
    {'S','A','M','X'},
    {' ',' ',' ',' '},
    {' ',' ',' ',' '},
    {' ',' ',' ',' '}
}, 1, 4};
matrix_t g_matrix3 = {{
    {'X',' ',' ',' '},
    {'M',' ',' ',' '},
    {'A',' ',' ',' '},
    {'S',' ',' ',' '}
}, 4, 1};
matrix_t g_matrix4 = {{
    {'S',' ',' ',' '},
    {'A',' ',' ',' '},
    {'M',' ',' ',' '},
    {'X',' ',' ',' '}
}, 4, 1};

matrix_t g_matrix5 = {{
    {'X',' ',' ',' '},
    {' ','M',' ',' '},
    {' ',' ','A',' '},
    {' ',' ',' ','S'}
}, 4, 4};
matrix_t g_matrix6 = {{
    {'S',' ',' ',' '},
    {' ','A',' ',' '},
    {' ',' ','M',' '},
    {' ',' ',' ','X'}
}, 4, 4};
matrix_t g_matrix7 = {{
    {' ',' ',' ','X'},
    {' ',' ','M',' '},
    {' ','A',' ',' '},
    {'S',' ',' ',' '}
}, 4, 4};
matrix_t g_matrix8 = {{
    {' ',' ',' ','S'},
    {' ',' ','A',' '},
    {' ','M',' ',' '},
    {'X',' ',' ',' '}
}, 4, 4};


int match(int row, int col, matrix_t* m) {
    if (row + m->rows > DATA_ROWS || col + m->cols > DATA_COLS) {
        return FALSE;
    }
    for (int i=0; i < m->rows; i++) {
        for (int j=0; j < m->cols; j++) {
            if (m->matrix[i][j] == ' ') {
                continue;
            }
            if (m->matrix[i][j] != g_data[row+i][col+j]) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

int main() {
    char chr;
    int line = 0;
    int result = 0;

    FILE *file = fopen("day4data.txt", "r");
    if (file == NULL) {
        printf("Error reading file");
        return 1;
    }

    while (fscanf(file, "%s", g_data[line++]) >= 0);

    for (int row=0; row < DATA_ROWS; row++) {
        for (int col=0; col < DATA_COLS; col++) {
            match(row, col, &g_matrix1) && result++;
            match(row, col, &g_matrix2) && result++;
            match(row, col, &g_matrix3) && result++;
            match(row, col, &g_matrix4) && result++;
            match(row, col, &g_matrix5) && result++;
            match(row, col, &g_matrix6) && result++;
            match(row, col, &g_matrix7) && result++;
            match(row, col, &g_matrix8) && result++;
        }
    }

    printf("Result: %d\n", result);
    result == 2358 && printf("Result is correct\n");

    return 0;
}
