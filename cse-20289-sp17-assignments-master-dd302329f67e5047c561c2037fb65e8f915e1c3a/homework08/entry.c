/* entry.c: map entry */

#include "map.h"
#include <inttypes.h>

/**
 * Create entry structure.
 * @param   key             Entry's key.
 * @param   value           Entry's value.
 * @param   next            Reference to next entry.
 * @param   type            Entry's value's type.
 * @return  Allocate Entry structure.
 */
Entry *		entry_create(const char *key, const Value value, Entry *next, Type type) {
    Entry* newEntry = malloc(sizeof(Entry));
    if(newEntry == NULL)
        return NULL;

    newEntry->key = strdup(key);

    if(type == NUMBER)
    {
        newEntry->type = NUMBER;
        newEntry->value.number = value.number;
    }
    else
    {
        newEntry->type = STRING;
        newEntry->value.string = strdup(value.string);
    }

    newEntry->next = next;

    return newEntry;
}

/**
 * Delete entry structure.
 * @param   e               Entry structure.
 * @param   recursive       Whether or not to delete remainder of entries.
 * return   NULL.
 */
Entry *		entry_delete(Entry *e, bool recursive) {
    if(e == NULL)
        return NULL;

    if(e->type == STRING)
        free(e->value.string);
    free(e->key);
    
    if(recursive && e->next != NULL)
        entry_delete(e->next,true);

    free(e);

    return NULL;
}

/**
 * Update entry's value.
 * @param   e               Entry structure.
 * @param   value           New value for entry.
 * @param   type            New value's type.
 */
void            entry_update(Entry *e, const Value value, Type type) {

    if(e->type == STRING)
        free(e->value.string);

    e->type = type;

    if(type == STRING)
        e->value.string = strdup(value.string);
    else
        e->value.number = value.number;
}

/**
 * Dump entry.
 * @param   e               Entry structure.
 * @param   stream          File stream to write to.
 * @param   mode            Dump mode to use.
 */
void            entry_dump(Entry *e, FILE *stream, const DumpMode mode) {
    switch(mode)
    {
        case KEY:
            fprintf(stream,"%s\n",e->key);
            break;
        case VALUE:
            if(e->type == STRING)
                fprintf(stream,"%s\n",e->value.string);
            else
                fprintf(stream,"%"PRId64"\n",e->value.number);
            break;
        case KEY_VALUE:
            if(e->type == STRING)
                fprintf(stream,"%s\t%s\n",e->key,e->value.string);
            else
                fprintf(stream,"%s\t%"PRId64"\n",e->key,e->value.number);
            break;
        case VALUE_KEY:
            if(e->type == STRING)
                fprintf(stream,"%s\t%s\n",e->value.string,e->key);
            else
                fprintf(stream,"%"PRId64"\t%s\n",e->value.number,e->key);
            break;
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
