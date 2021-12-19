
#include <bits/stdc++.h>

using namespace std;

struct Vec3 {
    union {
        int d[3];
        struct {
            int x, y, z;
        };
    };

    Vec3() : x(0), y(0), z(0) { }

    Vec3(int x, int y, int z) : x(x), y(y), z(z) { }

    Vec3 operator+(Vec3 o) {
        return Vec3(x + o.x, y + o.y, z + o.z);
    }

    Vec3 operator-(Vec3 o) {
        return Vec3(x - o.x, y - o.y, z - o.z);
    }

    bool operator<(Vec3 o) {
        if (x != o.x) {
            return x < o.x;
        } else if (y != o.y) {
            return y < o.y;
        } else {
            return z < o.z;
        }
    }

    bool operator==(Vec3 o) {
        return x == o.x && y == o.y && z == o.z;
    }

    bool operator!=(Vec3 o) {
        return !(*this == o);
    }

    Vec3 abs() {
        return Vec3(std::abs(x), std::abs(y), std::abs(z));
    }

    Vec3 sorted() {
        int sorted[3] = {x, y, z};
        sort(sorted, sorted + 3);
        return Vec3(sorted[0], sorted[1], sorted[2]);
    }
};

struct Mat3x3 {
    int d[3][3];

    Vec3 operator*(Vec3 v) {
        Vec3 r = Vec3();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                r.d[i] += d[i][j] * v.d[j];
            }
        }
        return r;
    }
};

Mat3x3 matrixForSimpleRotation(Vec3 from, Vec3 to) {
    Mat3x3 r = Mat3x3();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (abs(from.d[j]) == abs(to.d[i])) {
                r.d[i][j] = from.d[j] == to.d[i] ? 1 : -1;
            }
        }
    }
    return r;
}

struct Scanner {
    vector<Vec3> points;
    vector<vector<pair<Vec3, size_t>>> distances;

    void computeDistances() {
        distances.resize(points.size());
        for (size_t i = 0; i < points.size(); i++) {
            for (size_t j = i; j < points.size(); j++) {
                Vec3 dist = (points[i] - points[j]).abs().sorted();
                distances[i].push_back(make_pair(dist, j));
                if (i != j) {
                    distances[j].push_back(make_pair(dist, i));
                }
            }
            sort(distances[i].begin(), distances[i].end(), [](auto& a, auto& b) {
                return a.first < b.first;
            });
        }
    }
};

vector<vector<pair<size_t, size_t>>> computeMapping(Scanner from, Scanner to) {
    vector<vector<pair<size_t, size_t>>> mappings;
    for (size_t i = 0; i < from.points.size(); i++) {
        for (size_t j = 0; j < to.points.size(); j++) {
            vector<pair<size_t, size_t>> mapping;
            size_t l = 0, k = 0;
            while (l < from.distances[i].size() && k < to.distances[j].size()) {
                if (from.distances[i][l].first == to.distances[j][k].first) {
                    mapping.push_back(make_pair(from.distances[i][l].second, to.distances[j][k].second));
                    l++;
                    k++;
                } else if (from.distances[i][l].first < to.distances[j][k].first) {
                    l++;
                } else {
                    k++;
                }
            }
            if (mapping.size() >= 12) {
                mappings.push_back(mapping);
            }
        }
    }
    return mappings;
}

bool tryMatchingPoints(Scanner& base, Scanner& add) {
    auto maps = computeMapping(base, add);
    for (auto map : maps) {
        Vec3 from = add.points[map[1].second] - add.points[map[0].second];
        Vec3 to = base.points[map[1].first] - base.points[map[0].first];
        vector<Vec3> trans = add.points;
        Mat3x3 rot = matrixForSimpleRotation(from, to);
        for (Vec3& p : trans) {
            p = rot * p;
        }
        Vec3 off = base.points[map[0].first] - trans[map[0].second];
        for (Vec3& p : trans) {
            p = p + off;
        }
        int matches = 0;
        for (auto m : map) {
            if (base.points[m.first] == trans[m.second]) {
                matches++;
            }
        }
        if (matches >= 12) {
            add.points = trans;
            return true;
        }
    }
    return false;
}

int main() {
    vector<Scanner> scanners;
    string header;
    while (getline(cin, header)) {
        scanners.push_back(Scanner());
        int x, y, z;
        char ign;
        while (cin >> x) {
            cin >> ign >> y >> ign >> z;
            scanners.back().points.push_back(Vec3(x, y, z));
        }
        scanners.back().computeDistances();
        cin.clear();
    }
    vector<size_t> created;
    unordered_set<size_t> missing;
    created.push_back(0);
    for (size_t i = 1; i < scanners.size(); i++) {
        missing.insert(i);
    }
    for (size_t i = 0; i < created.size(); i++) {
        unordered_set<size_t> new_missing = missing;
        for (size_t j : missing) {
            if (tryMatchingPoints(scanners[created[i]], scanners[j])) {
                new_missing.erase(j);
                created.push_back(j);
            }
        }
        missing = new_missing;
    }
    vector<Vec3> points;
    for (Scanner s : scanners) {
        for (Vec3 p : s.points) {
            points.push_back(p);
        }
    }
    sort(points.begin(), points.end());
    auto end = unique(points.begin(), points.end());
    points.resize(end - points.begin());
    cout << "Result: " << points.size() << endl;
}

