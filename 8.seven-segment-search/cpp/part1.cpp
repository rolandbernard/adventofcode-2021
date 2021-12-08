
#include <bits/stdc++.h>

using namespace std;

int main() {
    int count = 0;
    for (;;) {
        string sequence;
        for (int i = 0; i < 10; i++) {
            if (!(cin >> sequence)) {
                cout << "Result: " << count << endl;
                return 0;
            }
        }
        char ign;
        do {
            cin >> ign;
        } while (ign != '|');
        for (int i = 0; i < 4; i++) {
            cin >> sequence;
            if (
                sequence.size() == 2 || sequence.size() == 3 || sequence.size() == 4
                || sequence.size() == 7
            ) {
                count++;
            }
        }
    }
    return 0;
}

