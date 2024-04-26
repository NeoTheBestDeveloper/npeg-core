#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../src/npeg.h"
#include "assets.h"

void setup_ascii_pbm(void) {
    perror("");
    i32 fd = open("img.pbm", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    printf("%d\n", fd);
    perror("");
    for (u8 i = 0; i < 1; ++i) {
        write(fd, &pbm_ascii_img[i], IMG_WIDTH * IMG_HEIGHT);
    }
    perror("");
    close(fd);
    perror("");
}

void teardown_img(void) { remove("img.pbm"); }

Test(img_reading, test_img_reading, .init = setup_ascii_pbm, .fini = teardown_img) {
    ImgResult res = img_read("img.pbm");
    Img* img = (Img*)res.data;
    img_free(img);
}
