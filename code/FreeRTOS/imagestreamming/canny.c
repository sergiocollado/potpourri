#include "canny.h"


pixel_t *load_bmp(const char *filename,
                  bitmap_info_header_t *bitmapInfoHeader)
{
    FILE *filePtr = ff_fopen(filename, "r");
    if (filePtr == NULL) {
        printf("error fopen() ");
        return NULL;
    }

    bmpfile_magic_t mag;
    if (ff_fread(&mag, sizeof(bmpfile_magic_t), 1, filePtr) != 1) {
		printf("\nerror when reading a file %s ,%d", __FUNCTION__, __LINE__);
		if (ff_fclose(filePtr) == -1) { printf("\nError when closing a file"); }
        return NULL;
    }

    // verify that this is a bmp file by check bitmap id
    // warning: dereferencing type-punned pointer will break
    // strict-aliasing rules [-Wstrict-aliasing]
    if (*((uint16_t*)mag.magic) != 0x4D42) {
        printf("Not a BMP file: magic=%c%c\n",
                mag.magic[0], mag.magic[1]);
        if(ff_fclose(filePtr)==-1) { printf("\nError when closing a file"); }
        return NULL;
    }

    bmpfile_header_t bitmapFileHeader; // our bitmap file header
    // read the bitmap file header
    if (ff_fread(&bitmapFileHeader, sizeof(bmpfile_header_t),
              1, filePtr) != 1) {
		printf("\nerror when reading a file %s ,%d", __FUNCTION__, __LINE__);
		 if(ff_fclose(filePtr) == -1) { printf("\nError when closing a file"); }
        return NULL;
    }

    // read the bitmap info header
    if (ff_fread(bitmapInfoHeader, sizeof(bitmap_info_header_t),
              1, filePtr) != 1) {
		printf("\nerror when reading a file %s ,%d", __FUNCTION__, __LINE__);
		if(ff_fclose(filePtr) == -1) { printf("\nError when closing a file"); }
        return NULL;
    }

    if (bitmapInfoHeader->compress_type != 0)
        printf("Warning, compression is not supported.\n");

    // move file point to the beginning of bitmap data
    if (ff_fseek(filePtr, bitmapFileHeader.bmp_offset, SEEK_SET)) {
        if(ff_fclose(filePtr)==-1) { printf("\nError when closing"); }
        return NULL;
    }

    // allocate enough memory for the bitmap image data
    pixel_t *bitmapImage = pvPortMalloc(bitmapInfoHeader->bmp_bytesz *
                                  sizeof(pixel_t));

    // verify memory allocation
    if (bitmapImage == NULL) {
        if(ff_fclose(filePtr)==-1) { printf("\nError when closing"); }
        return NULL;
    }

    // read in the bitmap image data
    size_t pad, count=0;
    unsigned char c;
    pad = 4*ceil(bitmapInfoHeader->bitspp*bitmapInfoHeader->width/32.) - bitmapInfoHeader->width;
    for(int32_t i=0; i<bitmapInfoHeader->height; i++){
	    for(int32_t j=0; j<bitmapInfoHeader->width; j++){
		    if (ff_fread(&c, sizeof(unsigned char), 1, filePtr) != 1) {
				printf("\nerror when reading a file %s ,%d", __FUNCTION__ , __LINE__);
			    if(ff_fclose(filePtr)==-1) { printf("\nError when closing a file"); }
			    return NULL;
		    }
		    bitmapImage[count++] = (pixel_t) c;
	    }
	    ff_fseek(filePtr, pad, SEEK_CUR);
    }

    // If we were using unsigned char as pixel_t, then:
    // fread(bitmapImage, 1, bitmapInfoHeader->bmp_bytesz, filePtr);

    // close file and return bitmap image data
    if(ff_fclose(filePtr)==-1) { printf("\nError when closing a file"); }
    return bitmapImage;
}


