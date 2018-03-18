#include "lodepng.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

unsigned char* image;
unsigned char* ret_image;
unsigned width, height;
const char* filename;

void decodeOneStep()
{
  unsigned error;

  error = lodepng_decode32_file(&image, &width, &height, filename);
  //if(error) printf("error %u: %s ? \n", error, lodepng_error_text(error));

  

}

void encodeOneStep(const char* filename)
{
  /*Encode the image*/
  unsigned error = lodepng_encode32_file(filename, image, width, height);

  /*if there's an error, display it*/
  //if(error) printf("error %u: %s !\n", error, lodepng_error_text(error));
}



void pixOp(){
    uint32_t r [height][width];
    uint32_t g [height][width];
    uint32_t b [height][width];
    uint32_t a [height][width];
    uint32_t after_grey [height][width];
    uint32_t greyscale [height][width];
    uint32_t grey_PDF [256]; 
    uint32_t ret_PDF [256];

    uint32_t counter;

    uint32_t default_particle = width * height / 256;



    int test = 444*332;
    
    for(counter=0; counter<256; counter++){
        grey_PDF[counter] = 0;
    }

    //printf("GreyScale PDF: \n");

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
            printf("%c ",(unsigned char)after_grey[row][col]);
            ret_image[4*row*width + 4*col +0] = (unsigned char)after_grey[row][col];
            ret_image[4*row*width + 4*col +1] = (unsigned char)after_grey[row][col];
            ret_image[4*row*width + 4*col +2] = (unsigned char)after_grey[row][col];
            ret_image[4*row*width + 4*col +3] = (unsigned char)255;
        }
    }

    
/*
    printf("After grey:\n");    
    for(row=0; row<height; row++){
        for(col=0; col<width; col++){
            printf("%d ", after_grey[row][col]);
        }
        printf("\n");
    }
*/

    /*
    for(counter=0; counter<256; counter++){
        printf("%d ",ret_PDF[counter]);
        //test -= grey_PDF[counter];
    }
    */
    //printf("\nToTal= %d\n", test);

    // calc cumlative distribution function (CDF) of greyscale   

}

int main(int argc, char *argv[])
{
  const char* filename = argc > 1 ? argv[1] : "test01.png";
  decodeOneStep();
  //pixOp();
  //encodeOneStep("testOutput.png");
  return 0;
}