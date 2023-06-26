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
    fread(bmp_file, sizeof(bmp_file), 1, fp);
    fclose(fp);
    return bmp_file;
}

void freeBMPFile(BMPFile* bmp_file) {
    if (bmp_file) {
        free(bmp_file);
    }
}
