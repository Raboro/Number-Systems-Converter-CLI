#include <stdio.h>

void printHelp() {
    printf("Usage: ns [OPTIONS] [SOURCE_BASE] [TARGET_BASES] [NUMBER]\n");
    printf("Options:\n");
    printf("  -h, --help               Display this help message\n");
    printf("  -i, --input-base BASE    Source number base\n");
    printf("  -t, --target-bases BASES Space-separated list of target bases\n");
    printf("  -n, --number NUMBER      Number to convert\n");
}

int main() {
    printHelp();
    return 0;
}
