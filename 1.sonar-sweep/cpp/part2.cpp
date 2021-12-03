
#include <bits/stdc++.h>

using namespace std;

int main() {
    int m[3];
    int i = 0;
    int c = 0;
    cin >> m[0];
    cin >> m[1];
    cin >> m[2];
    int n;
    while (cin >> n) {
        if (m[i] < n) {
            c++;
        }
        m[i] = n;
        i = (i + 1) % 3;
    }
    cout << "Count: " << c << endl;
}

