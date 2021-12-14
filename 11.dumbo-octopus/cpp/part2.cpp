
#include <bits/stdc++.h>

using namespace std;

void incrementEnergy(vector<vector<int>>& map, vector<vector<bool>>& flashed, size_t i, size_t j) {
    if (i >= 0 && j >= 0 && i < map.size() && j < map[0].size() && !flashed[i][j]) {
        map[i][j]++;
        if (map[i][j] > 9) {
            flashed[i][j] = true;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di != 0 || dj != 0) {
                        incrementEnergy(map, flashed, i + di, j + dj);
                    }
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> map;
    string line;
    while (cin >> line) {
        vector<int> map_line;
        for (char c : line) {
            map_line.push_back(c - '0');
        }
        map.push_back(map_line);
    }
    long res = 0;
    for (int s = 0; res == 0; s++) {
        vector<vector<bool>> flash(map.size(), vector<bool>(map[0].size()));
        for (size_t i = 0; i < map.size(); i++) {
            for (size_t j = 0; j < map[i].size(); j++) {
                incrementEnergy(map, flash, i, j);
            }
        }
        size_t count = 0;
        for (size_t i = 0; i < map.size(); i++) {
            for (size_t j = 0; j < map[i].size(); j++) {
                if (flash[i][j]) {
                    map[i][j] = 0;
                    count++;
                }
            }
        }
        if (count == map.size() * map[0].size()) {
            res = s + 1;
        }
    }
    cout << "Result: " << res << endl;
    return 0;
}

