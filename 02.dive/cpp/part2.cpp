
#include <bits/stdc++.h>

using namespace std;

int main() {
    int a = 0;
    int x = 0;
    int y = 0;
    string dir;
    int amount;
    while (cin >> dir && cin >> amount) {
        if (dir[0] == 'f') {
            x += amount;
            y += a * amount;
        } else if (dir[0] == 'd') {
            a += amount;
        } else if (dir[0] == 'u') {
            a -= amount;
        }
    }
    cout << "Location: " << x << " " << y << endl;
    cout << "Result: " << (x * y) << endl;
}

