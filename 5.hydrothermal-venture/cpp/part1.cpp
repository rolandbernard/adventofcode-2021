
#include <bits/stdc++.h>

using namespace std;

struct Line {
    int x1, y1;
    int x2, y2;
};

int main() {
    vector<Line> lines;
    int x;
    while (cin >> x) {
        char ign;
        Line l;
        l.x1 = x;
        cin >> ign >> l.y1;
        do {
            cin >> ign;
        } while (ign != '>');
        cin >> l.x2 >> ign >> l.y2;
        lines.push_back(l);
    }
    int minx = INT_MAX;
    int miny = INT_MAX;
    int maxx = INT_MIN;
    int maxy = INT_MIN;
    for (Line l : lines) {
        maxx = max(maxx, max(l.x1, l.x2));
        maxy = max(maxy, max(l.y1, l.y2));
        minx = min(minx, min(l.x1, l.x2));
        miny = min(miny, min(l.y1, l.y2));
    }
    int width = maxx + 1 - minx;
    int height = maxy + 1 - miny;
    vector<vector<int>> map(width, vector<int>(height));
    for (Line l : lines) {
        if (l.x1 == l.x2) {
            for (int y = min(l.y1, l.y2); y <= max(l.y1, l.y2); y++) {
                map[l.x1 - minx][y - miny]++;
            }
        } else if (l.y1 == l.y2) {
            for (int x = min(l.x1, l.x2); x <= max(l.x1, l.x2); x++) {
                map[x - minx][l.y1 - miny]++;
            }
        }
    }
    int danger = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[x][y] >= 2) {
                danger++;
            }
        }
    }
    cout << "Result: " << danger << endl;
    return 0;
}

