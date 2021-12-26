
#include <bits/stdc++.h>

#include <llvm-c/Core.h>
#include <llvm-c/Orc.h>
#include <llvm-c/LLJIT.h>
#include <llvm-c/Transforms/PassManagerBuilder.h>

using namespace std;

#define LENGTH 14

typedef array<int64_t, 5> AluState;

template<>
struct std::hash<AluState> {
    size_t operator()(const AluState& s) const {
        size_t h = 0;
        for (int64_t i : s) {
            h ^= hash<int64_t>()(i);
        }
        return h;
    }
};

typedef void (*ProgramPart)(int64_t* state, int64_t input);

struct Program {
    LLVMModuleRef llvm_module;
    LLVMOrcThreadSafeModuleRef orc_module;
    LLVMOrcLLJITRef orc_jit;
    ProgramPart parts[LENGTH];
};

static LLVMValueRef buildFunctionHead(const char* func_name, LLVMModuleRef module, LLVMValueRef regs[0], LLVMBuilderRef builder) {
    LLVMTypeRef func_args[] = { LLVMPointerType(LLVMInt64Type(), 0), LLVMInt64Type() };
    LLVMTypeRef func_type = LLVMFunctionType(LLVMVoidType(), func_args, 2, false);
    LLVMValueRef function = LLVMAddFunction(module, func_name, func_type);
    LLVMBasicBlockRef func_body = LLVMAppendBasicBlock(function, "");
    LLVMPositionBuilderAtEnd(builder, func_body);
    LLVMValueRef state = LLVMGetParam(function, 0);
    for (int i = 0; i < 4; i++) {
        LLVMValueRef idx = LLVMConstInt(LLVMInt64Type(), i, false);
        regs[i] = LLVMBuildLoad(builder, LLVMBuildGEP(builder, state, &idx, 1, ""), "");
    }
    return function;
}

static void buildFunctionTail(LLVMValueRef function, LLVMValueRef regs[0], LLVMBuilderRef builder) {
    LLVMValueRef state = LLVMGetParam(function, 0);
    for (int i = 0; i < 4; i++) {
        LLVMValueRef idx = LLVMConstInt(LLVMInt64Type(), i, false);
        LLVMBuildStore(builder, regs[i], LLVMBuildGEP(builder, state, &idx, 1, ""));
    }
    LLVMBuildRetVoid(builder);
}

static void compileFunctionsInto(Program& prog, istream& stream) {
    char func_name[] = "a_monad";
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMValueRef regs[4];
    LLVMValueRef function = buildFunctionHead(func_name, prog.llvm_module, regs, builder);
    bool input_used = false;
    string opc, arg0, arg1;
    while (stream >> opc) {
        stream >> arg0;
        int a0 = arg0[0] - 'w';
        if (opc == "inp") {
            if (input_used) {
                buildFunctionTail(function, regs, builder);
                func_name[0]++;
                function = buildFunctionHead(func_name, prog.llvm_module, regs, builder);
            }
            regs[a0] = LLVMGetParam(function, 1);
            input_used = true;
        } else {
            stream >> arg1;
            LLVMValueRef ar0 = regs[a0];
            LLVMValueRef ar1 = isalpha(arg1[0])
                ? regs[arg1[0] - 'w'] : LLVMConstIntOfString(LLVMInt64Type(), arg1.c_str(), 10);
            if (opc == "add") {
                regs[a0] = LLVMBuildAdd(builder, ar0, ar1, "");
            } else if (opc == "mul") {
                regs[a0] = LLVMBuildMul(builder, ar0, ar1, "");
            } else if (opc == "div") {
                regs[a0] = LLVMBuildSDiv(builder, ar0, ar1, "");
            } else if (opc == "mod") {
                regs[a0] = LLVMBuildSRem(builder, ar0, ar1, "");
            } else if (opc == "eql") {
                regs[a0] = LLVMBuildZExt(builder, LLVMBuildICmp(builder, LLVMIntEQ, ar0, ar1, ""), LLVMInt64Type(), "");
            }
        }
    }
    buildFunctionTail(function, regs, builder);
}

