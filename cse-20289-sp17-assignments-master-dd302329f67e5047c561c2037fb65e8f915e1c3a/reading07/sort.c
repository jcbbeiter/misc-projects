/* sort.c */

#include <stdio.h>
#include <stdlib.h>

/* Constants */

#define MAX_NUMBERS (1<<10)

/* Functions */

size_t read_numbers(FILE *stream, int numbers[], size_t n) {
    size_t i = 0;

    while (i < n && scanf("%d", &numbers[i]) != EOF) {
    i++;
    }

    return i;
}

void sort_numbers(int numbers[], size_t n) {
    // runs through each index on sort
    for(int i = 1; i < n; i++)
    {
        int dest = i;
        //finds destination in sorted beginning
        for(int j = 0; j < i; j++)
        {
            if(numbers[j] > numbers[i])
            {
                dest = j;
                break;

            }
        }
        int val = numbers[i];
        //shifts numbers over, starting from i
        for(int index = i; index > dest; index--)
            numbers[index] = numbers[index-1];

        //inserts value at destination
        numbers[dest] = val;
    }
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int numbers[MAX_NUMBERS];
    size_t nsize;

    nsize = read_numbers(stdin, numbers, MAX_NUMBERS);
    if(nsize == 0)
    {
        printf("\n");
        return 0;
    }
    sort_numbers(numbers, nsize);
    for(int i = 0; i < nsize-1; i++)
        printf("%d ", numbers[i]);
    printf("%d\n", numbers[nsize-1]);

    return EXIT_SUCCESS;
}
