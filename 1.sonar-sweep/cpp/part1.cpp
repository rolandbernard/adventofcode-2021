
#include <bits/stdc++.h>

using namespace std;

int main() {
    int c = 0;
    int p;
    cin >> p;
    int d;
    while (cin >> d) {
        if (p < d) {
            c++;
        }
        p = d;
    }
    cout << "Count: " << c << endl;
}

