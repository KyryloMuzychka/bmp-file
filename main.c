#include <stdio.h>
#include <stdlib.h>
#include "bmp_reader.h"

int main() {
//int main(int argc, char * argv[]) {
//    if (argc < 2) {
//        printf("Syntax: bmpreader <bmp file>\n");
//        return 0;
//    }
    //BMPFile* bmpf = loadBMPFile(argv[1]);
    
   BMPFile* bmpf = loadBMPFile("/Users/muzycka/Desktop/bmpFile/bmpFile/clue.bmp");
    
    //printf("char ID\[2\] = %c%c\nunsigned int file_size = %d\nchar unused\[4\] = %d\nunsigned int pixel_offset = %d\n", bmpf->bhdr.ID[0], bmpf->bhdr.ID[1], bmpf->bhdr.file_size, bmpf->bhdr.pixel_offset);
    
  //  freeBMPFile(bmpf);
    
    return 0;
}
