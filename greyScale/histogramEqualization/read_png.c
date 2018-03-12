#include</home/chenishi/git-repos/ImgProcessing/greyScale/histogramEqualization/lodepng.h>
#include</home/chenishi/git-repos/ImgProcessing/greyScale/histogramEqualization/pixelOperation.c>
#include<stdio.h>
#include<stdlib.h>


void decodeOneStep(const char* filename)
{
  unsigned error;
  unsigned char* image;
  unsigned width, height;

  error = lodepng_decode32_file(&image, &width, &height, filename);
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

  pixOp(width, height, image);

  free(image);
}

int main(int argc, char *argv[])
{
  const char* filename = argc > 1 ? argv[1] : "test01.png";
  decodeOneStep(filename);
  return 0;
}