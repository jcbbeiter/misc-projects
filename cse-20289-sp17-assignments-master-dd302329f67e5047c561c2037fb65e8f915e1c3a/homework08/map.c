/* map.c: separate chaining hash table */

#include "map.h"

/**
 * Create map data structure.
 * @param   capacity        Number of buckets in the hash table.
 * @param   load_factor     Maximum load factor before resizing.
 * @return  Allocated Map structure.
 */
Map *	        map_create(size_t capacity, double load_factor) {

    Map* newMap = malloc(sizeof(Map));
    if(newMap == NULL)
        return NULL;

    if(capacity > 0)
        newMap->capacity = capacity;
    else
        newMap->capacity = DEFAULT_CAPACITY;

    if(load_factor > 0)
        newMap->load_factor = load_factor;
    else
        newMap->load_factor = DEFAULT_LOAD_FACTOR;

    newMap->size = 0;

    newMap->buckets = calloc(newMap->capacity,sizeof(Entry));
    for(size_t i = 0; i < newMap->capacity; i++)
    {
        newMap->buckets[i].next = NULL;

    }
    return newMap;
}

/**
 * Delete map data structure.
 * @param   m               Map data structure.
 * @return  NULL.
 */
Map *	        map_delete(Map *m) {
    for(size_t i = 0; i < m->capacity; i++)
        entry_delete(m->buckets[i].next,true);
    free(m->buckets);
    free(m);
    return NULL;
}

/**
 * Insert or update entry into map data structure.
 * @param   m               Map data structure.
 * @param   key             Entry's key.
 * @param   value           Entry's value.
 * @param   type            Entry's value's type.
 */
void            map_insert(Map *m, const char *key, const Value value, Type type) {

    if((double)m->size/(double)m->capacity > m->load_factor)
        map_resize(m, m->capacity*2);

    Entry* search = map_search(m,key);
    if(search != NULL)
        entry_update(search,value,type);

    else
    {
        uint64_t hash = fnv_hash(key,strlen(key)) % m->capacity;
        Entry* prev = m->buckets+hash;

        prev->next = entry_create(key,value,prev->next,type);
        m->size++;
    }
}

/**
 * Search map data structure by key.
 * @param   m               Map data structure.
 * @param   key             Key of the entry to search for.
 * @param   Pointer to the entry with the specified key (or NULL if not found).
 */
Entry *         map_search(Map *m, const char *key) {
    uint64_t hash = fnv_hash(key,strlen(key)) % m->capacity;
    Entry* entry = m->buckets[hash].next;
    
    while(entry != NULL)
    {
        if(strcmp(entry->key,key) == 0)
            return entry;
        else
            entry = entry->next;
    }

    return NULL;
}

/**
 * Remove entry from map data structure with specified key.
 * @param   m               Map data structure.
 * @param   key             Key of the entry to remove.
 * return   Whether or not the removal was successful.
 */
bool            map_remove(Map *m, const char *key) {
    uint64_t hash = fnv_hash(key,strlen(key)) % m->capacity;
    Entry* prev = m->buckets+hash;
    
    while(prev->next != NULL)
    {
        if(strcmp(prev->next->key,key) == 0)
        {
            Entry* doomed = prev->next;
            prev->next = doomed->next;
            entry_delete(doomed,false);
            m->size--;
            return true;
        }
        else
            prev = prev->next;
    }
    return false;
}

/**
 * Dump all the entries in the map data structure.
 * @param   m               Map data structure.
 * @param   stream          File stream to write to.
 * @param   mode            Dump mode to use.
 */
void		map_dump(Map *m, FILE *stream, const DumpMode mode) {
    for(size_t i = 0; i < m->capacity; i++)
    {
        Entry* e = m->buckets+i;
        while(e->next != NULL)
        {
            entry_dump(e->next,stream,mode);
            e = e->next;
        }
    }
}

/**
 * Resize the map data structure.
 * @param   m               Map data structure.
 * @param   new_capacity    New capacity for the map data structure.
 */
void            map_resize(Map *m, size_t new_capacity) {
    Entry* newBuckets = calloc(new_capacity,sizeof(Entry));
    
    for(size_t i = 0; i < m->capacity; i++)
    {
        for(Entry* old = m->buckets[i].next; old != NULL;  )
        {
            uint64_t hash = fnv_hash(old->key,strlen(old->key)) % new_capacity;
            Entry* newPrev = newBuckets+hash;
            while(newPrev->next != NULL)
            {
                newPrev = newPrev->next;
            }
            newPrev->next = old;
            old = old->next;
            newPrev->next->next = NULL;
        }
    }
    free(m->buckets);
    m->buckets = newBuckets;
    m->capacity = new_capacity;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
