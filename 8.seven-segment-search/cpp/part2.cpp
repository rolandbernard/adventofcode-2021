
#include <bits/stdc++.h>

using namespace std;

const int freq_map[] = {
    4, 0, 0, 6, 1, 3, 0, 0, 0, 0, 2, 5,
};

void analyzeFrequency(string sequences[10], int mapping[7]) {
    int freq[7];
    for (int i = 0; i < 7; i++) {
        freq[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        for (char c : sequences[i]) {
            freq[c - 'a'] += sequences[i].size() <= 4 ? 3 : 1;
        }
    }
    for (int i = 0; i < 7; i++) {
        mapping[i] = freq_map[freq[i] - 4];
    }
}

const string digi_map[] = {
    "abcefg", "cf", "acdeg", "acdfg", "bcdf", "abdfg", "abdefg", "acf", "abcdefg", "abcdfg",
};

int main() {
    int count = 0;
    for (;;) {
        string sequences[10];
        string sequence;
        for (int i = 0; i < 10; i++) {
            if (cin >> sequence) {
                sequences[i] = sequence;
            } else {
                cout << "Result: " << count << endl;
                return 0;
            }
        }
        char ign;
        do {
            cin >> ign;
        } while (ign != '|');
        int mapping[7];
        analyzeFrequency(sequences, mapping);
        int value = 0;
        for (int i = 0; i < 4; i++) {
            cin >> sequence;
            for (char& c : sequence) {
                c = mapping[c - 'a'] + 'a';
            }
            sort(sequence.begin(), sequence.end());
            value *= 10;
            value += find(digi_map, digi_map + 10, sequence) - digi_map;
        }
        count += value;
    };
    return 0;
}

