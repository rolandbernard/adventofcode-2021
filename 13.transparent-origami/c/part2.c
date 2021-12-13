
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Point {
    int x;
    int y;
} points[1 << 20];

struct Fold {
    char d;
    int v;
} folds[1 << 10];

void applyFold(int n, struct Fold fold) {
    if (fold.d == 'x') {
        for (int i = 0; i < n; i++) {
            if (points[i].x > fold.v) {
                points[i].x = 2 * fold.v - points[i].x;
            }
        }
    } else if (fold.d == 'y') {
        for (int i = 0; i < n; i++) {
            if (points[i].y > fold.v) {
                points[i].y = 2 * fold.v - points[i].y;
            }
        }
    }
}

int main() {
    int n = 0, m = 0;
    int x, y;
    while (fscanf(stdin, " %i,%i", &x, &y) == 2) {
        points[n].x = x;
        points[n].y = y;
        n++;
    }
    char d;
    while (fscanf(stdin, " fold along %c=%i", &d, &x) == 2) {
        folds[m].d = d;
        folds[m].v = x;
        m++;
    }
    for (int i = 0; i < m; i++) {
        applyFold(n, folds[i]);
    }
    int minx = INT_MAX, miny = INT_MAX, maxx = INT_MIN, maxy = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (points[i].x < minx) {
            minx = points[i].x;
        }
        if (points[i].y < miny) {
            miny = points[i].y;
        }
        if (points[i].x > maxx) {
            maxx = points[i].x;
        }
        if (points[i].y > maxy) {
            maxy = points[i].y;
        }
    }
    fprintf(stdout, "Result:\n");
    bool paper[maxx - minx + 1][maxy - miny + 1];
    for (int y = miny; y <= maxy; y++) {
        for (int x = minx; x <= maxx; x++) {
            paper[x][y] = false;
        }
    }
    for (int i = 0; i < n; i++) {
        paper[points[i].x][points[i].y] = true;
    }
    for (int y = miny; y <= maxy; y++) {
        for (int x = minx; x <= maxx; x++) {
            if (paper[x][y]) {
                fprintf(stdout, "\e[97m#\e[m");
            } else {
                fprintf(stdout, "\e[90m.\e[m");
            }
        }
        fprintf(stdout, "\n");
    }
}

