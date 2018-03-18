#include<stdint.h>
#include<stdio.h>
#include</home/chenishi/git-repos/ImgProcessing/greyScale/histogramEqualization/lodepng.h>

void pixOp(unsigned width, unsigned height, unsigned char* image){
    uint32_t r [height][width];
    uint32_t g [height][width];
    uint32_t b [height][width];
    uint32_t a [height][width];
    uint32_t after_grey [height][width];
    uint32_t greyscale [height][width];
    uint32_t grey_PDF [256]; 
    uint32_t ret_PDF [256];
    unsigned char* ret_image;
    uint32_t counter;

    uint32_t default_particle = width * height / 256;



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


    // PDF to CDF
    for(counter=0; counter<256; counter++){
        if(counter){
            grey_PDF[counter] += grey_PDF[counter-1];
        }
    }

    for(counter=0; counter<256; counter++){
        if(grey_PDF[counter] / default_particle){
            ret_PDF[counter] = (grey_PDF[counter] / default_particle) -1;
        }else{
            ret_PDF[counter] = grey_PDF[counter] / default_particle ;
        }
        
    }

    for(counter=0; counter<256; counter++){
        for(row=0; row<height; row++){
            for(col=0; col<width; col++){
                if(greyscale[row][col] == counter){
                    after_grey[row][col] = ret_PDF[counter];
                }
            }
        }
    }

    for(row=0; row<height; row++){
        for(col=0; col<width; col++){
            ret_image[4*row*width + 4*col +0] = after_grey[row][col];
            ret_image[4*row*width + 4*col +1] = after_grey[row][col];
            ret_image[4*row*width + 4*col +2] = after_grey[row][col];
            ret_image[4*row*width + 4*col +3] = 255;
        }
    }

    

    printf("After grey:\n");    
    for(row=0; row<height; row++){
        for(col=0; col<width; col++){
            printf("%d ", after_grey[row][col]);
        }
        printf("\n");
    }


    /*
    for(counter=0; counter<256; counter++){
        printf("%d ",ret_PDF[counter]);
        //test -= grey_PDF[counter];
    }
    */
    //printf("\nToTal= %d\n", test);

    // calc cumlative distribution function (CDF) of greyscale


    

}