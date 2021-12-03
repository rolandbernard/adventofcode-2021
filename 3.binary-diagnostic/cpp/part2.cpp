
#include <bits/stdc++.h>
#include <cstddef>

using namespace std;

int findLast(vector<string>& v, bool common) {
    auto pos = v.begin();
    size_t size = v.size();
    int i = 0;
    while (size > 1) {
        auto center = upper_bound(pos, pos + size, *pos, [=](const string& a, const string& b) {
            return b[i] != (common ? '0' : '1');
        });
        size_t first = (center - pos);
        if (common ? first > size - first : first < size - first) {
            size = center - pos;
        } else {
            size -= center - pos;
            pos = center;
        }
        i++;
    }
    return stoi(*pos, 0, 2);
}

int main() {
    vector<string> numbers;
    string number;
    while (cin >> number) {
        numbers.push_back(number);
    }
    sort(numbers.begin(), numbers.end());
    int first = findLast(numbers, true);
    sort(numbers.begin(), numbers.end(), [](auto a, auto b) { return a > b; });
    int second = findLast(numbers, false);
    cout << "Parts: " << first << " " << second << endl;
    cout << "Result: " << (first * second) << endl;
}

