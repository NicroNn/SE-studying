#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

// Returns true if specified coordinates are inside the object
bool hit_test(float x, float y, float z){
    return (x * x * x * x - 2 * x * x * x + 4 * (y * y + z * z)) <= 0;
}

// Returns array of 6 values:
// x_min, x_max, y_min, y_max, z_min, z_max
const float* get_axis_range(){
    static const float range[6] = {0, 2, -0.65, 0.65, -0.65, 0.65};
    return range;
}

#ifdef __cplusplus
}
#endif
