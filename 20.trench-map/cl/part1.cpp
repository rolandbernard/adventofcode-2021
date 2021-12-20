
#define CL_TARGET_OPENCL_VERSION 300
#include <CL/cl.h>

#include <bits/stdc++.h>

using namespace std;

#define ITERATIONS 2

int main() {
    vector<cl_uchar> algo(512);
    vector<vector<cl_uchar>> img;
    for (size_t i = 0; i < 512; i++) {
        char c;
        cin >> c;
        algo[i] = c == '#' ? 1 : 0;
    }
    cin.ignore(2);
    string line;
    while (getline(cin, line)) {
        img.push_back(vector<cl_uchar>(line.size()));
        for (size_t i = 0; i < line.size(); i++) {
            img.back()[i] = line[i] == '#' ? 1 : 0;
        }
    }

    ifstream file( "./cl/kernel.cl", ios::ate);
    size_t file_size = file.tellg();
    vector<char> data(file_size);
    file.seekg(0);
    file.read(data.data(), file_size);
    file.close();
    string source(data.data(), file_size);

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

    const char* source_c_str = source.c_str();
    const size_t source_size = source.size();
    cl_program program = clCreateProgramWithSource(context, 1, &source_c_str, &source_size, &res);

    clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    cl_kernel kernel = clCreateKernel(program, "applyAlgo", &res);

    cl_int2 size;
    size.x = 2 * ITERATIONS + img.size();
    size.y = 2 * ITERATIONS + img[0].size();
    size_t total_size = size.x * size.y;
    cl_uchar* hbuffer = new cl_uchar[total_size];
    for (size_t i = 0; i < total_size; i++) {
        hbuffer[i] = 0;
    }
    for (size_t i = 0; i < img.size(); i++) {
        for (size_t j = 0; j < img[0].size(); j++) {
            hbuffer[(i + ITERATIONS) * size.y + j + ITERATIONS] = img[i][j];
        }
    }
    cl_mem cimg[2];
    cimg[0] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, total_size, hbuffer, &res);
    cimg[1] = clCreateBuffer(context, CL_MEM_WRITE_ONLY, total_size, nullptr, &res);
    cl_mem calgo = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, 512, algo.data(), &res);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&cimg[1]);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&cimg[0]);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&calgo);
    clSetKernelArg(kernel, 3, sizeof(cl_int2), (void*)&size);

    for (size_t s = 0; s < ITERATIONS; s++) {
        clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &total_size, nullptr, 0, nullptr, nullptr);
        clEnqueueCopyBuffer(queue, cimg[1], cimg[0], 0, 0, total_size, 0, nullptr, nullptr);
    }
    clEnqueueReadBuffer(queue, cimg[0], CL_TRUE, 0, total_size, hbuffer, 0, nullptr, nullptr);

    size_t count = 0;
    for (size_t i = 0; i < total_size; i++) {
        count += hbuffer[i];
    }
    cout << "Result: " << count << endl;
}

