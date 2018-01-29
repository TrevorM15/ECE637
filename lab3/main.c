
#include <math.h>
#include "tiff.h"
#include "allocate.h"
#include "typeutil.h"

void error(char *name);

int main (int argc, char **argv) 
{
  FILE *fp;
  struct TIFF_img input_img, Y;
  double **img;

  int32_t i,j,pixel;

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
  if ( input_img.TIFF_type != 'c' ) {
    fprintf ( stderr, "error:  image must be 24-bit color\n" );
    exit ( 1 );
  }

  /* Allocate image of double precision floats */
  img = (double **)get_img(input_img.width,input_img.height,sizeof(double));
    
  /* set up structure for output color image */
  /* Note that the type is 'c' rather than 'g' */
  get_TIFF ( &Y, input_img.height, input_img.width, 'c' );





  
  /* TODO: write connectedneighbors and connected sets*/







  
  
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

  
  free_img( (void**)img1 );
  free_img( (void**)img2 );  

  return(0);
}

void error(char *name)
{
    printf("usage:  %s  image.tiff \n\n",name);
    printf("this program reads in a 24-bit color TIFF image.\n");
    exit(1);
}

