#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Declarations from convert.c
void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

typedef struct {
    char function_name[50];
    char input1[100];
    char expected[200];
} TestCase;

int main() {
    FILE *f = fopen("A2_tests.txt", "r");
    if (!f) {
        printf("Could not open test file.\n");
        return 1;
    }

    char line[300];
    int test_num = 1, pass = 0, fail = 0;

    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '#' || strlen(line) < 2) continue;

        TestCase test;
        char input2[200];
        int num = sscanf(line, "%s %s %s", test.function_name, test.input1, test.expected);

        char actual[300];

        if (strcmp(test.function_name, "oct_to_bin") == 0) {
            oct_to_bin(test.input1, actual);
        } else if (strcmp(test.function_name, "oct_to_hex") == 0) {
            oct_to_hex(test.input1, actual);
        } else if (strcmp(test.function_name, "hex_to_bin") == 0) {
            hex_to_bin(test.input1, actual);
        } else if (strcmp(test.function_name, "to_sign_magnitude") == 0) {
            int32_t n = atoi(test.input1);
            to_sign_magnitude(n, actual);
        } else if (strcmp(test.function_name, "to_ones_complement") == 0) {
            int32_t n = atoi(test.input1);
            to_ones_complement(n, actual);
        } else if (strcmp(test.function_name, "to_twos_complement") == 0) {
            int32_t n = atoi(test.input1);
            to_twos_complement(n, actual);
        } else {
            continue;
        }

        if (strcmp(actual, test.expected) == 0) {
            printf("Test %d: %s(%s) -> PASS\n", test_num, test.function_name, test.input1);
            pass++;
        } else {
            printf("Test %d: %s(%s) -> Expected: %s, Got: %s [FAIL]\n",
                   test_num, test.function_name, test.input1, test.expected, actual);
            fail++;
        }
        test_num++;
    }

    fclose(f);

    printf("\nSummary: %d passed, %d failed\n", pass, fail);
    return 0;
}
