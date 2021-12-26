
#define CL_TARGET_OPENCL_VERSION 300
#include <CL/cl.h>

#include <bits/stdc++.h>

using namespace std;

#define DEPTH 5

size_t b9to10(size_t in) {
    size_t tmp = 0;
    for (int i = 0; i < 14; i++) {
        tmp *= 10;
        tmp += (in % 9) + 1;
        in /= 9;
    }
    in = tmp;
    tmp = 0;
    for (int i = 0; i < 14; i++) {
        tmp *= 10;
        tmp += in % 10;
        in /= 10;
    }
    return tmp;
}

size_t b10to9(size_t in) {
    size_t tmp = 0;
    for (int i = 0; i < 14 - DEPTH; i++) {
        tmp *= 9;
        tmp += (in % 10) - 1;
        in /= 10;
    }
    in = tmp;
    tmp = 0;
    for (int i = 0; i < 14 - DEPTH; i++) {
        tmp *= 9;
        tmp += in % 9;
        in /= 9;
    }
    return tmp;
}

int main() {
    stringstream source;
    source << "__kernel void runProgram(__global uint* result, ulong off) {" << endl;
    source << "size_t id = get_global_id(0); size_t tmp = id + off; size_t inp = 0;" << endl;
    source << "result[id + 1] = 0;" << endl;
    source << "for (int i = 0; i < " << (14 - DEPTH) << "; i++) { inp *= 9; inp += tmp % 9; tmp /= 9; }" << endl;
    source << "int w = 0, x = 0, y = 0, z = 0;" << endl;
    string opc, arg0, arg1;
    int i = 14;
    while (cin >> opc) {
        if (opc == "inp") {
            cin >> arg0;
            if (i <= DEPTH) {
                source << "int w" << i << " = w, x" << i << " = x, y" << i << " = y, z" << i << " = z;" << endl;
                source << "for (int i" << i << "= 1; i" << i << " <= 9; i" << i << "++) {" << endl;
                source << "w = w" << i << "; x = x" << i << "; y = y" << i << "; z = z" << i << ";" << endl;
                source << arg0 << " = i" << i << ";" << endl;
            } else {
                source << arg0 << " = (inp % 9) + 1; inp /= 9;" << endl;
            }
            i--;
        } else {
            cin >> arg0 >> arg1;
            if (opc == "add") {
                source << arg0 << " += " << arg1 << ";" << endl;
            } else if (opc == "mul") {
                source << arg0 << " *= " << arg1 << ";" << endl;
            } else if (opc == "div") {
                source << arg0 << " /= " << arg1 << ";" << endl;
            } else if (opc == "mod") {
                source << arg0 << " %= " << arg1 << ";" << endl;
            } else if (opc == "eql") {
                source << arg0 << " = (" << arg0 << " == " << arg1 << ") ? 1 : 0;" << endl;
            }
        }
    }
    source << "if (z == 0) {" << endl;
    source << "int res = 0;" << endl;
    for (int j = DEPTH; j > 0; j--) {
        source << "res *= 9;" << endl;
        source << "res += i" << j << " - 1;" << endl;
    }
    source << "result[id + 1] = res + 1;" << endl;
    source << "result[0] = true;" << endl;
    source << "}" << endl;
    for (int j = 1; j <= DEPTH; j++) {
        source << "}" << endl;
    }
    source << "}" << endl;
    string source_str = source.str();

    cl_int res;
    cl_uint platform_count;
    cl_platform_id platform_id;

    clGetPlatformIDs(1, &platform_id, &platform_count);

    cl_device_id device_id;
    cl_uint device_count;
    cl_command_queue_properties queue_prop;

    clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 1, &device_id, &device_count);
    clGetDeviceInfo(device_id, CL_DEVICE_QUEUE_PROPERTIES, sizeof(cl_command_queue_properties), &queue_prop, NULL);

    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &res);
    cl_command_queue queue = clCreateCommandQueueWithProperties(context, device_id, &queue_prop, &res);

    const char* source_c_str = source_str.c_str();
    const size_t source_size = source_str.size();
    cl_program program = clCreateProgramWithSource(context, 1, &source_c_str, &source_size, &res);

    clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    cl_kernel kernel = clCreateKernel(program, "runProgram", &res);

    size_t iter_size = 9*9*9*9*9*9;
    cl_uint* hbuffer = new cl_uint[iter_size + 1];
    cl_mem buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, (iter_size + 1) * sizeof(cl_uint), nullptr, &res);
    clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&buffer);

    size_t inner = 1;
    for (int i = 0; i < DEPTH; i++) {
        inner *= 9;
    }
    size_t min = ~0UL;
    for (size_t iter_offset = b10to9(99999999999999) + 1 - iter_size; min == ~0UL; iter_offset -= iter_size) {
        clock_t start = clock();
        cl_ulong off = iter_offset;
        clSetKernelArg(kernel, 1, sizeof(cl_ulong), (void*)&off);
        clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &iter_size, nullptr, 0, nullptr, nullptr);
        clEnqueueReadBuffer(queue, buffer, CL_TRUE, 0, sizeof(cl_int), hbuffer, 0, nullptr, nullptr);
        if (hbuffer[0]) {
            clEnqueueReadBuffer(queue, buffer, CL_TRUE, 0, (iter_size + 1) * sizeof(cl_uint), hbuffer, 0, nullptr, nullptr);
            for (size_t i = iter_size; i > 0; i--) {
                if (hbuffer[i]) {
                    min = (iter_offset + i - 1) * inner + hbuffer[i] - 1;
                    break;
                }
            }
        }
        clock_t end = clock();
        size_t ps = iter_size * inner * CLOCKS_PER_SEC / (end - start);
        size_t u = 0;
        while (ps > 10000) {
            u++;
            ps /= 1000;
        }
        cerr << "iter " << b9to10(iter_offset * inner) << " - ";
        cerr << ps << " " << "1kMGTPEZY"[u] << "/s" << endl;
    }
    
    cout << "Result: " << b9to10(min) << endl;
}

