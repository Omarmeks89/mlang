#ifndef MEM_CLASS_H
#define MEM_CLASS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/*
    Memory classificator - map object size on one of
    allowed memory classes defined in static table.
*/

enum _classification_error
{
    BIGOBJT =                                           -1,
    NULSIZE =                                           -2,
};

#define MAX_POSSIBLE_MEM_CLASSES                        64

#define _check_invalid_obj_size(os, err_type)           \
    if (os == 0) return (int) err_type

/*
    ...
*/
int get_obj_memclass_size(size_t obj_size);

#ifdef __cplusplus
}
#endif                                                  /* __cplusplus */

#endif                                                  /* MEM_CLASS_H */
