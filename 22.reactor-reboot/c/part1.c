
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAXX(X, Y, Z) MAX(X, MAX(Y, Z))
#define MINN(X, Y, Z) MIN(X, MIN(Y, Z))

typedef struct {
    long x[2], y[2], z[2];
} Box;

typedef struct {
    Box box;
    bool on;
} Step;

long cubes(Step* steps, size_t n) {
    if (n == 0) {
        return 0;
    } else if (!steps[0].on) {
        return cubes(steps + 1, n - 1);
    } else {
        Box head = steps[0].box;
        if (MINN(head.x[0], head.y[0], head.z[0]) >= -50 && MAXX(head.x[1], head.y[1], head.z[1]) <= 50) {
            size_t maxm = 32;
            Step* intrs = malloc(sizeof(Step) * maxm);
            size_t m = 0;
            for (size_t i = 1; i < n; i++) {
                Box box = steps[i].box;
                Box intr;
                intr.x[0] = MAX(head.x[0], box.x[0]); intr.x[1] = MIN(head.x[1], box.x[1]);
                intr.y[0] = MAX(head.y[0], box.y[0]); intr.y[1] = MIN(head.y[1], box.y[1]);
                intr.z[0] = MAX(head.z[0], box.z[0]); intr.z[1] = MIN(head.z[1], box.z[1]);
                if (intr.x[1] >= intr.x[0] && intr.y[1] >= intr.y[0] && intr.z[1] >= intr.z[0]) {
                    if (m == maxm) {
                        maxm *= 2;
                        intrs = realloc(intrs, sizeof(Step) * maxm);
                    }
                    intrs[m].box = intr;
                    intrs[m].on = true;
                    m++;
                }
            }
            long result = cubes(steps + 1, n - 1) - cubes(intrs, m);
            free(intrs);
            return result + (head.x[1] - head.x[0] + 1) * (head.y[1] - head.y[0] + 1) * (head.z[1] - head.z[0] + 1);
        } else {
            return cubes(steps + 1, n - 1);
        }
    }
}

int main() {
    size_t maxn = 32;
    Step* steps = malloc(sizeof(Step) * maxn);
    size_t n = 0;
    Box b;
    char cmd[16];
    while (fscanf(stdin, "%s x=%li..%li,y=%li..%li,z=%li..%li", cmd, &b.x[0], &b.x[1], &b.y[0], &b.y[1], &b.z[0], &b.z[1]) == 7) {
        if (n == maxn) {
            maxn *= 2;
            steps = realloc(steps, sizeof(Step) * maxn);
        }
        steps[n].box = b;
        steps[n].on = cmd[1] == 'n';
        n++;
    }
    fprintf(stdout, "Result: %li\n", cubes(steps, n));
    free(steps);
}

