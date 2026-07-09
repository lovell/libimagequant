#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "libimagequant.h"

#define width 8
#define height 8

int main(void) {
    unsigned char pixels[width * height * 4];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int i = (y * width + x) * 4;
            pixels[i + 0] = (unsigned char)(x * 32);
            pixels[i + 1] = (unsigned char)(y * 32);
            pixels[i + 2] = (unsigned char)((x * 16 + y * 8) & 0xFF);
            pixels[i + 3] = 255;
        }
    }

    liq_attr *attr = liq_attr_create();
    if (!attr) {
        fprintf(stderr, "liq_attr_create failed\n");
        return 1;
    }

    liq_set_max_colors(attr, 16);
    liq_set_speed(attr, 1);
    liq_set_quality(attr, 0, 100);

    liq_image *image = liq_image_create_rgba(attr, pixels, width, height, 1.0);
    if (!image) {
        fprintf(stderr, "liq_image_create_rgba failed\n");
        liq_attr_destroy(attr);
        return 1;
    }

    liq_result *result = liq_quantize_image(attr, image);
    if (!result) {
        fprintf(stderr, "liq_quantize_image failed\n");
        liq_image_destroy(image);
        liq_attr_destroy(attr);
        return 1;
    }

    const liq_palette *pal = liq_get_palette(result);
    if (!pal) {
        fprintf(stderr, "liq_get_palette returned NULL\n");
        liq_result_destroy(result);
        liq_image_destroy(image);
        liq_attr_destroy(attr);
        return 1;
    }

    if (pal->count < 2) {
        fprintf(stderr, "palette too small: %u\n", pal->count);
        liq_result_destroy(result);
        liq_image_destroy(image);
        liq_attr_destroy(attr);
        return 1;
    }

    unsigned char out[width * height];
    liq_error err = liq_write_remapped_image(result, image, out, sizeof(out));
    if (err != LIQ_OK) {
        fprintf(stderr, "liq_write_remapped_image failed: %u\n", err);
        liq_result_destroy(result);
        liq_image_destroy(image);
        liq_attr_destroy(attr);
        return 1;
    }

    int counts[256] = {0};
    for (int i = 0; i < width * height; ++i) {
        unsigned int idx = out[i];
        if (idx >= pal->count) {
            fprintf(stderr, "index out of range: %u >= %u\n", idx, pal->count);
            liq_result_destroy(result);
            liq_image_destroy(image);
            liq_attr_destroy(attr);
            return 1;
        }
        counts[idx]++;
    }
    int distinct = 0;
    for (unsigned int i = 0; i < pal->count; ++i) if (counts[i]) distinct++;
    if (distinct < 2) {
        fprintf(stderr, "too few distinct palette indices: %d\n", distinct);
        liq_result_destroy(result);
        liq_image_destroy(image);
        liq_attr_destroy(attr);
        return 1;
    }

    for (unsigned int i = 0; i < width * height; i++) {
        unsigned int idx0 = out[i];
        liq_color c = pal->entries[idx0];
        unsigned char orig_r = pixels[i * 4 + 0];
        unsigned char orig_g = pixels[i * 4 + 1];
        unsigned char orig_b = pixels[i * 4 + 2];
        int dr = abs((int)c.r - (int)orig_r);
        int dg = abs((int)c.g - (int)orig_g);
        int db = abs((int)c.b - (int)orig_b);
        if (dr > 60 || dg > 60 || db > 60) {
            fprintf(stderr, "mapped colour too far from original: dr=%d dg=%d db=%d\n", dr, dg, db);
            liq_result_destroy(result);
            liq_image_destroy(image);
            liq_attr_destroy(attr);
            return 1;
        }
    }

    liq_result_destroy(result);
    liq_image_destroy(image);
    liq_attr_destroy(attr);
    return 0;
}
