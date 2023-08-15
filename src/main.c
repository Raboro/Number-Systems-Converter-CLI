#include <stdio.h>
#include <getopt.h>

void printHelp() {
    printf("Usage: ns [OPTIONS] [SOURCE_BASE] [TARGET_BASES] [NUMBER]\n");
    printf("Options:\n");
    printf("  -h, --help               Display this help message\n");
    printf("  -i, --input-base BASE    Source number base\n");
    printf("  -t, --target-bases BASES Space-separated list of target bases\n");
    printf("  -n, --number NUMBER      Number to convert\n");
}

int printErrorInvalidInput() {
    fprintf(stderr, "Try 'ns --help' for more information.\n");
    return 1;
}

int main(int argc, char* argv[]) {
    int opt;
    static struct option options[] = {
            {"help", no_argument, 0, 'h'},
            {"input-base", required_argument, 0, 'i'},
            {"target-bases", required_argument, 0, 't'},
            {"number", required_argument, 0, 'n'},
            {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "hi:t:n:", options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                printHelp();
                return 0;
            default:
                return printErrorInvalidInput();
        }
    }
    return printErrorInvalidInput();
}
