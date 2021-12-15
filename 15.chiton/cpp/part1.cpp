
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
    vector<vector<int>> dists(map.size(), vector<int>(map[0].size(), INT_MAX));
    auto comp = [&dists](pair<int, int> a, pair<int, int> b) {
        return dists[a.first][a.second] > dists[b.first][b.second];
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> queue(comp);
    dists[0][0] = 0;
    queue.push(make_pair(0, 0));
    while (!queue.empty()) {
        pair<int, int> p = queue.top();
        queue.pop();
        int x = p.first, y = p.second;
        if ((size_t)x == map.size() - 1 && (size_t)y == map[x].size() - 1) {
            break;
        } else {
            if (x != 0 && dists[x][y] + map[x - 1][y] < dists[x - 1][y]) {
                dists[x - 1][y] = dists[x][y] + map[x - 1][y];
                queue.push((make_pair(x - 1, y)));
            }
            if (y != 0 && dists[x][y] + map[x][y - 1] < dists[x][y - 1]) {
                dists[x][y - 1] = dists[x][y] + map[x][y - 1];
                queue.push((make_pair(x, y - 1)));
            }
            if ((size_t)x != map.size() - 1 && dists[x][y] + map[x + 1][y] < dists[x + 1][y]) {
                dists[x + 1][y] = dists[x][y] + map[x + 1][y];
                queue.push((make_pair(x + 1, y)));
            }
            if ((size_t)y != map[0].size() - 1 && dists[x][y] + map[x][y + 1] < dists[x][y + 1]) {
                dists[x][y + 1] = dists[x][y] + map[x][y + 1];
                queue.push((make_pair(x, y + 1)));
            }
        }
    }
    cout << "Result: " << dists.back().back() << endl;
    return 0;
}
