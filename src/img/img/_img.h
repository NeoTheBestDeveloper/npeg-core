#pragma once
#define __IMG

#include "../../math/matrix.h"
#include "img_type.h"

#undef Img

typedef struct {
    Matrix* channels;
    char* path;
    ImgType type;
    u8 depth;
    u8 channels_count;
} Img;
