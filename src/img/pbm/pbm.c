#include <ctype.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pbm.h"

#include "../../img/img.h"
#include "../../math/matrix.h"

#define IMG_HEADER_BUFFER_SIZE (64)
#define BLOCK_SIZE (16 * 1024)

static inline u8 digit_to_chr(u8 digit) { return digit + 48; }
static inline u8 chr_to_digit(u8 digit) { return digit - 48; }

static bool is_ascii(const char* magic) { return 0 == strncmp(magic, "P1", 2); }

static void read_data(PbmImg* img, i32 fin) {
    i64 width, height;

    u8 line[IMG_HEADER_BUFFER_SIZE] = {0};
    i64 line_top = 0;
    u8 whitespaces_read_count = 0;

    while (whitespaces_read_count != 2) {
        read(fin, line + line_top, 1);
        if (isspace(line[line_top])) {
            whitespaces_read_count++;
        }
        line_top++;
    }

    sscanf(line, "%li %li", &width, &height);

    img->img.channels = (Matrix*)malloc(sizeof(Matrix));
    img->img.channels[0] = matrix_new(width, height, U8_MATRIX, false);

    u8** img_data = (u8**)img->img.channels[0].data;

    u8 buf[BLOCK_SIZE] = {0};
    i64 buf_size = 0;
    i64 i = 0, j = 0;

    while ((buf_size = read(fin, buf, BLOCK_SIZE))) {
        for (i64 buf_top = 0; buf_top < buf_size; ++buf_top) {
            if (!isspace(buf[buf_top])) {
                if (j == width) {
                    j = 0;
                    i++;
                }
                img_data[i][j++] = chr_to_digit(buf[buf_top]);
            }
        }
    }
}

Img* pbm_img_read(const char* path) {
    PbmImg* new_img = (PbmImg*)malloc(sizeof *new_img);

    i32 fin = open(path, O_RDONLY);

#ifdef _WIN64
    char magic[4] = {0};
    read(fin, magic, 3);
    if (magic[2] == '\r') {
        read(fin, magic + 3, 1);
    }
#else
    char magic[3] = {0};
    read(fin, magic, 3);
#endif


    new_img->is_ascii = is_ascii(magic);
    new_img->img.depth = 1;
    new_img->img.channels_count = 1;
    new_img->img.type = PBM;

    read_data(new_img, fin);
    close(fin);

    return &new_img->img;
}

static void write_magic(const PbmImg* img, i32 fout) {
    if (img->is_ascii) {
        write(fout, "P1\n", 3);
    } else {
        write(fout, "P4\n", 3);
    }
}

static void write_size(const PbmImg* img, i32 fout) {
    char header_buf[IMG_HEADER_BUFFER_SIZE] = {0};
    sprintf(header_buf, "%li %li\n", img->img.channels->width, img->img.channels->height);
    write(fout, header_buf, strlen(header_buf));
}

static void write_data(const PbmImg* img, i32 fout) {
    u8 buf[BLOCK_SIZE];
    u64 buf_top = 0;

    u8** data = (u8**)img->img.channels[0].data;
    i64 width = img_width((const Img*)img);
    i64 height = img_height((const Img*)img);

    for (i64 i = 0; i < height; ++i) {
        for (i64 j = 0; j < width; ++j) {
            if (buf_top == BLOCK_SIZE) {
                write(fout, buf, buf_top);
                buf_top = 0;
            }
            buf[buf_top++] = digit_to_chr(data[i][j]);
            buf[buf_top++] = ' ';
        }
    }

    if (buf_top) {
        write(fout, buf, buf_top);
    }
}

void pbm_img_write(const PbmImg* img, i32 fout) {
    write_magic(img, fout);
    write_size(img, fout);
    write_data(img, fout);
}

Img* pbm_img_copy(const PbmImg* img) {
    PbmImg* new_img = (PbmImg*)malloc(sizeof *new_img);
    memcpy(new_img, img, sizeof *new_img);

    new_img->img.channels = (Matrix*)malloc(sizeof *img->img.channels);
    new_img->img.channels[0] = matrix_copy(img->img.channels + 0);

    return &new_img->img;
}
