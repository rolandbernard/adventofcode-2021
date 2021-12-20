
__kernel void applyAlgo(
    __global uchar* output,
    __global const uchar* input,
    __constant const uchar* algo,
    int2 size
) {
    int x = get_global_id(0) / size.y;
    int y = get_global_id(0) % size.y;
    int idx = 0;
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            int i = min(max(x + di, 0), size.x - 1);
            int j = min(max(y + dj, 0), size.y - 1);
            idx <<= 1;
            idx |= input[i * size.y + j];
        }
    }
    output[x * size.y + y] = algo[idx];
}

