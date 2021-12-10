
#include "Vsolver.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    Vsolver solver;
    solver.enable = 1;
    solver.directrion = 0b11;
    solver.clk = 0;
    solver.eval();
    solver.clk = 1;
    solver.eval();
    string dir;
    int value;
    while (cin >> dir && cin >> value) {
        solver.clk = 0;
        solver.eval();
        solver.directrion = dir[0] == 'f' ? 0 : dir[0] == 'u' ? 1 : 2;
        solver.value = value;
        solver.clk = 1;
        solver.eval();
    }
    solver.enable = 0;
    solver.eval();
    cout << "Solution: " << solver.solution << endl;
}

