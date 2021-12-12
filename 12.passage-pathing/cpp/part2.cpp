
#include <bits/stdc++.h>

using namespace std;

struct Map {
    unordered_map<string, int> mapping;
    vector<bool> is_small;
    vector<vector<int>> connections;
};

size_t countPaths(Map& map, vector<int>& visited, bool allow, int at, int start, int end) {
    if (at == end) {
        return 1;
    } else if ((at == 0 || !allow) && map.is_small[at] && visited[at] > 0) {
        return 0;
    } else {
        size_t ret = 0;
        visited[at]++;
        for (int con : map.connections[at]) {
            ret += countPaths(map, visited, allow && (!map.is_small[at] || visited[at] <= 1), con, start, end);
        }
        visited[at]--;
        return ret;
    }
}

int getMapping(Map& map, string name) {
    if (map.mapping.find(name) == map.mapping.end()) {
        map.mapping[name] = map.mapping.size();
        map.is_small.push_back(islower(name[0]));
        map.connections.push_back(vector<int>());
    }
    return map.mapping[name];
}

int main() {
    Map map;
    int start = getMapping(map, "start");
    int end = getMapping(map, "end");
    string line;
    while (cin >> line) {
        size_t split = line.find("-");
        int from = getMapping(map, line.substr(0, split));
        int to = getMapping(map, line.substr(split + 1));
        map.connections[from].push_back(to);
        map.connections[to].push_back(from);
    }
    vector<int> visited(map.mapping.size());
    size_t res = countPaths(map, visited, true, start, start, end);
    cout << "Result: " << res << endl;
    return 0;
}

