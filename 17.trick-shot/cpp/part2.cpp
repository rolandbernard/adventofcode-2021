
#include <bits/stdc++.h>

using namespace std;

int main() {
    int minx, maxx, miny, maxy;
    fscanf(stdin, "target area: x=%i..%i, y=%i..%i", &minx, &maxx, &miny, &maxy);
    int count = 0;
    for (int dy = min(0, miny); dy <= max(-miny - 1, maxy); dy++) {
        for (int dx = min(0, minx); dx <= max(0, maxx); dx++) {
            int x = 0, y = 0;
            int ddx = dx, ddy = dy;
            while (y >= miny) {
                if (x >= minx && x <= maxx && y >= miny && y <= maxy) {
                    count++;
                    break;
                }
                x += ddx; y += ddy;
                ddx = max(0, ddx - 1); ddy--;
            }
        }
    }
    cout << "Result: " << count << endl;
}

