#include "amalloc.h"
#include "./ammap/ammap.h"
#include "./mem_class.h"

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
typedef struct _memobj__pg_meta
{
    /* 8 + 8, align = 16, place?? */
    memobj__mempage                     *first;
    memobj__mempage                     *last;
}
memobj__pg_meta;

/* service */
struct _memobj_arena
{
    /* each item by index is a own memory class descriptor */
    memobj__pg_meta                     mem_blocks[MAX_POSSIBLE_MEM_CLASSES];
};


memobj__arena init_arena(size_t arena_size);
memobj__pg_meta * init_pg_meta();
memobj__mempage * new_mem_pg();

/* ==== public interface ==== */

/* \fn allocate new object using obj_size as
 * memory class definition/
 *
 * Return:
 *  pointer on new allocated object */
void * 
allocate(size_t obj_size)
{
    int mem_class = 0;

    mem_class = get_obj_memclass_size(obj_size);
    if (mem_class == NULSIZE) return NULL;

    if (mem_class == BIGOBJT)
    {
        /* ... */
        return NULL;
    }

    return NULL;
}

/* \fn deallocate (free) memory from wished object.
 * If ptr == NULL or ptr address not exists in address table
 * this pointer will be ignored */
void
deallocate(void * ptr)
{
}

memobj__arena
init_arena(size_t arena_size)
{
    void * arena_ptr = NULL;

    if (arena_size < DEFAULT_ARENA_SIZE)
        arena_size = (size_t) DEFAULT_ARENA_SIZE;

    arena_ptr = ammap__allocprot(arena_size);
    if (arena_ptr == NULL) return NULL;
    
    /* init arena */

    return (memobj__arena) arena_ptr;
}

/* \fn destroy_arena destroy main arena if needed. */
void
destroy_arena(memobj__arena * arena, size_t arena_size)
{
    if ((arena == NULL) || (*arena == NULL)) return;
    ammap__freeprot((void **) arena, arena_size);
}

