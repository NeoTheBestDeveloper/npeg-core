#ifndef IMG_TYPE_H
#define IMG_TYPE_H

#include "types.h"

typedef enum {
    UNKNOWN_MAGIC = 0,
    PNG = 1,
    JPG = 2,
    PAM = 3,
    PBM = 4,
    PGM = 5,
    PPM = 6,
    WEBP = 7,
    TIFF = 8,
} ImgType;

/* Return UNKNOWN (0) if format is unknown. */
ImgType guess_img_type(i32 fin);
const char *img_type_to_text(ImgType type);

#endif // !IMG_TYPE_H
