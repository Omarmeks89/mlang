#include "amalloc.h"
#include "./ammap/ammap.h"

/* Module contains operation with memory arena */

typedef struct _mem_page
{
    struct _mem_page                    *prev;
    struct _mem_page                    *next;
    void                                *mem;
    unsigned char                       flags;
}
memobj__mempage;

/* service */
typedef struct
{
    /* 8 + 8, align = 16, place?? */
    memobj__mempage                     *first;
    memobj__mempage                     *last;
}
memobj__pg_meta;

/* service */
typedef struct
{
    /* each item by index is a own memory class descriptor */
    memobj__pg_meta                     mem_blocks[DEFAULT_MEM_CLASSES_CNT];
}
memobj__arena;

memobj__arena * init_arena(size_t arena_size);
memobj__pg_meta * init_pg_meta();
memobj__mempage * new_mem_pg();
static void * init_service_mem_region(size_t size);

/* ==== public interface ==== */

/* \fn allocate new object using obj_size as
 * memory class definition/
 *
 * Return:
 *  pointer on new allocated object */
void * 
allocate(size_t obj_size)
{
    return NULL;
}

/* \fn deallocate (free) memory from wished object.
 * If ptr == NULL or ptr address not exists in address table
 * this pointer will be ignored */
void
deallocate(void * ptr)
{
}

memobj__arena *
init_arena(size_t arena_size)
{
    void * arena_ptr = NULL;
    /*
     * TODO: implement
     * 1. size == 0 or less than default -> set default
     * 2. check returned pointer
     */

    arena_ptr = ammap__allocprot(arena_size);
    if (arena_ptr == NULL)
    {
        /* TODO: handle error, lookup error.h */
    }
    return NULL;
}
