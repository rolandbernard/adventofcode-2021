
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

typedef struct Packet Packet;

struct Packet {
    int version;
    int type;
    union {
        int literal;
        struct {
            int length_type;
            size_t length;
            size_t sub_count;
            Packet* subs;
        };
    };
};

uint64_t hexDigit(char c) {
    if (c >= 'A' && c <= 'F') {
        return 10 + c - 'A';
    } else if (c >= 'a' && c <= 'f') {
        return 10 + c - 'f';
    } else {
        return c - '0';
    }
}

uint64_t readBits(size_t n) {
    static uint64_t buffer = 0;
    static size_t buffer_size = 0;
    while (buffer_size < n) {
        buffer <<= 4;
        buffer |= hexDigit(getc(stdin));
        buffer_size += 4;
    }
    buffer_size -= n;
    return (buffer >> (buffer_size)) & ((1 << n) - 1);
}

size_t readPacket(Packet* packet) {
    packet->version = readBits(3);
    packet->type = readBits(3);
    int bits = 6;
    if (packet->type == 4) {
        packet->literal = 0;
        int cur = 0;
        do {
            cur = readBits(5);
            bits += 5;
            packet->literal <<= 4;
            packet->literal |= cur & 0xf;
        } while ((cur & 0x10) != 0);
    } else {
        packet->length_type = readBits(1);
        bits += 1;
        if (packet->length_type == 0) {
            packet->length = readBits(15);
            bits += 15 + packet->length;
            packet->sub_count = 0;
            packet->subs = malloc(sizeof(Packet) * (packet->length / 11));
            size_t left = packet->length;
            while (left != 0) {
                left -= readPacket(packet->subs + packet->sub_count);
                packet->sub_count++;
            }
        } else {
            packet->length = readBits(11);
            packet->sub_count = packet->length;
            packet->subs = malloc(sizeof(Packet) * packet->sub_count);
            bits += 11;
            for (size_t i = 0; i < packet->sub_count; i++) {
                bits += readPacket(packet->subs + i);
            }
        }
    }
    return bits;
}

int versionSum(Packet* packet) {
    if (packet->type == 4) {
        return packet->version;
    } else {
        int ret = packet->version;
        for (size_t i = 0; i < packet->sub_count; i++) {
            ret += versionSum(packet->subs + i);
        }
        return ret;
    }
}

int main() {
    Packet root;
    readPacket(&root);
    fprintf(stdout, "Result: %i\n", versionSum(&root));
}

