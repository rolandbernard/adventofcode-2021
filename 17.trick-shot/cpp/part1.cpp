
#include <bits/stdc++.h>

using namespace std;

int main() {
    int minx, maxx, miny, maxy;
    fscanf(stdin, "target area: x=%i..%i, y=%i..%i", &minx, &maxx, &miny, &maxy);
    int sy = max(-miny - 1, maxy);
    cout << "Result: " << sy * (sy + 1) / 2 << endl;
}

