#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <MagickWand/MagickWand.h>




int find_avg(char * str) {
  int ret = 0;
  char p[4];
  int i = 0;
  while(str[0] != ')'){
    if(str[0] == ','){
      p[i] = '\0';
      ret += atoi(p);
      i = 0;
      str++;
    } else {
      if (isdigit(str[0])){
        p[i] = str[0];
        i++;
      }
      str++;
    }
  }
  p[i] = '\0';
  ret += atoi(p);
  return ret / 3;
}

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

char *to_print = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

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
  int i;
  size_t j;
  // storing average directly
  for(i = 0;i < height;i++) {
  pixels = PixelGetNextIteratorRow(iterator, &j);
  for(x=0;x<width;x++){
          char* to_parse = PixelGetColorAsString(pixels[x]);
          pixel[i][x] = find_avg(to_parse);
      }
  }
  double l = (255.0 / strlen(to_print));
  // Printing out stuff
  for(i = 0;i<height;i++) {
    for(x=0;x<width;x++) {
      int k = pixel[i][x] / l;
      printf("%c", to_print[k]);
    }
    // printf("\n");
  }
  return(0);
}