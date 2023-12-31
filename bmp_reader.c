#include <stdio.h>
#include <stdlib.h>
#include "bmp_reader.h"

void readBMPRowByRow(FILE* fp, BMPFile* bmpf) {
    int bytes_per_pixel = bmpf->dhdr.bits_per_pixel / 8;
    int row_size = bytes_per_pixel * bmpf->dhdr.width;
    int row_padding = (4 - (row_size % 4)) % 4;
    int rows_written = 0;
    unsigned char* row = (unsigned char*)malloc(row_size + row_padding);
    unsigned char* p = &bmpf->data[(bmpf->dhdr.height - 1) * row_size];
    fseek(fp, bmpf->bhdr.pixel_offset, SEEK_SET);
    while (rows_written < bmpf->dhdr.height) {
        fread(row, row_size + row_padding, 1, fp);
        if (bytes_per_pixel == 3) {
            for (int i = 0; i < row_size; i += bytes_per_pixel) {
                *p = row[i + 2]; p++;
                *p = row[i + 1]; p++;
                *p = row[i]; p++;
            }
        } else if (bytes_per_pixel == 4) {
            for (int i = 0; i < row_size; i += bytes_per_pixel) {
                *p = row[i + 3]; p++;
                *p = row[i + 2]; p++;
                *p = row[i + 1]; p++;
                *p = row[i]; p++;
            }
        } else {
            printf("Error: don't work with bytes_per_pixel = %d\n", bytes_per_pixel);
            exit(0);
        }
        rows_written++;
        p = p - 2 * row_size;
    }
    free(row);
}

BMPFile* loadBMPFile(char* fname) {
    FILE* fp = fopen(fname, "r");
    if(!fp) {
        printf("Can't load file \'%s\'\n", fname);
        exit(0);
    }
    BMPFile* bmp_file = (BMPFile*)malloc(sizeof(BMPFile));
    fread(&bmp_file->bhdr, sizeof(BMPHeader), 1, fp);
    fread(&bmp_file->dhdr, sizeof(DIBHeader), 1, fp);

    int data_size = bmp_file->dhdr.width * bmp_file->dhdr.height * bmp_file->dhdr.bits_per_pixel / 8;
    bmp_file->data = (unsigned char*)malloc(data_size); // memory for info of pixels
    readBMPRowByRow(fp, bmp_file);

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

void printBMPPixels(BMPFile* bmpf) {
    int data_size = bmpf->dhdr.width * bmpf->dhdr.height * bmpf->dhdr.bits_per_pixel / 8;
    for (int i = 0; i < data_size; i++) {
        if (!(i % 16)) 
            printf("\n%04x: ", i);
        printf("%02x ", bmpf->data[i]);
    }
    printf("\n");
}