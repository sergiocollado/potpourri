#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/* FreeRTOS+FAT includes. */
#include "ff_headers.h"
#include "ff_stdio.h"
#include "ff_ramdisk.h"


#define MAX_BRIGHTNESS 255

// C99 doesn't define M_PI (GNU-C99 does)
#define M_PI 3.14159265358979323846264338327

/*
 * Loading part taken from
 * http://www.vbforums.com/showthread.php?t=261522
 * BMP info:
 * http://en.wikipedia.org/wiki/BMP_file_format
 *
 * Note: the magic number has been removed from the bmpfile_header_t
 * structure since it causes alignment problems
 *     bmpfile_magic_t should be written/read first
 * followed by the
 *     bmpfile_header_t
 * [this avoids compiler-specific alignment pragmas etc.]
 */

typedef struct {
    uint8_t magic[2];
} bmpfile_magic_t;

typedef struct {
    uint32_t filesz;
    uint16_t creator1;
    uint16_t creator2;
    uint32_t bmp_offset;
} bmpfile_header_t;

typedef struct {
    uint32_t header_sz;
    int32_t  width;
    int32_t  height;
    uint16_t nplanes;
    uint16_t bitspp;
    uint32_t compress_type;
    uint32_t bmp_bytesz;
    int32_t  hres;
    int32_t  vres;
    uint32_t ncolors;
    uint32_t nimpcolors;
} bitmap_info_header_t;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t nothing;
} rgb_t;

// Use short int instead `unsigned char' so that we can
// store negative values.
typedef short int pixel_t;

pixel_t *load_bmp(const char *filename,
                  bitmap_info_header_t *bitmapInfoHeader); 

bool save_bmp(const char *filename, const bitmap_info_header_t *bmp_ih,
              const pixel_t *data); 
			  

/*
 * gaussianFilter:
 * http://www.songho.ca/dsp/cannyedge/cannyedge.html
 * determine size of kernel (odd #)
 * 0.0 <= sigma < 0.5 : 3
 * 0.5 <= sigma < 1.0 : 5
 * 1.0 <= sigma < 1.5 : 7
 * 1.5 <= sigma < 2.0 : 9
 * 2.0 <= sigma < 2.5 : 11
 * 2.5 <= sigma < 3.0 : 13 ...
 * kernelSize = 2 * int(2*sigma) + 3;
 */
void gaussian_filter(const pixel_t *in, pixel_t *out,
                     const int nx, const int ny, const float sigma);

/*
 * Links:
 * http://en.wikipedia.org/wiki/Canny_edge_detector
 * http://www.tomgibara.com/computer-vision/CannyEdgeDetector.java
 * http://fourier.eng.hmc.edu/e161/lectures/canny/node1.html
 * http://www.songho.ca/dsp/cannyedge/cannyedge.html
 *
 * Note: T1 and T2 are lower and upper thresholds.
 */
pixel_t *canny_edge_detection(const pixel_t *in,
                              const bitmap_info_header_t *bmp_ih,
                              const int tmin, const int tmax,
                              const float sigma);
							  
/* example.
int main(const int argc, const char ** const argv)
{
    if (argc < 2) {
        printf("Usage: %s image.bmp\n", argv[0]);
        return 1;
    }

    static bitmap_info_header_t ih;
    const pixel_t *in_bitmap_data = load_bmp(argv[1], &ih);
    if (in_bitmap_data == NULL) {
        fprintf(stderr, "main: BMP image not loaded.\n");
        return 1;
    }

    printf("Info: %d x %d x %d\n", ih.width, ih.height, ih.bitspp);

    const pixel_t *out_bitmap_data =
        canny_edge_detection(in_bitmap_data, &ih, 40, 80, 1.0);
    if (out_bitmap_data == NULL) {
        fprintf(stderr, "main: failed canny_edge_detection.\n");
        return 1;
    }

    if (save_bmp("out.bmp", &ih, out_bitmap_data)) {
        fprintf(stderr, "main: BMP image not saved.\n");
        return 1;
    }

    free((pixel_t*)in_bitmap_data);
    free((pixel_t*)out_bitmap_data);
    return 0;
}
*/
