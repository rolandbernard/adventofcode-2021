
#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<long> line_scores;
    string sequence;
    while (cin >> sequence) {
        vector<char> stack;
        bool error = false;
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
                    error = true;
                    break;
                }
            }
        }
        if (!error) {
            long score = 0;
            while (!stack.empty()) {
                score *= 5;
                char exp = stack.back();
                stack.pop_back();
                if (exp == '(') {
                    score += 1;
                } else if (exp == '[') {
                    score += 2;
                } else if (exp == '{') {
                    score += 3;
                } else {
                    score += 4;
                }
            }
            line_scores.push_back(score);
        }
    }
    nth_element(line_scores.begin(), line_scores.begin() + line_scores.size() / 2, line_scores.end());
    cout << "Result: " << line_scores[line_scores.size() / 2] << endl;
    return 0;
}

