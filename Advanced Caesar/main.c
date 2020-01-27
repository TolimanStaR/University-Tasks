#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>

#include "file.h"
#include "caesar.h"

int main(int argc, char *argv[]) {

     int sizeofFile = getSize(argv);
     char *data = readData(argv);
     int shift = (int) argv[4][0] - '0';

     char *processedData = (int) argv[1][0] - '0' == 1
                           ?
                           encodeText(argv, data, shift, sizeofFile)
                           :
                           decodeText(argv, data, shift, sizeofFile);

     writeData(argv, processedData, sizeofFile);

     return 0;
}