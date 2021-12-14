
#include <bits/stdc++.h>

using namespace std;

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
    int basin_size[3] = { 0, 0, 0 };
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            if (
                (i == 0 || map[i - 1][j] > map[i][j])
                && (i == map.size() - 1 || map[i + 1][j] > map[i][j])
                && (j == 0 || map[i][j - 1] > map[i][j])
                && (j == map[i].size() - 1 || map[i][j + 1] > map[i][j])
            ) {
                int size = 0;
                queue<pair<size_t, size_t>> to_analyze;
                to_analyze.push(make_pair(i, j));
                while (!to_analyze.empty()) {
                    pair<size_t, size_t> p = to_analyze.front();
                    to_analyze.pop();
                    if (map[p.first][p.second] != 9) {
                        size++;
                        if (p.first != 0 && map[p.first - 1][p.second] > map[p.first][p.second]) {
                            to_analyze.push(make_pair(p.first - 1, p.second));
                        }
                        if (p.first != map.size() - 1 && map[p.first + 1][p.second] > map[p.first][p.second]) {
                            to_analyze.push(make_pair(p.first + 1, p.second));
                        }
                        if (p.second != 0 && map[p.first][p.second - 1] > map[p.first][p.second]) {
                            to_analyze.push(make_pair(p.first, p.second - 1));
                        }
                        if (p.second != map[0].size() - 1 && map[p.first][p.second + 1] > map[p.first][p.second]) {
                            to_analyze.push(make_pair(p.first, p.second + 1));
                        }
                        map[p.first][p.second] = 9;
                    }
                }
                if (size > basin_size[0]) {
                    basin_size[2] = basin_size[1];
                    basin_size[1] = basin_size[0];
                    basin_size[0] = size;
                } else if (size > basin_size[1]) {
                    basin_size[2] = basin_size[1];
                    basin_size[1] = size;
                } else if (size > basin_size[2]) {
                    basin_size[2] = size;
                }
            }
        }
    }
    cout << "Result: " << basin_size[0] * basin_size[1] * basin_size[2] << endl;
    return 0;
}

