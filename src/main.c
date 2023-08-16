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
    printf("  -m, --minus              If present then - else +");
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

double toDez(const char *number, int base) {
    double decimalNumber = 0.0;
    int dotPosition = strchr(number, '.') - number;

    for (int i = 0; i < strlen(number); i++) {
        if (number[i] == '.') continue;
        int digit = (number[i] >= 'A') ? number[i] - 'A' + 10 : number[i] - '0';
        decimalNumber += digit * pow(base, (dotPosition < i) ? dotPosition - i : dotPosition - i - 1);
    }

    return decimalNumber;
}

int action(int argc, char* argv[], struct option* options) {
    int opt;
    int base;
    char* endPtr;
    int targetBases[(argc == 2) ? 0 : countTargetBasis(argv[4])]; // if only -h => size = 0
    int numTargetBases = 0;
    const char *charNumber;
    int multiplier = 1;

    while ((opt = getopt_long(argc, argv, "hi:t:n:m", options, NULL)) != -1) {
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
            case 'm':
                multiplier = -1;
                break;
            default:
                printErrorInvalidInput();
        }
    }
    if (base == 0 || numTargetBases == 0 || isnan(strtod(charNumber, NULL))) {
        fprintf(stderr, "Missing required arguments.\n");
        return 1;
    }
    const double dez = toDez(charNumber, base) * multiplier;
    printf("%f", dez);
    return 0;
}

int main(int argc, char* argv[]) {
    static struct option options[] = {
            {"help", no_argument, 0, 'h'},
            {"input-base", required_argument, 0, 'i'},
            {"target-bases", required_argument, 0, 't'},
            {"number", required_argument, 0, 'n'},
            {"minus", no_argument, 0, 'm'},
            {0, 0, 0, 0}
    };
    return action(argc, argv, options);
}
