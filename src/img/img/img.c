#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>

#include "_img.h"

#include "../../algorithms/algorithms.h"
#include "../../img/img/img_type.h"
#include "../img.h"
#include "../pbm/pbm.h"

static bool file_exists(const char* path) { return access(path, F_OK) == 0; }
static bool can_read(const char* path) { return access(path, R_OK) == 0; }
static bool can_write(const char* path) {
    if (0 == access(path, W_OK)) {
        return true;
    }
    return errno == 0 || errno == ENOENT;
}

static ImgResult result_new(void* data, ImgResultType type) {
    ImgResult result = {
        .data = data,
        .type = type,
    };
    return result;
}

ImgResult img_read(const char* path) {
    Img* res;
    if (!file_exists(path)) {
        return result_new(NULL, FILE_DOES_NOT_EXISTS);
    }

    if (!can_read(path)) {
        return result_new(NULL, DO_NOT_HAVE_READ_PERMISSIONS);
    }

    i32 fin = open(path, O_RDONLY);
    ImgType type = guess_img_type(fin);
    close(fin);

    switch (type) {
    case PBM:
        res = pbm_img_read(path);
        break;
    case PNG:
    case JPG:
    case PGM:
    case PAM:
    case PPM:
    case WEBP:
    case TIFF:
        return result_new(NULL, IMG_TYPE_IS_NOT_SUPPORTED_YET);
    case UNKNOWN_MAGIC:
    default:
        return result_new(NULL, UNKNOWN_IMG_TYPE);
    }
    return result_new(res, IMG_OK);
}

ImgResult img_write(const Img* img, const char* path) {
    if (!can_write(path)) {
        return result_new(NULL, DO_NOT_HAVE_WRITE_PERMISSIONS);
    }
    i32 fout = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);

    switch (img->type) {
    case PBM:
        pbm_img_write((const PbmImg*)img, fout);
        break;
    case PNG:
    case JPG:
    case PGM:
    case PAM:
    case PPM:
    case WEBP:
    case TIFF:
        return result_new(NULL, IMG_TYPE_IS_NOT_SUPPORTED_YET);
    case UNKNOWN_MAGIC:
    default:
        return result_new(NULL, UNKNOWN_IMG_TYPE);
    }
    close(fout);
    return result_new(NULL, IMG_OK);
}

Img* img_copy(const Img* img) {
    switch (img->type) {
    case PBM:
        return pbm_img_copy((const PbmImg*)img);
    case PNG:
    case JPG:
    case PGM:
    case PAM:
    case PPM:
    case WEBP:
    case TIFF:
    case UNKNOWN_MAGIC:
        break;
    }
    return NULL;
}

void img_free(Img* img) {
    switch (img->type) {
    case PBM:
    case PNG:
    case JPG:
    case PGM:
    case PAM:
    case PPM:
    case WEBP:
    case TIFF:
    case UNKNOWN_MAGIC:
        break;
    }

    for (u8 i = 0; i < img->channels_count; i++) {
        matrix_free(img->channels + i);
    }

    free(img->channels);
    free(img);
}

void img_rotate(Img* img, f32 degrees, Interpolation inter) {
    for (u8 i = 0; i < img->channels_count; i++) {
        matrix_rotate(img->channels + i, degrees, inter);
    }
}

void img_interpolate(Img* img, Interpolation inter) {
    for (u8 i = 0; i < img->channels_count; i++) {
        matrix_interpolate(img->channels + i, inter);
    }
}

inline i64 img_width(const Img* img) { return img->channels[0].width; }
inline i64 img_height(const Img* img) { return img->channels[0].height; }
inline u8 img_depth(const Img* img) { return img->depth; }
inline u8 img_channels_count(const Img* img) { return img->channels_count; }
inline ImgType img_type(const Img* img) { return img->type; }
