
#include <bits/stdc++.h>

using namespace std;

long forLocation(vector<long>& locs, long avg) {
    return accumulate(locs.begin(), locs.end(), 0, [=](long acc, long el) {
        long n = abs(avg - el);
        return acc + (n + 1) * n / 2;
    });
}

int main() {
    vector<long> positions;
    long pos;
    while (cin >> pos) {
        char ign;
        cin >> ign;
        positions.push_back(pos);
    }
    long sum = accumulate(positions.begin(), positions.end(), 0);
    long avg_low = sum / positions.size();
    long result = min(
        forLocation(positions, avg_low),
        forLocation(positions, avg_low + 1)
    );
    cout << "Result: " << result << endl;
    return 0;
}

