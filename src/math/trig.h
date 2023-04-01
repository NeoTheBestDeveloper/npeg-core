#pragma once

#include "types.h"

#define PI 3.141592653589793f
#define PI_2_POW 9.869604401089358f
#define PI_DEVIDED_BY_180 0.017453292519943295f

static inline f32 deg_to_rad(f32 degrees) { return degrees * PI_DEVIDED_BY_180; }
