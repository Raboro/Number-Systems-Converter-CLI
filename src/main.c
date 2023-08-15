#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

int countTargetBasis(const char *str) {
    int count = 0;
    while (*str) {
        if (*str == ',') {
            count++;
        }
        str++;
    }
    return count;
}

int action(int argc, char* argv[], struct option* options) {
    int opt;
    int base;
    char* endPtr;
    int targetBases[countTargetBasis(argv[4])];
    int numTargetBases = 0;
    const char *charNumber;

    while ((opt = getopt_long(argc, argv, "hi:t:n:", options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                printHelp();
                return 0;
            case 'i':
                base = strtol(optarg, &endPtr, 10);
                if (*endPtr != '\0') {
                    fprintf(stderr, "Invalid source base.\n");
                    return 1;
                }
                break;
            case 't': {
                char *targetBaseToken = strtok(optarg, ",");
                while (targetBaseToken != NULL) {
                    targetBases[numTargetBases++] = strtol(targetBaseToken, &endPtr, 10);
                    if (*endPtr != '\0') {
                        fprintf(stderr, "Invalid target base.\n");
                        return 1;
                    }
                    targetBaseToken = strtok(NULL, ",");
                }
                break;
            }
            case 'n':
                charNumber = optarg;
                break;
            default:
                printErrorInvalidInput();
        }
    }
    const double number = strtod(charNumber, NULL);
    if (base == 0 || numTargetBases == 0 || isnan(number)) {
        fprintf(stderr, "Missing required arguments.\n");
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    static struct option options[] = {
            {"help", no_argument, 0, 'h'},
            {"input-base", required_argument, 0, 'i'},
            {"target-bases", required_argument, 0, 't'},
            {"number", required_argument, 0, 'n'},
            {0, 0, 0, 0}
    };
    return action(argc, argv, options);
}
