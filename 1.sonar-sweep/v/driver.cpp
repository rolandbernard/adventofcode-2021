
#include "Vsolver.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    Vsolver solver;
    solver.enable = 1;
    solver.reset = 1;
    solver.clk = 0;
    solver.eval();
    solver.clk = 1;
    solver.eval();
    solver.reset = 0;
    int value;
    while (cin >> value) {
        solver.clk = 0;
        solver.eval();
        solver.value = value;
        solver.clk = 1;
        solver.eval();
    }
    solver.enable = 0;
    solver.eval();
    cout << "Solution: " << solver.solution << endl;
}

