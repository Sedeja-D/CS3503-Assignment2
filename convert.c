#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

// ============================================================================
// Helper: Convert an integer value to a 32-bit binary string
// ============================================================================
void to_32bit_binary(uint32_t value, char *out) {
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((value >> i) & 1) ? '1' : '0';
    }
    out[32] = '\0';
}

// ============================================================================
// Part 1: Direct Mapping Functions
// ============================================================================

// 1. oct_to_bin
void oct_to_bin(const char *oct, char *out) {
    int len = strlen(oct);
    int pos = 0;
    for (int i = 0; i < len; i++) {
        int digit = oct[i] - '0'; // convert char to int
        out[pos++] = (digit & 4) ? '1' : '0';
        out[pos++] = (digit & 2) ? '1' : '0';
        out[pos++] = (digit & 1) ? '1' : '0';
    }
    out[pos] = '\0';
}

// 2. oct_to_hex
void oct_to_hex(const char *oct, char *out) {
    char bin[200];
    oct_to_bin(oct, bin);

    // pad binary string to multiple of 4 bits
    int len = strlen(bin);
    int pad = (4 - (len % 4)) % 4;
    char padded[200];
    for (int i = 0; i < pad; i++) padded[i] = '0';
    strcpy(padded + pad, bin);

    // convert groups of 4 bits to hex
    int pos = 0;
    for (int i = 0; i < strlen(padded); i += 4) {
        int val = (padded[i] - '0') * 8 +
                  (padded[i+1] - '0') * 4 +
                  (padded[i+2] - '0') * 2 +
                  (padded[i+3] - '0');
        if (val < 10) out[pos++] = '0' + val;
        else out[pos++] = 'A' + (val - 10);
    }
    out[pos] = '\0';
}

// 3. hex_to_bin
void hex_to_bin(const char *hex, char *out) {
    int pos = 0;
    for (int i = 0; hex[i] != '\0'; i++) {
        char c = toupper(hex[i]);
        int val;
        if (c >= '0' && c <= '9') val = c - '0';
        else if (c >= 'A' && c <= 'F') val = 10 + (c - 'A');
        else continue; // skip invalid

        out[pos++] = (val & 8) ? '1' : '0';
        out[pos++] = (val & 4) ? '1' : '0';
        out[pos++] = (val & 2) ? '1' : '0';
        out[pos++] = (val & 1) ? '1' : '0';
    }
    out[pos] = '\0';
}

// ============================================================================
// Part 2: Signed Number Representations
// ============================================================================

// 4. to_sign_magnitude
void to_sign_magnitude(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary((uint32_t)n, out);
    } else {
        int32_t absval = -n;
        to_32bit_binary((uint32_t)absval, out);
        out[0] = '1'; // set sign bit
    }
}

// 5. to_ones_complement
void to_ones_complement(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary((uint32_t)n, out);
    } else {
        uint32_t absval = (uint32_t)(-n);
        char temp[33];
        to_32bit_binary(absval, temp);
        for (int i = 0; i < 32; i++) {
            out[i] = (temp[i] == '0') ? '1' : '0';
        }
        out[32] = '\0';
    }
}

// 6. to_twos_complement
void to_twos_complement(int32_t n, char *out) {
    uint32_t val = (uint32_t)n; // already in 2's complement in memory
    to_32bit_binary(val, out);
}