// Return: true on error.
bool save_bmp(const char *filename, const bitmap_info_header_t *bmp_ih,
              const pixel_t *data)
{
    FILE* filePtr = ff_fopen(filename, "w+");
    if (filePtr == NULL)  {printf("error when opening a file: %s, %d", __FUNCTION__, __LINE__); return true;}

    bmpfile_magic_t mag = {{0x42, 0x4d}};
    if (ff_fwrite(&mag, sizeof(bmpfile_magic_t), 1, filePtr) != 1) {
		printf("error when writting the file to save1 %s",filename);
        if(ff_fclose(filePtr)==-1) { printf("\nError when closing a file"); }
        return true;
    }

    const uint32_t offset = sizeof(bmpfile_magic_t) +
                            sizeof(bmpfile_header_t) +
                            sizeof(bitmap_info_header_t) +
                            ((1U << bmp_ih->bitspp) * 4);

    const bmpfile_header_t bmp_fh = {
        .filesz = offset + bmp_ih->bmp_bytesz,
        .creator1 = 0,
        .creator2 = 0,
        .bmp_offset = offset
    };

    if (ff_fwrite(&bmp_fh, sizeof(bmpfile_header_t), 1, filePtr) != 1) {
		printf("error when writting the file to save2 %s", filename);
        if(ff_fclose(filePtr)==-1) { printf("\nError when closing a file"); }
        return true;
    }
    if (ff_fwrite(bmp_ih, sizeof(bitmap_info_header_t), 1, filePtr) != 1) {
		printf("error when writting the file to save3 %s", filename);
		if (ff_fclose(filePtr) == -1) { printf("\nError when closing a file"); }
        return true;
    }

    // Palette
    for (size_t i = 0; i < (1U << bmp_ih->bitspp); i++) {
        const rgb_t color = {(uint8_t)i, (uint8_t)i, (uint8_t)i};
        if (ff_fwrite(&color, sizeof(rgb_t), 1, filePtr) != 1) {
			printf("error when writting the file to save4 %s", filename);
			if (ff_fclose(filePtr) == -1) { printf("\nError when closing a file"); }
            return true;
        }
    }

    // We use int instead of uchar, so we can't write img
    // in 1 call any more.
    // fwrite(data, 1, bmp_ih->bmp_bytesz, filePtr);

    // Padding: http://en.wikipedia.org/wiki/BMP_file_format#Pixel_storage
    size_t pad = 4*ceil(bmp_ih->bitspp*bmp_ih->width/32.) - bmp_ih->width;
    unsigned char c;
    for(int32_t i=0; i < bmp_ih->height; i++) {
	    for(int32_t j=0; j < bmp_ih->width; j++) {
		    c = (unsigned char) data[j + bmp_ih->width*i];
		    if (ff_fwrite(&c, sizeof(char), 1, filePtr) != 1) {
				printf("error when writting the file to save5 %s", filename);
			    if(ff_fclose(filePtr)==-1) { printf("\nError when closing a file"); }
			    return true;
		    }
	    }
	    c = 0;
	    for(size_t j=0; j<pad; j++)
		    if (ff_fwrite(&c, sizeof(char), 1, filePtr) != 1) {
				printf("error when writting the file to save6 %s", filename);
				if (ff_fclose(filePtr) == -1) { printf("\nError when closing a file"); }
			    return true;
		    }
    }

	if (ff_fclose(filePtr) == -1) { printf("\nError when closing a file"); }

	//printf("save_bmp: %s", filename);
    return false;
}

// if normalize is true, map pixels to range 0..MAX_BRIGHTNESS
void convolution(const pixel_t *in, pixel_t *out, const float *kernel,
                 const int nx, const int ny, const int kn,
                 const bool normalize)
{
    assert(kn % 2 == 1);
    assert(nx > kn && ny > kn);
    const int khalf = kn / 2;
    float min = FLT_MAX, max = -FLT_MAX;
	float maxmin = 0;

    if (normalize)
        for (int m = khalf; m < nx - khalf; m++)
            for (int n = khalf; n < ny - khalf; n++) {
                float pixel = 0.0;
                size_t c = 0;
                for (int j = -khalf; j <= khalf; j++)
                    for (int i = -khalf; i <= khalf; i++) {
                        pixel += in[(n - j) * nx + m - i] * kernel[c];
                        c++;
                    }
                if (pixel < min)
                    min = pixel;
                if (pixel > max)
                    max = pixel;
                }
	maxmin = max - min; 

    for (int m = khalf; m < nx - khalf; m++)
        for (int n = khalf; n < ny - khalf; n++) {
            float pixel = 0.0;
            size_t c = 0;
            for (int j = -khalf; j <= khalf; j++)
                for (int i = -khalf; i <= khalf; i++) {
                    pixel += in[(n - j) * nx + m - i] * kernel[c];
                    c++;
                }

            if (normalize)
                pixel = MAX_BRIGHTNESS * (pixel - min) / (maxmin);
            out[n * nx + m] = (pixel_t)pixel;
        }
}

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
                     const int nx, const int ny, const float sigma)
{
    const int n = 2 * (int)(2 * sigma) + 3;
    const float mean = (float)floor(n / 2.0);
    float *kernel= pvPortMalloc(n*n*sizeof(float)); // variable length array

    //printf("gaussian_filter: kernel size %d, sigma=%g\n", n, sigma);

    size_t c = 0;
	int numerator = 1 / (2 * M_PI * sigma * sigma);
	double ifactor = 0;
	for (int i = 0; i < n; i++)
	{   //only is needed to be calculated once per outer loop
		ifactor = pow((i - mean) / sigma, 2.0); 
		for (int j = 0; j < n; j++) {
			kernel[c] = exp(-0.5 * (ifactor +
				pow((j - mean) / sigma, 2.0)))* numerator;
			c++;
		}
	}

    convolution(in, out, kernel, nx, ny, n, true);
	vPortFree(kernel);
}


