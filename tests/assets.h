#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "types.h"

#define IMG_WIDTH 6
#define IMG_HEIGHT 10


void dump_u8_img(u8** img, u8 channels_count, const char* path) {}

static u8 black_white_img_data[] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
                                    0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
                                    1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static u8 pbm_ascii_img[] = "P1\n6 10\n000010000010000010000010000010000010100010011100000000000000";
static u8 pbm_raw_img[] = {'P', '4', '\n', '6', ' ', '1', '0', '\n', 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
                           0,   1,   0,    0,   0,   0,   0,   1,    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0,
                           0,   0,   1,    0,   0,   1,   1,   1,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
