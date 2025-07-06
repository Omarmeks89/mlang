#ifndef A_MALLOC
#define A_MALLOC

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#define DEFAULT_PG_SIZE         8192ULL         /* default arena mem page size */
#define DEFAULT_PG_OFFSET_MASK  0x1FFFULL       /* default mask for receive obj offset */
#define DEFAULT_PG_OFFSET_BITS  12ULL           /* bits count for shift */

#define DEFAULT_MEM_CLASSES_CNT 64ULL           /* memory classes count */

#define DEFAULT_PTR_SIZE        8ULL            

/*
    --
*/
/* TODO: create macro that define mem_class by obj size */

void * allocate(size_t obj_size);
void deallocate(void * ptr);

#ifdef __cplusplus
}
#endif

#endif                                           /* A_MALLOC */