pixel_t *canny_edge_detection(const pixel_t *in,
                              const bitmap_info_header_t *bmp_ih,
                              const int tmin, const int tmax,
                              const float sigma)
{
    const int nx = bmp_ih->width;
    const int ny = bmp_ih->height;

    pixel_t *G = pvPortMalloc(nx * ny * sizeof(pixel_t), 1); //calloc
    pixel_t *after_Gx = pvPortMalloc(nx * ny * sizeof(pixel_t), 1); //calloc
    pixel_t *after_Gy = pvPortMalloc(nx * ny * sizeof(pixel_t), 1); //calloc
    pixel_t *nms = pvPortMalloc(nx * ny * sizeof(pixel_t), 1); //calloc
    pixel_t *out = pvPortMalloc(bmp_ih->bmp_bytesz * sizeof(pixel_t));

    if (G == NULL || after_Gx == NULL || after_Gy == NULL ||
        nms == NULL || out == NULL) {
        fprintf(stderr, "canny_edge_detection:"
                " Failed memory allocation(s).\n");
        exit(1);
    }

    gaussian_filter(in, out, nx, ny, sigma);

    const float Gx[] = {-1, 0, 1,
                        -2, 0, 2,
                        -1, 0, 1};

    convolution(out, after_Gx, Gx, nx, ny, 3, false);

    const float Gy[] = { 1, 2, 1,
                         0, 0, 0,
                        -1,-2,-1};

    convolution(out, after_Gy, Gy, nx, ny, 3, false);

    for (int i = 1; i < nx - 1; i++)
        for (int j = 1; j < ny - 1; j++) {
            const int c = i + nx * j;
            // G[c] = abs(after_Gx[c]) + abs(after_Gy[c]);
            G[c] = (pixel_t)hypot(after_Gx[c], after_Gy[c]);
        }

    // Non-maximum suppression, straightforward implementation.
    for (int i = 1; i < nx - 1; i++)
        for (int j = 1; j < ny - 1; j++) {
            const int c = i + nx * j;
            const int nn = c - nx;
            const int ss = c + nx;
            const int ww = c + 1;
            const int ee = c - 1;
            const int nw = nn + 1;
            const int ne = nn - 1;
            const int sw = ss + 1;
            const int se = ss - 1;

            const float dir = (float)(fmod(atan2(after_Gy[c],
                                                 after_Gx[c]) + M_PI,
                                           M_PI) / M_PI) * 8;

            if (((dir <= 1 || dir > 7) && G[c] > G[ee] &&
                 G[c] > G[ww]) || // 0 deg
                ((dir > 1 && dir <= 3) && G[c] > G[nw] &&
                 G[c] > G[se]) || // 45 deg
                ((dir > 3 && dir <= 5) && G[c] > G[nn] &&
                 G[c] > G[ss]) || // 90 deg
                ((dir > 5 && dir <= 7) && G[c] > G[ne] &&
                 G[c] > G[sw]))   // 135 deg
                nms[c] = G[c];
            else
                nms[c] = 0;
        }

    // Reuse array
    // used as a stack. nx*ny/2 elements should be enough.
    int *edges = (int*) after_Gy;
    memset(out, 0, sizeof(pixel_t) * nx * ny);
    memset(edges, 0, sizeof(pixel_t) * nx * ny);

    // Tracing edges with hysteresis . Non-recursive implementation.
    size_t c = 1;
    for (int j = 1; j < ny - 1; j++)
        for (int i = 1; i < nx - 1; i++) {
            if (nms[c] >= tmax && out[c] == 0) { // trace edges
                out[c] = MAX_BRIGHTNESS;
                int nedges = 1;
                edges[0] = c;

                do {
                    nedges--;
                    const int t = edges[nedges];

                    int nbs[8]; // neighbours
                    nbs[0] = t - nx;     // nn
                    nbs[1] = t + nx;     // ss
                    nbs[2] = t + 1;      // ww
                    nbs[3] = t - 1;      // ee
                    nbs[4] = nbs[0] + 1; // nw
                    nbs[5] = nbs[0] - 1; // ne
                    nbs[6] = nbs[1] + 1; // sw
                    nbs[7] = nbs[1] - 1; // se

                    for (int k = 0; k < 8; k++)
                        if (nms[nbs[k]] >= tmin && out[nbs[k]] == 0) {
                            out[nbs[k]] = MAX_BRIGHTNESS;
                            edges[nedges] = nbs[k];
                            nedges++;
                        }
                } while (nedges > 0);
            }
            c++;
        }

	vPortFree(after_Gx);
	vPortFree(after_Gy);
	vPortFree(G);
	vPortFree(nms);

    return out;
}
