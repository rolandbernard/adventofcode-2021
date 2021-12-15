
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100

int map[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];

int qu[MAX_N][MAX_N][2];
int ql[MAX_N];
int qu_off = 0;
int qu_ind = 0;
int qu_siz = 0;

void quPop(int* x, int* y) {
    while (ql[qu_ind] == 0) {
        qu_ind = (qu_ind + 1) % MAX_N;
        qu_off++;
    }
    *x = qu[qu_ind][ql[qu_ind] - 1][0];
    *y = qu[qu_ind][ql[qu_ind] - 1][1];
    ql[qu_ind]--;
    qu_siz--;
}

void quPush(int x, int y) {
    int i = (qu_ind + dist[x][y] - qu_off) % MAX_N;
    qu[i][ql[i]][0] = x;
    qu[i][ql[i]][1] = y;
    ql[i]++;
    qu_siz++;
}

int main() {
    int n = 0, m = 0;
    char c;
    while ((c = getc(stdin)) != EOF) {
        m = 0;
        do {
            map[n][m] = c - '0';
            m++;
        } while ((c = getc(stdin)) != '\n');
        n++;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dist[i][j] = INT_MAX;
        }
    }
    dist[0][0] = 0;
    qu[qu_ind][0][0] = 0;
    qu[qu_ind][0][1] = 0;
    ql[qu_ind] = 1;
    qu_siz++;
    while (qu_siz != 0) {
        int x, y;
        quPop(&x, &y);
        if (x == n - 1 && y == m - 1) {
            break;
        } else {
            if (x != 0 && dist[x][y] + map[x - 1][y] < dist[x - 1][y]) {
                dist[x - 1][y] = dist[x][y] + map[x - 1][y];
                quPush(x - 1, y);
            }
            if (y != 0 && dist[x][y] + map[x][y - 1] < dist[x][y - 1]) {
                dist[x][y - 1] = dist[x][y] + map[x][y - 1];
                quPush(x, y - 1);
            }
            if (x != n - 1 && dist[x][y] + map[x + 1][y] < dist[x + 1][y]) {
                dist[x + 1][y] = dist[x][y] + map[x + 1][y];
                quPush(x + 1, y);
            }
            if (y != m - 1 && dist[x][y] + map[x][y + 1] < dist[x][y + 1]) {
                dist[x][y + 1] = dist[x][y] + map[x][y + 1];
                quPush(x, y + 1);
            }
        }
    }
    fprintf(stdout, "Result: %i\n", dist[n - 1][m - 1]);
}

