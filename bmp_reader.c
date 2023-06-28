#include <stdio.h>
#include <stdlib.h>
#include "bmp_reader.h"

BMPFile* loadBMPFile(char* fname) {
    FILE* fp = fopen(fname, "r");
    if(!fp) {
        printf("Can't load file \'%s\'\n", fname);
        exit(0);
    }
    BMPFile* bmp_file = (BMPFile*)malloc(sizeof(BMPFile));
    fread(&bmp_file->bhdr, sizeof(BMPHeader), 1, fp);
    fread(&bmp_file->dhdr, sizeof(DIBHeader), 1, fp);

    bmp_file->data = (unsigned char*)malloc(bmp_file->dhdr.data_size); // memory for info of pixels
    fseek(fp, bmp_file->bhdr.pixel_offset, SEEK_SET); // set reading position of the file
    fread(bmp_file->data, bmp_file->dhdr.data_size, 1, fp); // set data of pixels

    fclose(fp);
    return bmp_file;
}

void freeBMPFile(BMPFile* bmp_file) {
    if (bmp_file) {
        free(bmp_file);
    }
}

void printBMPHeaders(BMPFile* bmp_file) {
    printf(
       "ID[2] = %c%c\n"
       "file_size = %d\n"
       "pixel_offset = %d\n",
       bmp_file->bhdr.ID[0],
       bmp_file->bhdr.ID[1],
       bmp_file->bhdr.file_size,
       bmp_file->bhdr.pixel_offset
    );
    printf(
       "header_size = %d\n"
       "width = %d\n"
       "height = %d\n"
       "color_planes = %d\n"
       "bits_per_pixel = %d\n"
       "compression = %d\n"
       "data_size = %d\n"
       "pheight = %d\n"
       "colors_count = %d\n"
       "imp_colors_count = %d\n",
       bmp_file->dhdr.header_size,
       bmp_file->dhdr.width,
       bmp_file->dhdr.height,
       bmp_file->dhdr.color_planes,
       bmp_file->dhdr.bits_per_pixel,
       bmp_file->dhdr.compression,
       bmp_file->dhdr.data_size,
       bmp_file->dhdr.pheight,
       bmp_file->dhdr.colors_count,
       bmp_file->dhdr.imp_colors_count
    );
}