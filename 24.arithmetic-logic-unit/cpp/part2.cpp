
#include <bits/stdc++.h>

using namespace std;

enum InstrOp {
    INP, ADD, ADD_I, MUL, MUL_I, DIV, DIV_I, MOD, MOD_I, EQL, EQL_I
};

struct Instr {
    InstrOp opc;
    uint32_t arg1;
    int64_t arg2;
};

struct Program {
    size_t length;
    Instr instr[];
};

Program* readPrograms(FILE* file) {
    size_t maxp = 32;
    Program* prog = (Program*)malloc(sizeof(Program) + sizeof(Instr) * maxp);
    prog->length = 0;
    size_t size = 0;
    char* instr = NULL;
    while (getline(&instr, &size, file) > 0) {
        Instr i;
        if (strncasecmp(instr, "inp ", 4) == 0) {
            i.opc = INP;
        } else if (strncasecmp(instr, "add ", 4) == 0) {
            i.opc = ADD;
        } else if (strncasecmp(instr, "mul ", 4) == 0) {
            i.opc = MUL;
        } else if (strncasecmp(instr, "div ", 4) == 0) {
            i.opc = DIV;
        } else if (strncasecmp(instr, "mod ", 4) == 0) {
            i.opc = MOD;
        } else if (strncasecmp(instr, "eql ", 4) == 0) {
            i.opc = EQL;
        } else {
            continue;
        }
        size_t j = 4;
        while (isspace(instr[j])) {
            j++;
        }
        i.arg1 = instr[j] - 'w';
        if (i.opc != INP) {
            j++;
            while (isspace(instr[j])) {
                j++;
            }
            if (isalpha(instr[j])) {
                i.arg2 = instr[j] - 'w';
            } else {
                i.opc = (InstrOp)((int)i.opc + 1);
                bool neg = false;
                if (instr[j] == '-' || instr[j] == '+') {
                    neg = instr[j] == '-';
                    j++;
                }
                int64_t val = 0;
                while (isdigit(instr[j])) {
                    val *= 10;
                    val += instr[j] - '0';
                    j++;
                }
                i.arg2 = neg ? -val : val;
            }
        }
        if (prog->length == maxp) {
            maxp *= 2;
            prog = (Program*)realloc(prog, sizeof(Program) + sizeof(Instr) * maxp);
        }
        prog->instr[prog->length] = i;
        prog->length++;
    }
    free(instr);
    return prog;
}

struct AluState {
    size_t pc;
    int64_t regs[4];

    bool operator==(const AluState& o) const {
        return pc == o.pc
            && regs[0] == o.regs[0] && regs[1] == o.regs[1]
            && regs[2] == o.regs[2] && regs[3] == o.regs[3];
    }
};

template<>
struct std::hash<AluState> {
    size_t operator()(const AluState& s) const {
        size_t h = hash<size_t>()(s.pc);
        for (size_t i = 0; i < 4; i++) {
            h ^= hash<int64_t>()(s.regs[i]) << i;
        }
        return h;
    }
};

AluState runProgram(AluState state, const Program* prog, bool has_input, int64_t input) {
    for (; state.pc < prog->length; state.pc++) {
        Instr instr = prog->instr[state.pc];
        switch (instr.opc) {
            case INP:
                if (!has_input) {
                    return state;
                } else {
                    state.regs[instr.arg1] = input;
                    has_input = false;
                }
                break;
            case ADD:
                state.regs[instr.arg1] += state.regs[instr.arg2];
                break;
            case ADD_I:
                state.regs[instr.arg1] += instr.arg2;
                break;
            case MUL:
                state.regs[instr.arg1] *= state.regs[instr.arg2];
                break;
            case MUL_I:
                state.regs[instr.arg1] *= instr.arg2;
                break;
            case DIV:
                state.regs[instr.arg1] /= state.regs[instr.arg2];
                break;
            case DIV_I:
                state.regs[instr.arg1] /= instr.arg2;
                break;
            case MOD:
                state.regs[instr.arg1] %= state.regs[instr.arg2];
                break;
            case MOD_I:
                state.regs[instr.arg1] %= instr.arg2;
                break;
            case EQL:
                state.regs[instr.arg1] = state.regs[instr.arg1] == state.regs[instr.arg2] ? 1 : 0;
                break;
            case EQL_I:
                state.regs[instr.arg1] = state.regs[instr.arg1] == instr.arg2 ? 1 : 0;
                break;
        }
    }
    return state;
}

uint64_t minNumber(unordered_set<AluState>& invalid, AluState state, const Program* prog, uint64_t number) {
    if (state.pc >= prog->length) {
        if (state.regs[3] == 0) {
            return number;
        } else {
            return 0;
        }
    } else {
        if (invalid.find(state) == invalid.end()) {
            for (int64_t i = 1; i <= 9; i++) {
                size_t max = minNumber(invalid, runProgram(state, prog, true, i), prog, number * 10 + i);
                if (max != 0) {
                    return max;
                }
            }
            invalid.insert(state);
            return 0;
        } else {
            return 0;
        }
    }
}

int main() {
    Program* prog = readPrograms(stdin);
    AluState initial = {.pc = 0, .regs = {0, 0, 0, 0}};
    unordered_set<AluState> invalid;
    int64_t number = minNumber(invalid, initial, prog, 0);
    free(prog);
    cout << "Result: " << number << endl;
}

