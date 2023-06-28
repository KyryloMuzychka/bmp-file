#ifndef _BMP_READER_H_
#define _BMP_READER_H_

#pragma pack(1)

typedef struct BMPHeader {
    char ID[2];
    unsigned int file_size;
    char unused[4];
    unsigned int pixel_offset;
} BMPHeader;

typedef struct DIBHeader {
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short color_planes;
    unsigned short bits_per_pixel;
    unsigned int compression;
    unsigned int data_size;
    unsigned int pheight;
    unsigned int colors_count;
    unsigned int imp_colors_count;
} DIBHeader;

typedef struct BMPFile {
    BMPHeader bhdr;
    DIBHeader dhdr;
    unsigned char* data;
} BMPFile;

#pragma pop

BMPFile* loadBMPFile(char* fname);
void freeBMPFile(BMPFile* bmp_file);
void printBMPHeaders(BMPFile* bmp_file);

#endif
