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
    mmap(NULL, (size_t) (sz), PROT_READ|PROT_WRITE, MAP_PRIVATE|_A_MAP_ANONYMOUS, -1, 0)

/*
    Get current system memory page size
*/

#define _a_mem__getpagesize() ((size_t) sysconf(_SC_PAGE_SIZE))

/*
    Round wished arena size by system aligned memory page size
*/

#define _a_mem__roundbsys(sz)                   \
    ((size_t) (sz) - ((size_t) (sz) % _a_mem__getpagesize()))

/*
    Check that page size is rounded by sys as require mumpal call
*/
#define _a_mem__is_roundbsys(sz)                \
    ((size_t) (sz) % _a_mem__getpagesize()) != 0 ? 0 : 1

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
};

void * ammap__allocprot(size_t pg_size);
int ammap__freeprot(void ** ptr, size_t pg_size);


#ifdef __cplusplus
}
#endif                                                              /* __cplusplus */

#endif                                                              /* A_MMAP */
