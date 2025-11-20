#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int tests_run = 0;
int tests_failed = 0;

#define ASSERT(message, test) do { \
    if (!(test)) { \
        printf(ANSI_COLOR_RED "FAIL: %s\n" ANSI_COLOR_RESET, message); \
        tests_failed++; \
    } else { \
        printf(ANSI_COLOR_GREEN "PASS: %s\n" ANSI_COLOR_RESET, message); \
    } \
    tests_run++; \
} while (0)

#define RUN_TEST(test) do { \
    test(); \
} while (0)

void print_test_summary() {
    printf("\nTests ejecutados: %d\n", tests_run);
    if (tests_failed == 0) {
        printf(ANSI_COLOR_GREEN "¡Todos los tests pasaron!\n" ANSI_COLOR_RESET);
    } else {
        printf(ANSI_COLOR_RED "%d tests fallaron.\n" ANSI_COLOR_RESET, tests_failed);
    }
}

#endif
