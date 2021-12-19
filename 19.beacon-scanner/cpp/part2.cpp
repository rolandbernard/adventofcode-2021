
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

    Vec3 operator+(Vec3 o) const {
        return Vec3(x + o.x, y + o.y, z + o.z);
    }

    Vec3 operator-(Vec3 o) const {
        return Vec3(x - o.x, y - o.y, z - o.z);
    }

    bool operator<(Vec3 o) const {
        if (x != o.x) {
            return x < o.x;
        } else if (y != o.y) {
            return y < o.y;
        } else {
            return z < o.z;
        }
    }

    bool operator==(Vec3 o) const {
        return x == o.x && y == o.y && z == o.z;
    }

    Vec3 abs() const {
        return Vec3(std::abs(x), std::abs(y), std::abs(z));
    }

    int sum() const {
        return x + y + z;
    }
};

struct Mat3x3 {
    int d[3][3];

    Mat3x3() : d{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}} { }

    Mat3x3(int v[3][3]) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                d[i][j] = v[i][j];
            }
        }
    }

    Vec3 operator*(Vec3 v) const {
        Vec3 r = Vec3();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                r.d[i] += d[i][j] * v.d[j];
            }
        }
        return r;
    }

    Mat3x3 operator*(Mat3x3 m) const {
        Mat3x3 r = Mat3x3();
        for (int k = 0; k < 3; k++) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    r.d[i][k] += d[i][j] * m.d[j][k];
                }
            }
        }
        return r;
    }
};

Mat3x3 matrixForRotation(int x, int a) {
    static const int sin[5] = {0, 1, 0, -1, 0};
    switch (a) {
        case 0: {
            int arr[3][3] = {{1, 0, 0}, {0, sin[x + 1], -sin[x]}, {0, sin[x], sin[x + 1]}};
            return Mat3x3(arr);
        }
        case 1: {
            int arr[3][3] = {{sin[x + 1], 0, sin[x]}, {0, 1, 0}, {-sin[x], 0, sin[x + 1]}};
            return Mat3x3(arr);
        }
        case 2: {
            int arr[3][3] = {{sin[x + 1], -sin[x], 0}, {sin[x], sin[x + 1], 0}, {0, 0, 1}};
            return Mat3x3(arr);
        }
    }
    return matrixForRotation(0, 0);
}

vector<Mat3x3> possibleRotations() {
    vector<Mat3x3> result;
    result.reserve(24);
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            result.push_back(matrixForRotation(x, 0) * matrixForRotation(y, 1));
        }
    }
    for (int z = 1; z < 4; z += 2) {
        for (int x = 0; x < 4; x++) {
            result.push_back(matrixForRotation(x, 0) * matrixForRotation(z, 2));
        }
    }
    return result;
}

struct Scanner {
    Vec3 pos;
    vector<Vec3> points;
    vector<vector<int>> dists;

    void initialize() {
        dists.resize(points.size(), vector<int>(points.size()));
        for (size_t i = 0; i < points.size(); i++) {
            for (size_t j = i; j < points.size(); j++) {
                int dist = (points[i] - points[j]).abs().sum();
                dists[i][j] = dist;
                dists[j][i] = dist;
            }
            sort(dists[i].begin(), dists[i].end());
        }
    }
};

vector<pair<int, int>> possibleMappings(const Scanner& from, const Scanner& to) {
    vector<pair<int, int>> mappings;
    mappings.reserve(32);
    for (size_t i = 11; i < from.points.size(); i++) {
        for (size_t j = 0; j < to.points.size(); j++) {
            size_t match = 0, l = 0, k = 0;
            while (l < from.dists[i].size() && k < to.dists[j].size()) {
                if (from.dists[i][l] == to.dists[j][k]) {
                    match++; l++; k++;
                } else if (from.dists[i][l] < to.dists[j][k]) {
                    l++;
                } else {
                    k++;
                }
            }
            if (match >= 12) {
                mappings.push_back(make_pair(i, j));
            }
        }
    }
    return mappings;
}

size_t countIntersection(vector<Vec3> a, vector<Vec3> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    size_t match = 0;
    size_t k = 0;
    for (Vec3 p : a) {
        while (k < b.size() && b[k] < p) {
            k++;
        }
        if (k < b.size() && b[k] == p) {
            match++;
            k++;
        }
    }
    return match;
}

tuple<bool, Vec3, vector<Vec3>> computeMapping(const Scanner& from, const Scanner& to) {
    static const vector<Mat3x3> rotations = possibleRotations();
    vector<pair<int, int>> possible = possibleMappings(from, to);
    vector<Vec3> rotated(to.points.size());
    vector<Vec3> moved(to.points.size());
    for (Mat3x3 rot : rotations) {
        for (size_t i = 0; i < to.points.size(); i++) {
            rotated[i] = rot * to.points[i];
        }
        for (pair<int, int> p : possible) {
            Vec3 pos = from.points[p.first] - rotated[p.second];
            for (size_t i = 0; i < rotated.size(); i++) {
                moved[i] = rotated[i] + pos;
            }
            if (countIntersection(from.points, moved) >= 12) {
                return make_tuple(true, pos, moved);
            }
        }
    }
    return make_tuple(false, Vec3(), vector<Vec3>());
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
        scanners.back().initialize();
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
            tuple<bool, Vec3, vector<Vec3>> match = computeMapping(scanners[created[i]], scanners[j]);
            if (get<0>(match)) {
                scanners[j].points = get<2>(match);
                scanners[j].pos = get<1>(match);
                new_missing.erase(j);
                created.push_back(j);
            }
        }
        missing = new_missing;
    }
    int max = 0;
    for (Scanner x : scanners) {
        for (Scanner y : scanners) {
            int dist = (x.pos - y.pos).abs().sum();
            if (dist > max) {
                max = dist;
            }
        }
    }
    cout << "Result: " << max << endl;
}

