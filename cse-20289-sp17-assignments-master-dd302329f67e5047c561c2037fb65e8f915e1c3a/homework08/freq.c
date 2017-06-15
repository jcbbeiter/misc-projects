/* freq.c */

#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s\n", PROGRAM_NAME);
    fprintf(stderr, "    -f FORMAT        Output format (KEY, KEY_VALUE, VALUE, VALUE_KEY)\n");
    fprintf(stderr, "    -l LOAD_FACTOR   Load factor for hash table\n");
    exit(status);
}

void freq_stream(FILE *stream, double load_factor, DumpMode mode) {

    char buffer[BUFSIZ];

    Map* m = map_create(0, load_factor); 

    while(fgets(buffer, BUFSIZ, stream))
    {

        char* token = strtok(buffer," \t\n");
        while(token != NULL)
        {
            Entry* e = map_search(m,token);

            if(e == NULL)
                map_insert(m,token,(Value)(int64_t)1,NUMBER);
            else
                e->value.number++;
            token = strtok(NULL," \t\n");
        }
    }
    map_dump(m,stdout,mode);
    map_delete(m);
}

/* Main Execution */

int main(int argc, char *argv[]) {

    double load_factor = 0;
    DumpMode mode = VALUE_KEY;
    /* Parse command line arguments */
    PROGRAM_NAME = argv[0];
    for(int i = 1; i < argc; i++)
    {
        char* arg = argv[i];
        if(*arg != '-' || strlen(arg) != 2)
            usage(1);

        if(i == argc-1 && arg[1] != 'h')
            usage(1);

        switch(arg[1])
        {
            case 'f': ; //empty statement to be able to do declaration
                char* format_string = argv[++i];
                if(strcmp(format_string,"KEY") == 0)
                    mode = KEY;
                else if(strcmp(format_string,"VALUE") == 0)
                    mode = VALUE;
                else if(strcmp(format_string,"KEY_VALUE") == 0)
                    mode = KEY_VALUE;
                else if(strcmp(format_string,"VALUE_KEY") == 0)
                    mode = VALUE_KEY;
                else
                    mode = KEY;
                break;
            case 'l':
                load_factor = atof(argv[++i]);
                break;
            case 'h':
                usage(0);
                break;
            default:
                usage(1);
        }
    }

    /* Compute frequencies of data from stdin */
    freq_stream(stdin,load_factor,mode);
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
