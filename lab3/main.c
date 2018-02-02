

#include <math.h>
#include "tiff.h"
#include "allocate.h"
#include "typeutil.h"
#include "connectedNeighbors.h"

void error(char *name);

int main (int argc, char **argv) 
{
  FILE *fp;
  struct TIFF_img input_img, Y;
  double **img;

  int32_t i,j;
  int ClassLabel = 1;
  unsigned int **seg;
  
  if ( argc != 2 ) error( argv[0] );
  /* open image file */

   if ( ( fp = fopen ( argv[1], "rb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file %s\n", argv[1] );
    exit ( 1 );
  }
 
  /* read image */

  if ( read_TIFF ( fp, &input_img ) ) {
    fprintf ( stderr, "error reading file %s\n", argv[1] );
    exit ( 1 );
  }

  /* close image file */

  fclose ( fp );

  /* check the type of image data */

  if ( input_img.TIFF_type != 'g' ) {
    fprintf ( stderr, "error:  image must be grayscale\n" );
    exit ( 1 );
  }

  /* Allocate image of double precision floats */
  img = (double **)get_img(input_img.width,input_img.height,sizeof(double));
  Y =  (double **)get_img(input_img.width,input_img.height,sizeof(double));
  **seg = (unsigned int **)malloc(input_img.height*sizeof(unsigned int));
  for (i=0; i<input_img.width;i++){
    seg[i] = (unsigned int *)malloc(input_img.width*sizeof(unsigned int));
  }
    /* copy img  to double array */
  for ( i = 0; i < input_img.height; i++ )
  for ( j = 0; j < input_img.width; j++ ) {
    img[i][j] = input_img[i][j];
    Y[i][j] = 0;
    seg[i][j]=0;
  }




  
  /* TODO: write connectedneighbors and connected sets*/







  /* set up structure for output color image */
  /* Note that the type is 'c' rather than 'g' */
  get_TIFF ( &Y, input_img.height, input_img.width, 'g' );
  
  
  /* open Y image file */
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
  free_TIFF ( &(input_img) );
  free_TIFF ( &(Y) );

  
  free_img( (void**)img );
    

  return(0);
}

void error(char *name)
{
    printf("usage:  %s  image.tiff \n\n",name);
    printf("this program reads in a 24-bit color TIFF image.\n");
    exit(1);
}

