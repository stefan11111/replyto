#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "replyto.h"

int main(int argc, char **argv)
{
    char stdout_flag = 0;

    if (argc == 3 && !strcmp(argv[2], "-1")) {
        stdout_flag = 1;
    }

    if (argc == 2 && !strcmp(argv[1], "-1")) {
        stdout_flag = 1;
    }

    if (argc > 2 && !stdout_flag) {
        fprintf(stderr, "USAGE: %s [file] [-1]\n", argv[0]);
        return 1;
    }

    if (argc == 1) {
        argv[1] = FILENAME;
    }

    char filename[MAX_FILENAME + sizeof(EXTENSION)];

    *stpncpy(stpncpy(filename, argv[1], MAX_FILENAME), EXTENSION, sizeof(EXTENSION) - 1) == '\0';
    FILE *f = (argc == 1 || (argc == 2 && stdout_flag)) ? stdin : fopen(argv[1], "r");

    if (!f) {
        fprintf(stderr, "Failed to open file for reading\n");
        return 1;
    }

    FILE *g = stdout_flag ? stdout : fopen(filename, "w");

    if (!g) {
        fprintf(stderr, "Failed to open file for writing\n");
        return 1;
    }

    fprintf(g, ">");

    for(;;) {
        char c;
        if (fscanf(f, "%c", &c) == EOF) {
            fprintf(g, "\n");
            return 0;
        }

        fprintf(g, "%c", c);

        if (c == '\n') {
            fprintf(g, ">");
        }
    }
/* Never reached */
    return 0;
}
