
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
    vector<vector<int>> dists(map.size() * 5, vector<int>(map[0].size() * 5, INT_MAX));
    auto comp = [&dists](pair<int, int> a, pair<int, int> b) {
        return dists[a.first][a.second] > dists[b.first][b.second];
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> queue(comp);
    dists[0][0] = 0;
    queue.push(make_pair(0, 0));
    auto map_val = [&map](int x, int y) -> int {
        return (map[x % map.size()][y % map.size()] + (x / map.size() + y / (map.size())) - 1) % 9 + 1;
    };
    while (!queue.empty()) {
        pair<int, int> p = queue.top();
        queue.pop();
        int x = p.first, y = p.second;
        if ((size_t)x == dists.size() - 1 && (size_t)y == dists[x].size() - 1) {
            break;
        } else {
            if (x != 0 && dists[x][y] + map_val(x - 1, y) < dists[x - 1][y]) {
                dists[x - 1][y] = dists[x][y] + map_val(x - 1, y);
                queue.push((make_pair(x - 1, y)));
            }
            if (y != 0 && dists[x][y] + map_val(x, y - 1) < dists[x][y - 1]) {
                dists[x][y - 1] = dists[x][y] + map_val(x, y - 1);
                queue.push((make_pair(x, y - 1)));
            }
            if ((size_t)x != dists.size() - 1 && dists[x][y] + map_val(x + 1, y) < dists[x + 1][y]) {
                dists[x + 1][y] = dists[x][y] + map_val(x + 1, y);
                queue.push((make_pair(x + 1, y)));
            }
            if ((size_t)y != dists[0].size() - 1 && dists[x][y] + map_val(x, y + 1) < dists[x][y + 1]) {
                dists[x][y + 1] = dists[x][y] + map_val(x, y + 1);
                queue.push((make_pair(x, y + 1)));
            }
        }
    }
    cout << "Result: " << dists.back().back() << endl;
    return 0;
}
