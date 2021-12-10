
#include <bits/stdc++.h>

using namespace std;

int main() {
    int count = 0;
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
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (
                (i == 0 || map[i - 1][j] > map[i][j])
                && (i == map.size() - 1 || map[i + 1][j] > map[i][j])
                && (j == 0 || map[i][j - 1] > map[i][j])
                && (j == map[i].size() - 1 || map[i][j + 1] > map[i][j])
            ) {
                res += 1 + map[i][j];
            }
        }
    }
    cout << "Result: " << res << endl;
    return 0;
}

