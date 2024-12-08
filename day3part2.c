/*

Advent of Code 2024, day 3, part 2

*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    char word[10];
    int matches;
    int data[2];
    void (*callback)(int*);
} word_t;

void match(word_t* w, char chr) {
    if (chr == (*w).word[0]) {
        (*w).matches = 1;
        return;
    }

    if (isdigit((*w).word[(*w).matches])) {
        if (isdigit(chr)) {
            int index = (int)((*w).word[(*w).matches] -'0');
            (*w).data[index] = (*w).data[index] * 10 + chr - '0';
            return;
        } else if (chr == (*w).word[(*w).matches+1]) {
            ((*w).matches)++;
        }
    }

    if (chr == (*w).word[(*w).matches]) {
        ((*w).matches)++;
        if ((*w).matches >= strlen((*w).word)) {
            (*w).callback((*w).data);
            (*w).matches = 0;
            (*w).data[0] = 0;
            (*w).data[1] = 0;
            return;
        }
        return;
    }

    (*w).matches = 0;
    (*w).data[0] = 0;
    (*w).data[1] = 0;
    return;
}

int g_result = 0;
int g_enabled = TRUE;

void calculate(int* data) {
    if (g_enabled == TRUE) {
        g_result += data[0] * data[1];
    }
}

void enable(int* data) {
    g_enabled = TRUE;
}

void disable(int* data) {
    g_enabled = FALSE;
}

int main() {
    char chr;

    word_t calculate_trigger = {"mul(0,1)", 0, {0, 0}, calculate}; 
    word_t disable_trigger = {"don't()", 0, {0, 0}, disable}; 
    word_t enable_trigger = {"do()", 0, {0, 0}, enable}; 

    FILE *file = fopen("day3data.txt", "r");
    if (file == NULL) {
        printf("Error reading file");
        return 1;
    }

    while (fscanf(file, "%c", &chr) >= 0) {
        match(&calculate_trigger, chr);
        match(&enable_trigger, chr);
        match(&disable_trigger, chr);
    }

    printf("Result: %d\n", g_result);
    g_result == 83595109 &&  printf("Result is correct\n");

    return 0;
}
