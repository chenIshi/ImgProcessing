#include</home/chenishi/git-repos/ImgProcessing/greyScale/histogramEqualization/read_png.c>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
  const char* filename = argc > 1 ? argv[1] : "test01.png";
  decodeOneStep(filename);
  return 0;
}