
#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include "tiff.h"
#include "allocate.h"
#include "typeutil.h"
#include "seg2.h"

void error(char *name);

int main (int argc, char **argv) 
{
  FILE *fp;
  struct TIFF_img iImg,Y;
  unsigned char **img;
  int32_t i,j;
  int ClassLabel;
  int T;  
  unsigned int **seg;
  int numRegions, NumConPixels;
  typedef struct pixel pixel;

  struct pixel{
    int m,n;
  };
  pixel s;

  if ( argc != 2 ) error( argv[0] );
  /* open image file */

   if ( ( fp = fopen ( argv[1], "rb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file %s\n", argv[1] );
    exit ( 1 );
  }
 
  /* read image */

  if ( read_TIFF ( fp, &iImg ) ) {
    fprintf ( stderr, "error reading file %s\n", argv[1] );
    exit ( 1 );
  }

  /* close image file */

  fclose ( fp );

  /* check the type of image data */

  if ( iImg.TIFF_type != 'g' ) {
    fprintf ( stderr, "error:  image must be grayscale\n" );
    exit ( 1 );
  }

  /* Allocate image and segmentation space */
 img = (unsigned char **)get_img(iImg.width,iImg.height,sizeof(unsigned char));
 seg = (unsigned int **)get_img(iImg.width,iImg.height,sizeof(unsigned int));
 
    /* fill arrays */
  for ( i = 0; i < iImg.height; i++ )
  for ( j = 0; j < iImg.width; j++ ) {
    img[i][j] = iImg.mono[i][j];
    seg[i][j]=65000;
  }
  /* segment image */
  numRegions =0;
  ClassLabel=1;
  T=3;
  NumConPixels=0;
  /*    for(i=67; i<68; i++)
    for (j = 45; j<46; j++){
  */
    for ( i = 0; i < iImg.height; i++ )
    for ( j = 0; j < iImg.width; j++ ) {
       s.m =i;
       s.n=j;
      if(seg[i][j]==65000){
	if(NumConPixels <100){
	connectedSet( s,T,img,iImg.width,iImg.height,0,seg,&NumConPixels);
	}else {
	  numRegions++;
	connectedSet( s,T,img,iImg.width,iImg.height,ClassLabel,seg,&NumConPixels);
	ClassLabel++;
	}
      }
      
    }
    printf("The number of regions is %d .\n",numRegions);
    
  /* set up structure for output segmented image */
  /* Note that the type is 'g' rather than 'c' */
  get_TIFF ( &Y, iImg.height, iImg.width, 'g' );

  
  /*  output segmented image to tiff img Y */
  for ( i = 0; i < iImg.height; i++ )
  for ( j = 0; j < iImg.width; j++ ) {
        Y.mono[i][j] = seg[i][j];
  }


  /* Open output  image file */
  if ( ( fp = fopen ( "Y.tif", "wb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file Y.tif\n");
    exit ( 1 );
  }

  /* write Y image */
  if ( write_TIFF ( fp, &Y ) ) {
    fprintf ( stderr, "error writing TIFF file %s\n", argv[2] );
    exit ( 1 );
  }

  /* close Y image file */
  fclose ( fp );
    
    

  /* de-allocate space which was used for the images */
  free_TIFF ( &(iImg) );
  free_TIFF ( &(Y) );
  free_img((void**)seg);
  free_img((void**)img);

  return(0);
}

void error(char *name)
{
    printf("usage:  %s  image.tiff \n\n",name);
    printf("this program reads in a grayscale TIFF image.\n");
    printf("and outputs a segmented version.\n");
     
    exit(1);
}
