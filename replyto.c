#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
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

    if (strlen(argv[1]) > MAX_FILENAME) {
        fprintf(stderr, "Filename too big\n");
        return 1;
    }
#ifdef ALLOCA
    char *filename = (char*)alloca(strlen(argv[1]) + sizeof(EXTENSION));
#else
    char *filename = (char*)malloc(strlen(argv[1]) + sizeof(EXTENSION));

    if (!filename) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }
#endif
    strcpy(filename, argv[1]);
    strcat(filename, EXTENSION);
    FILE *ifp;
    if(argc == 1 || (argc == 2 && stdout_flag)) {
        ifp = stdin;
    }
    else {
        ifp = fopen(argv[1], "r");
        if (!ifp) {
            fprintf(stderr, "Failed to open file for reading\n");
            return 1;
        }
    }
goto loop;
open_fd:
#ifndef STDOUT
    int ofd = open(filename, FLAGS, MODE);
    if (ofd == -1) {
        fprintf(stderr, "Failed to open file for writing\n");
        return 1;
    }
#else
    int ofd;
    if(stdout_flag) {
        ofd = STDOUT;
    }
    else {
        ofd = open(filename, FLAGS, MODE);
    }
    if (ofd == -1) {
        fprintf(stderr, "Failed to open file for writing\n");
        return 1;
    }
#endif
goto read_check;
loop:
int read = 0;
    for(;;) {
        char *buf = NULL;
        size_t buflen = BUFLEN;
        int nread = getline(&buf, &buflen, ifp);
        if(nread == -1) {
            return 0;
        }
/*madness to not open empty file if not needed*/
read_check:
        if(!read) {
            read = 1;
            goto open_fd;
        }
        if(write(ofd, ">", 1) == -1) {
            fprintf(stderr, "write() failed\n");
            return 1;
        }
        if(write(ofd, buf, nread) == -1) {
            fprintf(stderr, "write() failed\n");
            return 1;
        }
    }
/* Never reached */
    return 0;
}
