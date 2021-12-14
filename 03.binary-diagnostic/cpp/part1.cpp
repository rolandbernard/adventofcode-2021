
#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main() {
    size_t n = 0;
    vector<size_t> bits;
    string number;
    while (cin >> number) {
        if (bits.size() < number.size()) {
            bits.resize(number.size());
        }
        for (size_t i = 0; i < number.size(); i++) {
            if (number[i] == '1') {
                bits[number.size() - 1 - i]++;
            }
        }
        n++;
    }
    int first = 0;
    for (size_t i = 0; i < bits.size(); i++) {
        first |= (bits[i] >= n/2 ? 1 : 0) << i;
    }
    int second = ~first & ((1 << bits.size()) - 1);
    cout << "Parts: " << first << " " << second << endl;
    cout << "Result: " << (first * second) << endl;
}

