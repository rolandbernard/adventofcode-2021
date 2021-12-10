
#include <bits/stdc++.h>

using namespace std;

int main() {
    int count = 0;
    string sequence;
    while (cin >> sequence) {
        vector<char> stack;
        for (char c : sequence) {
            if (c == '(' || c == '[' || c == '{' || c == '<') {
                stack.push_back(c);
            } else {
                char exp = stack.back();
                stack.pop_back();
                if (
                    (exp == '(' && c != ')') || (exp == '[' && c != ']') || (exp == '{' && c != '}')
                    || (exp == '<' && c != '>')
                ) {
                    if (c == ')') {
                        count += 3;
                    } else if (c == ']') {
                        count += 57;
                    } else if (c == '}') {
                        count += 1197;
                    } else {
                        count += 25137;
                    }
                    break;
                }
            }
        }
    }
    cout << "Result: " << count << endl;
    return 0;
}

