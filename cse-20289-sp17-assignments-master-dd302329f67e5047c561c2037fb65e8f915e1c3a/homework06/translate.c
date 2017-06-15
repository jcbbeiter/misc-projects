/* translate.c: string translator */

#include "stringutils.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char *PROGRAM_NAME = NULL;

/* Define Modes */
enum flags
{
    STRIP = 1<<0,
    REVERSEL = 1<<1,
    REVERSEW = 1<<2,
    LOWER = 1<<3,
    UPPER = 1<<4,
};


/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s SOURCE TARGET\n\n", PROGRAM_NAME);
    fprintf(stderr, "Post Translation filters:\n\n");
    fprintf(stderr, "   -s     Strip whitespace\n");
    fprintf(stderr, "   -r     Reverse line\n");
    fprintf(stderr, "   -w     Reverse words in line\n");
    fprintf(stderr, "   -l     Convert to lowercase\n");
    fprintf(stderr, "   -u     Convert to uppercase\n");
    exit(status);
}

void translate_stream(FILE *stream, char *source, char *target, int mode) {
    char buffer[BUFSIZ];

    while(fgets(buffer, BUFSIZ, stream))
    {
        string_chomp(buffer);
        string_translate(buffer, source, target);

        if(mode & STRIP)
            string_strip(buffer);
        if(mode & REVERSEL)
            string_reverse(buffer);
        if(mode & REVERSEW)
            string_reverse_words(buffer);
        if(mode & LOWER)
            string_lowercase(buffer);
        if(mode & UPPER)
            string_uppercase(buffer);

        printf("%s\n", buffer);
    }
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* Parse command line arguments */

    int arg = 1;
    int mask = 0;

    while(arg < argc && *argv[arg] == '-')
    {
        if(strlen(argv[arg]) < 2)
            usage(1);

        switch(*(argv[arg]+1))
        {
            case 's':
                mask |= STRIP;
                break;
            case 'r':
                mask |= REVERSEL;
                break;
            case 'w':
                mask |= REVERSEW;
                break;
            case 'l':
                mask |= LOWER;
                break;
            case 'u':
                mask |= UPPER;
                break;
            case 'h':
                usage(0);
            default:
                usage(1);
        }
        arg++;
    }
    char* source;
    char* target;

    if(argc - arg == 0)
    {
        source = "";
        target = "";
    }
    else if(argc - arg == 2)
    {
        source = argv[arg++];
        target = argv[arg++];
    }
    else
        usage(1);

    /* Translate Stream */
    translate_stream(stdin, source, target, mask);

    return EXIT_SUCCESS;
}
/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
