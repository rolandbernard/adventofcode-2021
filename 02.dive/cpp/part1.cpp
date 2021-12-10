
#include <bits/stdc++.h>

using namespace std;

int main() {
    int x = 0;
    int y = 0;
    string dir;
    int amount;
    while (cin >> dir && cin >> amount) {
        if (dir[0] == 'f') {
            x += amount;
        } else if (dir[0] == 'd') {
            y += amount;
        } else if (dir[0] == 'u') {
            y -= amount;
        }
    }
    cout << "Location: " << x << " " << y << endl;
    cout << "Result: " << (x * y) << endl;
}

