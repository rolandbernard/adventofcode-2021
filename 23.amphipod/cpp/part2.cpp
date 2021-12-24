
#include <bits/stdc++.h>

using namespace std;

#define LENGTH 11
#define TYPES 4
#define DEPTH 4

static const int costs[] = {1, 10, 100, 1000};
static const int8_t rooms[] = {2, 4, 6, 8};

struct GameState {
    int heur;
    int dist;
    array<int8_t, 2> loc[TYPES][DEPTH];

    void norm() {
        for (int i = 0; i < TYPES; i++) {
            sort(loc[i], loc[i] + DEPTH);
        }
    }

    bool operator==(const GameState& o) const {
        for (int i = 0; i < TYPES; i++) {
            for (int j = 0; j < DEPTH; j++) {
                if (loc[i][j][0] != o.loc[i][j][0] || loc[i][j][1] != o.loc[i][j][1]) {
                    return false;
                }
            }
        }
        return true;
    }
};

template<>
struct std::hash<GameState> {
    size_t operator()(const GameState& s) const {
        size_t h = 91;
        for (int i = 0; i < TYPES; i++) {
            for (int j = 0; j < DEPTH; j++) {
                h ^= hash<int>()((s.loc[i][j][0] << i) + j);
                h ^= hash<int>()((s.loc[i][j][1] << i) + j + DEPTH);
            }
        }
        return hash<size_t>()(h);
    }
};

bool finished(const GameState& s) {
    for (int i = 0; i < TYPES; i++) {
        for (int j = 0; j < DEPTH; j++) {
            if (s.loc[i][j][1] == 0 || s.loc[i][j][0] != rooms[i]) {
                return false;
            }
        }
    }
    return true;
}

int heuristic(const GameState& s) {
    int h = 0;
    for (int i = 0; i < TYPES; i++) {
        for (int j = 0; j < DEPTH; j++) {
            h += costs[i] * (
                abs(s.loc[i][j][0] - rooms[i])
                + (s.loc[i][j][0] != rooms[i]
                    ? s.loc[i][j][1] + j : j - s.loc[i][j][1])
            );
        }
    }
    return h;
}

bool canMove(const GameState& s, const array<int8_t, 2>& from, const array<int8_t, 2>& to) {
    if (to[1] == 0) {
        for (int i = 0; i < TYPES; i++) {
            if (to[0] == rooms[i]) {
                return false;
            }
        }
        bool mov = false;
        for (int i = 0; !mov && i < TYPES; i++) {
            for (int j = 0; !mov && j < DEPTH; j++) {
                if (s.loc[i][j][0] == from[0] && s.loc[i][j][0] != rooms[i]) {
                    mov = true;
                }
            }
        }
        if (!mov) {
            return false;
        }
    }
    for (int i = 0; i < TYPES; i++) {
        for (int j = 0; j < DEPTH; j++) {
            const array<int8_t, 2> &x = s.loc[i][j];
            if (x[0] != from[0] || x[1] != from[1]) {
                if (x[1] == 0 && x[0] > min(to[0], from[0]) && x[0] < max(to[0], from[0])) {
                    return false;
                } else if (x[0] == from[0] && x[1] <= from[1]) {
                    return false;
                } else if (x[0] == to[0] && x[1] <= to[1]) {
                    return false;
                } else if (to[1] != 0 && x[0] == to[0] && x[0] != rooms[i]) {
                    return false;
                }
            }
        }
    }
    return true;
}

GameState readInput() {
    GameState state;
    int is[TYPES] = { 0 };
    char c;
    int i = 0;
    while (cin >> c) {
        if (c >= 'A' && c <= 'D') {
            state.loc[c - 'A'][is[c - 'A']][0] = rooms[i % TYPES];
            state.loc[c - 'A'][is[c - 'A']][1] = 1 + 3 * (i / TYPES);
            is[c - 'A']++; i++;
        }
    }
    char f[] = {'D', 'C', 'B', 'A', 'D', 'B', 'A', 'C'};
    for (char c : f) {
        state.loc[c - 'A'][is[c - 'A']][0] = rooms[i % TYPES];
        state.loc[c - 'A'][is[c - 'A']][1] = i / TYPES;
        is[c - 'A']++; i++;
    }
    state.norm();
    state.dist = 0;
    state.heur = heuristic(state);
    return state;
}

int getBestCost(GameState& initial) {
    auto cmp = [](const GameState& a, const GameState& b) {
        return a.heur > b.heur;
    };
    unordered_map<GameState, int> cost;
    priority_queue<GameState, vector<GameState>, decltype(cmp)> queue(cmp);
    auto try_adding = [&queue, &cost](const GameState& s, int i, int j, const array<int8_t, 2>& to) {
        if (canMove(s, s.loc[i][j], to)) {
            GameState next = s;
            next.loc[i][j] = to;
            next.norm();
            next.dist += costs[i] * (
                abs(to[0] - s.loc[i][j][0]) + abs(to[1] - s.loc[i][j][1])
            );
            if (cost[next] == 0 || cost[next] > next.dist) {
                next.heur = next.dist + heuristic(next);
                cost[next] = next.dist;
                queue.push(next);
            }
            return true;
        } else {
            return false;
        }
    };
    queue.push(initial);
    while (!queue.empty()) {
        GameState top = queue.top();
        queue.pop();
        if (finished(top)) {
            return top.dist;
        } else if (cost[top] == top.dist) {
            for (int i = 0; i < TYPES; i++) {
                for (int j = 0; j < DEPTH; j++) {
                    if (top.loc[i][j][1] == 0) {
                        for (int h = DEPTH; h >= 1; h--) {
                            array<int8_t, 2> to;
                            to[0] = rooms[i]; to[1] = h;
                            if (try_adding(top, i, j, to)) {
                                break;
                            }
                        }
                    } else {
                        for (int h = 0; h < LENGTH; h++) {
                            array<int8_t, 2> to;
                            to[0] = h; to[1] = 0;
                            try_adding(top, i, j, to);
                        }
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    GameState initial = readInput();
    int cost = getBestCost(initial);
    cerr << "Result: " << cost << endl;
}

