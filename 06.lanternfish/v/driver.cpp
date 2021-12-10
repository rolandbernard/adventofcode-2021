
#include "Vsolver.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    Vsolver solver;
    solver.reset = 1;
    solver.clk = 0;
    solver.eval();
    solver.clk = 1;
    solver.eval();
    solver.reset = 0;
    solver.insert = 1;
    int value;
    while (cin >> value) {
        char ign;
        cin >> ign;
        solver.clk = 0;
        solver.eval();
        solver.value = value;
        solver.clk = 1;
        solver.eval();
    }
    solver.insert = 0;
    solver.advance = 1;
    for (int i = 0; i < 80; i++) {
        solver.clk = 0;
        solver.eval();
        solver.clk = 1;
        solver.eval();
    }
    cout << "Solution: " << solver.solution << endl;
    for (int i = 0; i < 256 - 80; i++) {
        solver.clk = 0;
        solver.eval();
        solver.clk = 1;
        solver.eval();
    }
    solver.advance = 0;
    solver.eval();
    cout << "Solution: " << solver.solution << endl;
}

