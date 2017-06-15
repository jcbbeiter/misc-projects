/* lsort.c */

#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;
bool nFlag = false;
bool qFlag = false;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s\n", PROGRAM_NAME);
    fprintf(stderr, "  -n   Numerical sort\n");
    fprintf(stderr, "  -q   Quick sort\n");
    exit(status);
}

void lsort(FILE *stream, bool numeric, bool quicksort) {
    char buffer[BUFSIZ];
    struct list* l = list_create();

    while(fgets(buffer, BUFSIZ, stream))
    {
        if(buffer[strlen(buffer)-1] == '\n')
            buffer[strlen(buffer)-1] = '\0';
        list_push_front(l,buffer);
    }
    
    node_compare f;

    if(numeric)
        f = node_compare_number;
    else
        f = node_compare_string;

    if(quicksort)
        list_qsort(l,f);
    else
        list_msort(l,f);

    for(struct node* node = l->head; node != NULL; node = node->next)
        printf("%s\n",node->string);

    list_delete(l);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* Parse command line arguments */
    PROGRAM_NAME = argv[0];
    for(int i = 1; i < argc; i++)
    {
        if(*argv[i] != '-' || strlen(argv[i]) != 2)
            usage(1);

        switch(argv[i][1])
        {
            case 'n':
                nFlag = true;
                break;
            case 'q':
                qFlag = true;
                break;
            case 'h':
                usage(0);
            default:
                usage(1);
        }
    }
    /* Sort using list */
    lsort(stdin,nFlag,qFlag);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
