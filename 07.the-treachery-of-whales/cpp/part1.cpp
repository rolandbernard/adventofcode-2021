
#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<long> positions;
    long pos;
    while (cin >> pos) {
        char ign;
        cin >> ign;
        positions.push_back(pos);
    }
    nth_element(positions.begin(), positions.begin() + positions.size() / 2, positions.end());
    long median = positions[positions.size() / 2];
    long result = accumulate(positions.begin(), positions.end(), 0, [=](long acc, long el) {
        return acc + abs(median - el);
    });
    cout << "Result: " << result << endl;
    return 0;
}

