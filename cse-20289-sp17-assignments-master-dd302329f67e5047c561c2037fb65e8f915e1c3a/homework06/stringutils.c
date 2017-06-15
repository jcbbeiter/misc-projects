/* stringutils.c: String Utilities */

#include "stringutils.h"

#include <ctype.h>
#include <string.h>
#include <math.h>

/**
 * Convert all characters in string to lowercase.
 * @param   s       String to convert
 * @return          Pointer to beginning of modified string
 **/
char *	string_lowercase(char *s) {
    for(char* c = s; *c; c++)
        *c = tolower(*c);
    return s;
}

/**
 * Convert all characters in string to uppercase.
 * @param   s       String to convert
 * @return          Pointer to beginning of modified string
 **/
char *	string_uppercase(char *s) {
    for(char* c = s; *c; c++)
        *c = toupper(*c);
    return s;
}

/**
 * Returns whether or not the 's' string starts with given 't' string.
 * @param   s       String to search within
 * @param   t       String to check for
 * @return          Whether or not 's' starts with 't'
 **/
bool	string_startswith(char *s, char *t) {
    char* n = s;
    for(char* c = t; *c; c++)
        if(*n++ != *c)
            return false;
    return true;
}

/**
 * Returns whether or not the 's' string ends with given 't' string.
 * @param   s       String to search within
 * @param   t       String to check for
 * @return          Whether or not 's' ends with 't'
 **/
bool	string_endswith(char *s, char *t) {
    char* sPos = s + strlen(s)-strlen(t);
    for(char* c = t; *c; c++)
        if(*c != *sPos++)
            return false;
    return true;
}

/**
 * Removes trailing newline (if present).
 * @param   s       String to modify
 * @return          Pointer to beginning of modified string
 **/
char *	string_chomp(char *s) {

    char* c = s + strlen(s) - 1;

    if(*c == 10)
        *c = '\0';

    return s;
}

/**
 * Removes whitespace from front and back of string (if present).
 * @param   s       String to modify
 * @return          Pointer to beginning of modified string
 **/
char *	string_strip(char *s) {

    char* sEnd = s + strlen(s);
    while(isspace(*sEnd) || *sEnd == '\0')
        *sEnd-- = '\0';

    char* read = s;
    char* write = s;

    while(isspace(*read))
        read++;

    while(*read != '\0')
        *write++ = *read++;

    *write = '\0';

    return s;
}

/**
 * Reverses a string given the provided from and to pointers.
 * @param   from    Beginning of string
 * @param   to      End of string
 * @return          Pointer to beginning of modified string
 **/
static char *	string_reverse_range(char *from, char *to) {
    
    char* start = from;
    char* end = to;
    char temp;

    while(start < end)
    {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }

    return from;
}

/**
 * Reverses a string.
 * @param   s       String to reverse
 * @return          Pointer to beginning of modified string
 **/
char *	string_reverse(char *s) {
    string_reverse_range(s, s + strlen(s)-1);

    return s;
}

/**
 * Reverses all words in a string.
 * @param   s       String with words to reverse
 * @return          Pointer to beginning of modified string
 **/
char *	string_reverse_words(char *s) {


    string_reverse(s);

    char* wordStart = s;
    while(isspace(*wordStart) && *wordStart != '\0')
        wordStart++;

    char* wordEnd;

    while(*wordStart != '\0')
    {
        wordEnd = wordStart;
        while(!isspace(*(wordEnd+1)) && *(wordEnd+1) != '\0')
            wordEnd++;
        string_reverse_range(wordStart,wordEnd);
        wordStart = wordEnd+1;
        while(isspace(*wordStart) && *wordStart != '\0')
            wordStart++;
    }

    return s;
}

/**
 * Replaces all instances of 'from' in 's' with corresponding values in 'to'.
 * @param   s       String to translate
 * @param   from    String with letter to replace
 * @param   to      String with corresponding replacment values
 * @return          Pointer to beginning of modified string
 **/
char *	string_translate(char *s, char *from, char *to) {

    for(char* c = s; *c; c++)
        for(char* p = from; *p; p++)
            if(*c == *p)
            {
            /* have to find target character iteratively in case to is too short*/
                for(char* dest = to; *dest; dest++)
                    if(dest == to + (p - from))
                    {
                        *c = *dest;
                        break;
                    }
                break;
            }

    return s;
}

/**
 * Converts given string into an integer.
 * @param   s       String to convert
 * @param   base    Integer base
 * @return          Converted integer value
 **/
int	string_to_integer(char *s, int base) {
    int number = 0;
    int shift = 0;
    for(char* c = s; *c; c++)
    {
        if(*c > 47 && *c < 58)
            shift = '0';
        else if(*c > 64 && *c < 71)
            shift = 55;
        else if(*c > 96 && *c < 103)
            shift = 87;
        else
            continue;

        number = number*base + (*c-shift);
    }
    
    return number;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
