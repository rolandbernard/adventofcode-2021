
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

#define CASE_PRINT(X)                                                                              \
    case X: fprintf(stderr, #X); break;

void error(cl_int res, const char* err) {
    if (res != CL_SUCCESS) {
        fprintf(stderr, "%i from %s (", res, err);
        switch (res) {
            CASE_PRINT(CL_SUCCESS)
            CASE_PRINT(CL_DEVICE_NOT_FOUND)
            CASE_PRINT(CL_DEVICE_NOT_AVAILABLE)
            CASE_PRINT(CL_COMPILER_NOT_AVAILABLE)
            CASE_PRINT(CL_MEM_OBJECT_ALLOCATION_FAILURE)
            CASE_PRINT(CL_OUT_OF_RESOURCES)
            CASE_PRINT(CL_OUT_OF_HOST_MEMORY)
            CASE_PRINT(CL_PROFILING_INFO_NOT_AVAILABLE)
            CASE_PRINT(CL_MEM_COPY_OVERLAP)
            CASE_PRINT(CL_IMAGE_FORMAT_MISMATCH)
            CASE_PRINT(CL_IMAGE_FORMAT_NOT_SUPPORTED)
            CASE_PRINT(CL_BUILD_PROGRAM_FAILURE)
            CASE_PRINT(CL_MAP_FAILURE)
            CASE_PRINT(CL_MISALIGNED_SUB_BUFFER_OFFSET)
            CASE_PRINT(CL_COMPILE_PROGRAM_FAILURE)
            CASE_PRINT(CL_LINKER_NOT_AVAILABLE)
            CASE_PRINT(CL_LINK_PROGRAM_FAILURE)
            CASE_PRINT(CL_DEVICE_PARTITION_FAILED)
            CASE_PRINT(CL_KERNEL_ARG_INFO_NOT_AVAILABLE)
            CASE_PRINT(CL_INVALID_VALUE)
            CASE_PRINT(CL_INVALID_DEVICE_TYPE)
            CASE_PRINT(CL_INVALID_PLATFORM)
            CASE_PRINT(CL_INVALID_DEVICE)
            CASE_PRINT(CL_INVALID_CONTEXT)
            CASE_PRINT(CL_INVALID_QUEUE_PROPERTIES)
            CASE_PRINT(CL_INVALID_COMMAND_QUEUE)
            CASE_PRINT(CL_INVALID_HOST_PTR)
            CASE_PRINT(CL_INVALID_MEM_OBJECT)
            CASE_PRINT(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR)
            CASE_PRINT(CL_INVALID_IMAGE_SIZE)
            CASE_PRINT(CL_INVALID_SAMPLER)
            CASE_PRINT(CL_INVALID_BINARY)
            CASE_PRINT(CL_INVALID_BUILD_OPTIONS)
            CASE_PRINT(CL_INVALID_PROGRAM)
            CASE_PRINT(CL_INVALID_PROGRAM_EXECUTABLE)
            CASE_PRINT(CL_INVALID_KERNEL_NAME)
            CASE_PRINT(CL_INVALID_KERNEL_DEFINITION)
            CASE_PRINT(CL_INVALID_KERNEL)
            CASE_PRINT(CL_INVALID_ARG_INDEX)
            CASE_PRINT(CL_INVALID_ARG_VALUE)
            CASE_PRINT(CL_INVALID_ARG_SIZE)
            CASE_PRINT(CL_INVALID_KERNEL_ARGS)
            CASE_PRINT(CL_INVALID_WORK_DIMENSION)
            CASE_PRINT(CL_INVALID_WORK_GROUP_SIZE)
            CASE_PRINT(CL_INVALID_WORK_ITEM_SIZE)
            CASE_PRINT(CL_INVALID_GLOBAL_OFFSET)
            CASE_PRINT(CL_INVALID_EVENT_WAIT_LIST)
            CASE_PRINT(CL_INVALID_EVENT)
            CASE_PRINT(CL_INVALID_OPERATION)
            CASE_PRINT(CL_INVALID_GL_OBJECT)
            CASE_PRINT(CL_INVALID_BUFFER_SIZE)
            CASE_PRINT(CL_INVALID_MIP_LEVEL)
            CASE_PRINT(CL_INVALID_GLOBAL_WORK_SIZE)
            CASE_PRINT(CL_INVALID_PROPERTY)
            CASE_PRINT(CL_INVALID_IMAGE_DESCRIPTOR)
            CASE_PRINT(CL_INVALID_COMPILER_OPTIONS)
            CASE_PRINT(CL_INVALID_LINKER_OPTIONS)
            CASE_PRINT(CL_INVALID_DEVICE_PARTITION_COUNT)
        }
        fprintf(stderr, ")\n");
        exit(1);
    }
}

void errorp(void* pointer, cl_int* res, const char* err) {
    if (pointer == NULL) {
        error(*res, err);
    }
}

#define STRING(A) #A
#define STRINGIFY(A) STRING(A)
#define CHECK(F, AS) error(F AS, #F " at " STRINGIFY(__LINE__))
#define CHECKP(P, R, F, AS) errorp(P = F AS, &R, #F " at " STRINGIFY(__LINE__))

int main() {
    stringstream source;
    source << "__kernel void runProgram(__global uint* result, ulong off) {" << endl;
    source << "size_t id = get_global_id(0); size_t tmp = id + off; size_t inp = 0;" << endl;
    source << "result[id + 1] = 0;" << endl;
    source << "for (int i = 0; i < " << (14 - DEPTH)
           << "; i++) { inp *= 9; inp += tmp % 9; tmp /= 9; }" << endl;
    source << "int w = 0, x = 0, y = 0, z = 0;" << endl;
    string opc, arg0, arg1;
    int i = 14;
    while (cin >> opc) {
        if (opc == "inp") {
            cin >> arg0;
            if (i <= DEPTH) {
                source << "int w" << i << " = w, x" << i << " = x, y" << i << " = y, z" << i
                       << " = z;" << endl;
                source << "for (int i" << i << "= 1; i" << i << " <= 9; i" << i << "++) {" << endl;
                source << "w = w" << i << "; x = x" << i << "; y = y" << i << "; z = z" << i << ";"
                       << endl;
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

    CHECK(clGetPlatformIDs, (1, &platform_id, &platform_count));

    cl_device_id device_id;
    cl_uint device_count;
    cl_command_queue_properties queue_prop = 0;

    CHECK(clGetDeviceIDs, (platform_id, CL_DEVICE_TYPE_ALL, 1, &device_id, &device_count));

    cl_context context;
    CHECKP(context, res, clCreateContext, (NULL, 1, &device_id, NULL, NULL, &res));
    cl_command_queue queue;
    CHECKP(queue, res, clCreateCommandQueueWithProperties, (context, device_id, &queue_prop, &res));

    const char* source_c_str = source_str.c_str();
    const size_t source_size = source_str.size();
    cl_program program;
    CHECKP(
        program, res, clCreateProgramWithSource, (context, 1, &source_c_str, &source_size, &res)
    );

    CHECK(clBuildProgram, (program, 1, &device_id, NULL, NULL, NULL));

    cl_kernel kernel;
    CHECKP(kernel, res, clCreateKernel, (program, "runProgram", &res));

    size_t iter_size = 9 * 9 * 9 * 9 * 9 * 9;
    cl_uint* hbuffer = new cl_uint[iter_size + 1];
    cl_mem buffer;
    CHECKP(
        buffer, res, clCreateBuffer,
        (context, CL_MEM_WRITE_ONLY, (iter_size + 1) * sizeof(cl_uint), nullptr, &res)
    );
    CHECK(clSetKernelArg, (kernel, 0, sizeof(cl_mem), (void*)&buffer));

    size_t inner = 1;
    for (int i = 0; i < DEPTH; i++) {
        inner *= 9;
    }
    size_t min = ~0UL;
    for (size_t iter_offset = b10to9(99999999999999) + 1 - iter_size; min == ~0UL;
         iter_offset -= iter_size) {
        timespec start;
        clock_gettime(CLOCK_MONOTONIC, &start);
        cl_ulong off = iter_offset;
        CHECK(clSetKernelArg, (kernel, 1, sizeof(cl_ulong), (void*)&off));
        CHECK(
            clEnqueueNDRangeKernel,
            (queue, kernel, 1, NULL, &iter_size, nullptr, 0, nullptr, nullptr)
        );
        CHECK(
            clEnqueueReadBuffer,
            (queue, buffer, CL_TRUE, 0, sizeof(cl_int), hbuffer, 0, nullptr, nullptr)
        );
        if (hbuffer[0]) {
            CHECK(
                clEnqueueReadBuffer, (queue, buffer, CL_TRUE, 0, (iter_size + 1) * sizeof(cl_uint),
                                      hbuffer, 0, nullptr, nullptr)
            );
            for (size_t i = iter_size; i > 0; i--) {
                if (hbuffer[i]) {
                    min = (iter_offset + i - 1) * inner + hbuffer[i] - 1;
                    break;
                }
            }
        }
        timespec end;
        clock_gettime(CLOCK_MONOTONIC, &end);
        size_t nano_per_sec = 1000 * 1000 * 1000;
        size_t ps = iter_size * inner * nano_per_sec
                    / ((end.tv_sec - start.tv_sec) * nano_per_sec + end.tv_nsec - start.tv_nsec);
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
