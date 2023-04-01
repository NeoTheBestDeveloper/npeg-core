#include <criterion/hooks.h>
#include <stdlib.h>

#include <criterion/criterion.h>

#include "../src/npeg.h"

Test(img_rotation, test_pbm_img_rotate) {
    ImgResult res = img_read("./../../npeg/assets/ascii_pbm/small_sample1.pbm");
    Img *img = (Img *)res.data;

    img_rotate(img, 45, INTER_NONE);
    img_write(img, "res.pbm");
    img_free(img);
}
