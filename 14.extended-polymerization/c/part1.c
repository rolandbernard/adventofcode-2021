
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NUM_LETTERS 26
#define MAX_INSTR (NUM_LETTERS * NUM_LETTERS)

size_t freq[NUM_LETTERS];
size_t pairs[NUM_LETTERS][NUM_LETTERS];
size_t x;
struct Instr {
    int a1, a2, b;
} instr[MAX_INSTR];
size_t instr_count;

void applyInstructions() {
    size_t new_pairs[26][26];
    memcpy(new_pairs, pairs, sizeof(pairs));
    for (size_t i = 0; i < instr_count; i++) {
        size_t n = pairs[instr[i].a1][instr[i].a2];
        new_pairs[instr[i].a1][instr[i].a2] -= n;
        new_pairs[instr[i].a1][instr[i].b] += n;
        new_pairs[instr[i].b][instr[i].a2] += n;
        freq[instr[i].b] += n;
    }
    memcpy(pairs, new_pairs, sizeof(pairs));
}

int main() {
    char* line = NULL;
    size_t size = 0;
    size_t length = getline(&line, &size, stdin);
    for (size_t i = 0; i < length - 1; i++) {
        freq[line[i] - 'A']++;
    }
    for (size_t i = 0; i < length - 2; i++) {
        pairs[line[i] - 'A'][line[i + 1] - 'A']++;
    }
    free(line);
    char a1, a2, b;
    while (fscanf(stdin, "\n%c%c -> %c", &a1, &a2, &b) == 3) {
        instr[instr_count].a1 = a1 - 'A';
        instr[instr_count].a2 = a2 - 'A';
        instr[instr_count].b = b - 'A';
        instr_count++;
    }
    for (size_t i = 0; i < 10; i++) {
        applyInstructions();
    }
    size_t min = SIZE_MAX;
    size_t max = 0;
    for (size_t i = 0; i < NUM_LETTERS; i++) {
        if (freq[i] > 0 && freq[i] < min) {
            min = freq[i];
        }
        if (freq[i] > max) {
            max = freq[i];
        }
    }
    fprintf(stderr, "Result: %lu\n", max - min);
}

