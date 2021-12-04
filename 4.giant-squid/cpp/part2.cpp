
#include <bits/stdc++.h>

using namespace std;

struct Board {
    int values[5][5];
    unordered_multiset<int> uncalled;
};

struct Row {
    Board* board;
    int found;
};

#define cin file

ifstream file("input.txt");

bool readBoard(Board** b) {
    *b = new Board;
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            if (cin >> (*b)->values[i][j]) {
                (*b)->uncalled.insert((*b)->values[i][j]);
            } else {
                return false;
            }
        }
    }
    return true;
}

int main() {
    vector<int> values;
    string value_line;
    getline(cin, value_line);
    stringstream value_steam(value_line);
    int value;
    while (value_steam >> value) {
        char ign;
        value_steam >> ign;
        values.push_back(value);
    }
    unordered_set<Board*> boards;
    Board* board;
    while (readBoard(&board)) {
        boards.insert(board);
    }
    unordered_map<int, vector<Row*>> rows;
    for (Board* b : boards) {
        for (size_t i = 0; i < 5; i++) {
            Row* row = new Row;
            row->board = b;
            row->found = 0;
            for (size_t j = 0; j < 5; j++) {
                rows[b->values[i][j]].push_back(row);
            }
        }
        for (size_t j = 0; j < 5; j++) {
            Row* row = new Row;
            row->board = b;
            row->found = 0;
            for (size_t i = 0; i < 5; i++) {
                rows[b->values[i][j]].push_back(row);
            }
        }
    }
    int first = 0;
    int second = 0;
    for (int v : values) {
        for (Row* r : rows[v]) {
            r->found++;
            r->board->uncalled.erase(v);
            if (r->found == 5 || boards.find(r->board) == boards.end()) {
                if (boards.size() == 1 && boards.find(r->board) != boards.end()) {
                    for (int w : r->board->uncalled) {
                        first += w;
                    }
                    second = v;
                    cout << "Parts: " << first << " " << second << endl;
                    cout << "Result: " << (first * second) << endl;
                    return 0;
                } else {
                    boards.erase(r->board);
                }
            }
        }
        rows.erase(v);
    }
    return 0;
}