static void optimizeModule(Program& prog) {
    char* triple = LLVMGetDefaultTargetTriple();
    LLVMTargetRef target;
    LLVMGetTargetFromTriple(triple, &target, NULL);
    char* host_cpu = LLVMGetHostCPUName();
    char* host_features = LLVMGetHostCPUFeatures();
    LLVMTargetMachineRef machine = LLVMCreateTargetMachine(
        target, triple, host_cpu, host_features, LLVMCodeGenLevelAggressive, LLVMRelocPIC,
        LLVMCodeModelJITDefault
    );
    LLVMSetTarget(prog.llvm_module, triple);
    LLVMTargetDataRef data_layout = LLVMCreateTargetDataLayout(machine);
    LLVMSetModuleDataLayout(prog.llvm_module, data_layout);
    LLVMPassManagerRef pass_manager = LLVMCreatePassManager();
    LLVMPassManagerBuilderRef pass_manager_builder = LLVMPassManagerBuilderCreate();
    LLVMPassManagerBuilderSetOptLevel(pass_manager_builder, 3);
    LLVMPassManagerBuilderSetSizeLevel(pass_manager_builder, 2);
    LLVMPassManagerBuilderUseInlinerWithThreshold(pass_manager_builder, 500);
    LLVMAddAnalysisPasses(machine, pass_manager);
    LLVMPassManagerBuilderPopulateModulePassManager(pass_manager_builder, pass_manager);
    LLVMRunPassManager(pass_manager, prog.llvm_module);
    LLVMPassManagerBuilderDispose(pass_manager_builder);
    LLVMDisposePassManager(pass_manager);
    LLVMDisposeTargetData(data_layout);
    LLVMDisposeTargetMachine(machine);
    free(triple);
}

static void buildJit(Program& prog) {
    LLVMOrcLLJITBuilderRef jit_builder = LLVMOrcCreateLLJITBuilder();
    LLVMOrcCreateLLJIT(&prog.orc_jit, jit_builder);
    prog.orc_module = LLVMOrcCreateNewThreadSafeModule(prog.llvm_module, LLVMOrcCreateNewThreadSafeContext());
    LLVMOrcLLJITAddLLVMIRModule(prog.orc_jit, LLVMOrcLLJITGetMainJITDylib(prog.orc_jit), prog.orc_module);
    char func_name[] = "a_monad";
    for (int i = 0; i < LENGTH; i++, func_name[0]++) {
        LLVMOrcExecutorAddress addr;
        LLVMOrcLLJITLookup(prog.orc_jit, &addr, func_name);
        prog.parts[i] = (ProgramPart)(addr);
    }
}

Program compileProgram(istream& stream) {
    Program prog;
    prog.llvm_module = LLVMModuleCreateWithName("monad");
    compileFunctionsInto(prog, stream);
    optimizeModule(prog);
    buildJit(prog);
    return prog;
}

static inline AluState runProgram(const Program& program, AluState state, int64_t input) {
    program.parts[state[4]](state.data(), input);
    state[4]++;
    return state;
}

uint64_t minNumber(unordered_set<AluState>& invalid, AluState state, const Program& prog, uint64_t number) {
    if (state[4] >= LENGTH) {
        if (state[3] == 0) {
            return number;
        } else {
            return 0;
        }
    } else {
        if (invalid.find(state) == invalid.end()) {
            for (int64_t i = 1; i <= 9; i++) {
                size_t max = minNumber(invalid, runProgram(prog, state, i), prog, number * 10 + i);
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
    LLVMInitializeCore(LLVMGetGlobalPassRegistry());
    LLVMInitializeNativeAsmPrinter();
    LLVMInitializeNativeTarget();
    Program prog = compileProgram(cin);
    AluState initial{0, 0, 0, 0, 0};
    unordered_set<AluState> invalid;
    int64_t number = minNumber(invalid, initial, prog, 0);
    cout << "Result: " << number << endl;
    LLVMShutdown();
}

