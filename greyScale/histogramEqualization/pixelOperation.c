#include<stdint.h>
#include<stdio.h>


void pixOp(unsigned width, unsigned height, unsigned char* image){
    uint32_t r [height][width];
    uint32_t g [height][width];
    uint32_t b [height][width];
    uint32_t a [height][width];
    uint32_t greyscale [height][width];
    uint32_t grey_PDF [256]; 
    uint32_t counter;

    int test = 444*332;
    
    for(counter=0; counter<256; counter++){
        grey_PDF[counter] = 0;
    }

    printf("GreyScale PDF: \n");

    // read color code, put it in four int arr r, g, b, a, get final greyscale
    unsigned row, col;
    for(row=0; row<height; row++){
        for(col=0; col<width; col++){
            r[row][col] = image[4*row*width + 4*col +0];
            g[row][col] = image[4*row*width + 4*col +1];
            b[row][col] = image[4*row*width + 4*col +2];
            a[row][col] = image[4*row*width + 4*col +3];
            greyscale[row][col] = (r[row][col]*38 + g[row][col]*75 + b[row][col]*15) >> 7;
            grey_PDF[ greyscale[row][col] ] ++;
        }
    }
    
    for(counter=0; counter<256; counter++){
        printf("%d ",grey_PDF[counter]);
        test -= grey_PDF[counter];
    }

    //printf("\nToTal= %d\n", test);

    // calc cumlative distribution function (CDF) of greyscale


    

}