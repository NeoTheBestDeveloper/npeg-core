#include <criterion/hooks.h>
#include <stdio.h>
#include <stdlib.h>

#include <criterion/criterion.h>

#include "../src/npeg.h"

Test(img_reading, test_pbm_img_read) {
    ImgResult res = img_read("./../tests/imgs/ascii/small_sample1.pbm");
    Img *img = (Img *)res.data;
    img_write(img, "res1.pbm");
    img_free(img);
}
