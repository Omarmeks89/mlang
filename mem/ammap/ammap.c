#include "ammap.h"

/* \fn ammap__roundsz round size of wished block size
 * made them page-aligned */
static inline size_t
ammap__roundsz(size_t pg_size)
{
    size_t sys_mempg_size = _a_mem__getpagesize();

    if (pg_size < sys_mempg_size)
        return sys_mempg_size;

    return _a_mem__roundbsys(pg_size);
}

/* \fn ammap__allocprot allocate protected (not visible for
 * childs and other processes) memory region. */
void *
ammap__allocprot(size_t pg_size)
{
    /* https://man7.org/linux/man-pages/man2/mmap.2.html */
    void *mempage = NULL;

    pg_size = ammap__roundsz(pg_size);

#ifdef CLOX_MEM_DEBUG
    printf("[DEBUG] arena size to allocate: %ld bytes\n", pg_size);
#endif

    mempage = _a_mem__allocprot(pg_size);
    if ((mempage == NULL) || (mempage == MAP_FAILED))
    { 
        /* log system error */
        printf("-- %s\n", strerror(errno));
        return NULL;
    }

    return mempage;
}

/* \fn ammap_freeprot free protected memory region was
 * previously allocated. 
 *
 * Do not try to use ptr after freeprot call. */
int 
ammap__freeprot(void ** ptr, size_t pg_size)
{
    /* rnd_flag means mem page is rounded by system mem page size (t | f) */
    int rnd_flag = 0, munmap_stat = 0;

    rnd_flag = _a_mem__is_roundbsys(pg_size);
    if (!rnd_flag)
    {
#ifdef CLOX_MEM_DEBUG
        printf("[DEBUG] arena size not rounded (%ld)\n", pg_size);
#endif
        return NORND;
    }

    /* munmap return 0 if mem was deallocated or -1 */
    munmap_stat = munmap(*ptr, pg_size);
    if (munmap_stat < 0)
    {
        /* we have to notify about system error */
        printf("%s\n", strerror(errno));
        munmap_stat = NDEAL;
    }

    *ptr = NULL;

    return munmap_stat;
}

