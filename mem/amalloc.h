#ifndef A_MALLOC
#define A_MALLOC

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/*
    Specify default page size equal to 8192 bytes
*/

#define DEFAULT_PG_SIZE                         0x2000ULL         /* default arena mem page size */

/*
    Specify default arena size as 64MB.
*/

#define DEFAULT_ARENA_SIZE                      0x04000000ULL

/*
    Macro for destroy arena.
*/

#define amalloc_destroy_arena(a, a_size)        \
    destroy_arena(&(a), a_size)

/*
    Use this pointer type on arena object instead of direct reference.
*/

typedef struct _memobj_arena * memobj__arena;

/*
    Allocations for internal arena objects.
*/

void * allocate(size_t obj_size);
void deallocate(void * ptr);

void destroy_arena(memobj__arena * arena, size_t arena_size);

/*
    Init arena routine.
*/

memobj__arena init_arena(size_t arena_size);

#ifdef __cplusplus
}
#endif

#endif                                           /* A_MALLOC */
