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

enum _class_error
{
    BIGOBJT =                                                   -1,
    NULSIZE =                                                   -2,
};

/*
    Specify default memory classe count.
*/

#define MAX_POSSIBLE_MEM_CLASSES                                64

#define _check_invalid_obj_size(os, err_type)                   \
    if ((os) == 0) return (int) err_type

/*
    Get memory class size to allocate rounded memory 
    space for object.
*/

int get_obj_memclass_size(size_t obj_size);

#ifdef __cplusplus
}
#endif                                                          /* __cplusplus */

#endif                                                          /* MEM_CLASS_H */
