#include <stdlib.h>

#include "../mem/mem_class.h"

/*
    Is rounded by pointer size (64 bit).
*/
static const size_t _mem_classes[MAX_POSSIBLE_MEM_CLASSES] = {
    8, 16, 24, 32, 40, 48, 56, 64,
    80, 96, 112, 128, 144, 160, 176, 192,
    224, 256, 288, 320, 352, 384, 416, 448,
    512, 576, 640, 704, 768, 832, 896, 960,
    1088, 1216, 1344, 1472, 1600, 1728, 1856, 1984,
    2240, 2496, 2752, 3008, 3264, 3520, 3776, 4032,
    4544, 5056, 5568, 6080, 6592, 7104, 7616, 8128, 
    9152, 10176, 11200, 12224, 13248, 14272, 15296, 16320
};

static int
get_memclass_idx(size_t obj_size)
{
    const int max_arr_pos = 63;
    int i = 0, j = 1;

    if (obj_size <= _mem_classes[i]) return i;
    for (; j <= max_arr_pos; i++, j++)
    {
        if ((_mem_classes[i] < obj_size) && (obj_size <= _mem_classes[j]))
            return j;
    }

    return BIGOBJT;
}

static int
get_obj_memclass_pos(size_t obj_size)
{
    _check_invalid_obj_size(obj_size, NULSIZE);
    return get_memclass_idx(obj_size);
}

int
get_obj_memclass_size(size_t obj_size)
{
    int idx = 0;

    idx = get_obj_memclass_pos(obj_size);
    if ((idx == BIGOBJT) || (idx == NULSIZE)) return idx;

    return (int) _mem_classes[idx];
}
