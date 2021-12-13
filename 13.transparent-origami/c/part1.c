
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

int comparePoints(const struct Point* p1, const struct Point* p2) {
    if (p1->x != p2->x) {
        return p1->x - p2->x;
    } else {
        return p1->y - p2->y;
    }
}

int reducePoints(int n) {
    qsort(points, n, sizeof(struct Point), (void*)comparePoints);
    int c = 1;
    for (int i = 1; i < n; i++) {
        if (comparePoints(points + i, points + c - 1) != 0) {
            points[c] = points[i];
            c++;
        }
    }
    return c;
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
    applyFold(n, folds[0]);
    fprintf(stdout, "Result: %i\n", reducePoints(n));
}

