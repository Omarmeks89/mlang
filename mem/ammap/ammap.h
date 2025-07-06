#ifndef A_MMAP
#define A_MMAP

#ifdef __cplusplus
extern "C" {
#endif

/*
    We use mmap() so we have to care about
    definitions like MAP_ANONYMOUS (MAP_ANON)
    ...
*/

#include <sys/mman.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

/*
    For handle error from errno.h (mmap | munmap processing)
*/
#include <string.h>

#if defined(MAP_ANON)
#  define _A_MAP_ANONYMOUS MAP_ANON
#elif defined(MAP_ANONYMOUS)
#  define _A_MAP_ANONYMOUS MAP_ANONYMOUS
#else
# define _A_MAP_ANONYMOUS                           0
#endif

/*
    Check MAP_FIXED_NOREPLACE to be care that we dont
    overwrite allocated region, got EEXIST error instead.
*/ 

#if defined(MAP_FIXED_NOREPLACE)
#  define _A_MAP_FIXED MAP_FIXED_NOREPLACE
#else
#  define _A_MAP_FIXED MAP_FIXED
#endif

/*
    Ensure that we don`t use tagged memory (pointers).
*/

#ifdef USE_MTAG
#  error "tagged memory is not supported"
#endif

#include <unistd.h>

/*
    Is a wrapper around 'mmap()' call, incapsulate mmap call
    settings and pointer type casts.
*/

#define _a_mem__allocprot(sz)                   \
    (void *) ((char *) mmap(NULL, (size_t) sz, PROT_READ|PROT_WRITE, MAP_PRIVATE|_A_MAP_ANONYMOUS|_A_MAP_FIXED, -1, 0))

/*
    Get current system memory page size
*/

#define _a_mem__getpagesize() ((size_t) sysconf(_SC_PAGE_SIZE))

/*
    Round wished arena size by system aligned memory page size
*/

#define _a_mem__roundbsys(sz)                   \
    ((size_t) sz - ((size_t) sz % _a_mem__getpagesize()))

/*
    Check that page size is rounded by sys as require mumpal call
*/
#define _a_mem__is_roundbsys(sz)                \
    ((size_t) sz % _a_mem__getpagesize()) != 0 ? 0 : 1

/* ==== public API ==== */

/*
    mem_processing_errors describe possible error types
    returned from ammap routines.
*/
enum _mem_processing_errors
{
    NOERR = 0,
    NULPT,
    NORND,
    NDEAL,
}
mem_processing_errors;

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
static inline void *
ammap__allocprot(size_t pg_size)
{
    /* https://man7.org/linux/man-pages/man2/mmap.2.html */
    void *mempage = NULL;

    if (pg_size == 0)
    {
#ifdef CLOX_MEM_DEBUG
        /* TODO: implement logger with sys mem buffer */
        printf("invalid page size: %d bytes\n", pg_size);
#endif
        return NULL;
    }

    pg_size = ammap__roundsz(pg_size);

#ifdef CLOX_MEM_DEBUG
    printf("page size to allocate: %d bytes\n", pg_size);
#endif

    mempage = _a_mem__allocprot(pg_size);
    if (mempage == NULL)
    { 
        /* log system error */
        printf("%s\n", strerror(errno));
    }

    return mempage;
}

/* \fn ammap_freeprot free protected memory region was
 * previously allocated. 
 *
 * Do not try to use ptr after freeprot call. */
static inline int 
ammap__freeprot(void * ptr, size_t pg_size)
{
    /* rnd_flag means mem page is rounded by system mem page size (t | f) */
    int rnd_flag = 0, munmap_stat = 0;

    if (ptr == NULL)
    {
        /* notify about null pointer */
#ifdef CLOX_MEM_DEBUG
        printf("impossible free null pointer: %p\n", ptr);
#endif
        return NULPT;
    }

    rnd_flag = _a_mem__is_roundbsys(pg_size);
    if (!rnd_flag)
    {
#ifdef CLOX_MEM_DEBUG
        printf("page size not rounded (%d)\n", pg_size);
#endif
        return NORND;
    }

    /*
         munmap return 0 if mem was deallocated or -1
    */
    munmap_stat = munmap(ptr, pg_size);
    if (munmap_stat < 0)
    {
        /* we have to break and notify about system error */
        printf("%s\n", strerror(errno));
        munmap_stat = NDEAL;
    }

    /* we have to set pointer as NULL to avoid dangling pointer using */
    ptr = NULL;

    return munmap_stat;
}

#ifdef __cplusplus
}
#endif

#endif
