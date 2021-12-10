
#include <bits/stdc++.h>

using namespace std;

#define PERIOD 6
#define DELAY 2
#define DAYS PERIOD + DELAY + 1

#define LENGTH 80

int main() {
    int counts[DAYS];
    for (int i = 0; i < DAYS; i++) {
        counts[i] = 0;
    }
    int timer;
    while (cin >> timer) {
        char ign;
        cin >> ign;
        counts[timer]++;
    }
    for (int d = 0; d < LENGTH; d++) {
        int births = counts[0];
        for (int i = 1; i < DAYS; i++) {
            counts[i - 1] = counts[i];
        }
        counts[PERIOD] += births;
        counts[PERIOD + DELAY] = births;
    }
    int total = 0;
    for (int i = 0; i < DAYS; i++) {
        total += counts[i];
    }
    cout << "Result: " << total << endl;
    return 0;
}

