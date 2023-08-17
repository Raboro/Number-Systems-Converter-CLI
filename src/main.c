#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


void printHelp() {
    printf("Usage:\n  ns -h\n");
    printf("  ns -i [SOURCE_BASE] -t [TARGET_BASES] -n [NUMBER]\n");
    printf("  ns -i [SOURCE_BASE] -t [TARGET_BASES] -n [NUMBER] -m\n");
    printf("Options:\n");
    printf("  -h, --help               Display this help message\n");
    printf("  -i, --input-base BASE    Source number base\n");
    printf("  -t, --target-bases BASES Comma-separated list of target bases\n");
    printf("  -n, --number NUMBER      Number to convert\n");
    printf("  -m, --minus              If present then - else +");
}

int printError(char error[]) {
    fprintf(stderr, "%s", error);
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

bool noComma(const char *array) {
    for (int i = 0; array[i] != '\0'; i++) {
        if (array[i] == '.') {
            return false;
        }
    }
    return true;
}

void toTargetBase(double dez, int targetBase, char symbol) {
    int intPart = (int) dez;
    double fracPart = dez - intPart;

    // Convert integer part to target base
    char *result = NULL;
    size_t length = 0;
    while (intPart > 0) {
        int remainder = intPart % targetBase;
        char digit = (remainder < 10) ? remainder + '0' : remainder - 10 + 'A';
        result = (char *) realloc(result, length + 2);  // +1 for digit, +1 for null terminator
        if (result == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }
        result[length++] = digit;
        result[length] = '\0';
        intPart /= targetBase;
    }

    // Reverse the integer part
    for (size_t i = 0; i < length / 2; i++) {
        char temp = result[i];
        result[i] = result[length - i - 1];
        result[length - i - 1] = temp;
    }

    // Convert fractional part to target base
    if (fracPart > 0) {
        result = (char *) realloc(result, length + 8);  // +1 for '.', +6 for decimal places, +1 for null terminator
        if (result == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }
        result[length++] = '.';
        for (int i = 0; i < 6; i++) {  // Convert up to 6 decimal places
            fracPart *= targetBase;
            int digit = (int) fracPart;
            result[length++] = digit < 10 ? digit + '0' : digit - 10 + 'A';
            fracPart -= digit;
        }
        result[length] = '\0';
    }

    printf("into base %d => %c%s\n", targetBase, symbol, result);
    free(result);
}

int action(int argc, char* argv[], struct option* options) {
    int opt;
    int base;
    char* endPtr;
    int targetBases[(argc == 2) ? 0 : countTargetBasis(argv[4])]; // if only -h => size = 0
    int numTargetBases = 0;
    const char *charNumber;
    char symbol = '+';

    while ((opt = getopt_long(argc, argv, "hi:t:n:m", options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                printHelp();
                return 0;
            case 'i':
                base = strtol(optarg, &endPtr, 10);
                if (*endPtr != '\0') {
                    return printError("Invalid source base.");
                }
                break;
            case 't': {
                char *targetBaseToken = strtok(optarg, ",");
                while (targetBaseToken != NULL) {
                    targetBases[numTargetBases++] = strtol(targetBaseToken, &endPtr, 10);
                    if (*endPtr != '\0') {
                        return printError("Invalid target base.");
                    }
                    targetBaseToken = strtok(NULL, ",");
                }
                break;
            }
            case 'n':
                charNumber = optarg;
                break;
            case 'm':
                symbol = '-';
                break;
            default:
                return printError("Try 'ns --help' for more information");
        }
    }
    if (base == 0 || numTargetBases == 0 || isnan(strtod(charNumber, NULL))) {
        return printError("Invalid input.");
    }
    if (noComma(charNumber)) {
        return printError("Missing '.' => please do: number.");
    }

    const double dez = toDez(charNumber, base);
    printf("Input number %f converted:\n", strtod(charNumber, NULL));
    for (int i = 0; i < numTargetBases; i++) {
        toTargetBase(dez, targetBases[i], symbol);
    }
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
