#include <stdio.h>
#include <stdlib.h>
#include <MagickWand/MagickWand.h>

int main(int argc,char **argv)
{
#define ThrowWandException(wand) \
{ \
  char \
    *description; \
 \
  ExceptionType \
    severity; \
 \
  description=MagickGetException(wand,&severity); \
  (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); \
  description=(char *) MagickRelinquishMemory(description); \
  exit(-1); \
}

  MagickBooleanType
    status;

  MagickWand
    *magick_wand;

  if (argc != 2)
    {
      (void) fprintf(stdout,"Usage: %s image thumbnail\n",argv[0]);
      exit(0);
    }
  /*
    Read an image.
  */
  MagickWandGenesis();
  magick_wand=NewMagickWand();  
  status=MagickReadImage(magick_wand,argv[1]);
  if (status == MagickFalse)
    ThrowWandException(magick_wand);
  size_t width = MagickGetImageWidth(magick_wand);
  size_t height = MagickGetImageHeight(magick_wand);
  int pixel[height][width];
  PixelIterator *iterator = NewPixelIterator(magick_wand);
  PixelWand **pixels = NULL;
  int x;
  for(int i = 0;i<height;i++) {
      pixels = PixelGetNextIteratorRow(iterator, &x);
      for(x=0;x<width;x++){
          pixel[i][x] =  pixels[x];
      }
  }
  printf("First ele of pixel is: %d", pixel[0][0]);
  printf("Height and width are: %ld, %ld\n", height, width);
  return(0);
}