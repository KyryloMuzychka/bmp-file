#include <stdio.h>
#include <stdlib.h>
#include "bmp_reader.h"

int main(int argc, char * argv[]) {
  if (argc < 2) {
    printf("Syntax: bmpreader <bmp file>\n");
    return 0;
  }
  BMPFile* bmpf = loadBMPFile(argv[1]);
  printBMPHeaders(bmpf);
  printBMPPixels(bmpf);
  freeBMPFile(bmpf);
  return 0;
}
