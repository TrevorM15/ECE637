
#include <math.h>
#include "tiff.h"
#include "allocate.h"
#include "typeutil.h"

void error(char *name);

int main (int argc, char **argv) 
{
  FILE *fp;
  struct TIFF_img input_img, color_img;
  int lfilt =9;
  int32_t i,j,k;

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

  /* Allocate image of double precision floats and zero pad */
  double ***img = (double ***)malloc(3*sizeof(double **));
  for (i = 0; i<3; i++){
    img[i]= (double **)get_img(input_img.width,input_img.height,sizeof(double));
  }
    /* copy components to double array */
  for (k = 0; k < 3; k++)
    for ( i =0; i < input_img.height; i++ )
      for ( j = 0; j < input_img.width; j++ ) {
	img[k][i][j] = input_img.color[k][i][j];
  }
  
 /* TODO: filter image channels */


  
  /* set up structure for output color image */
  /* Note that the type is 'c' rather than 'g' */
  get_TIFF ( &color_img, input_img.height, input_img.width, 'c' );

  /* construct color image from filtered channels */
  for (k = 0; k<3; k++)
    for ( i = 0; i < input_img.height; i++ )
      for ( j = 0; j < input_img.width; j++ ) {
          color_img.color[k][i][j] = img[k][i][j];
      }

  /* open color image file */
  if ( ( fp = fopen ( "color.tif", "wb" ) ) == NULL ) {
      fprintf ( stderr, "cannot open file color.tif\n");
      exit ( 1 );
  }
    
  /* write color image */
  if ( write_TIFF ( fp, &color_img ) ) {
      fprintf ( stderr, "error writing TIFF file %s\n", argv[2] );
      exit ( 1 );
  }
    
  /* close color image file */
  fclose ( fp );

  /* de-allocate space which was used for the images */
  free_TIFF ( &(input_img) );
  free_TIFF ( &(color_img) );

  free_img((void**)img[0]);
  free_img((void**)img[1]);
  free_img((void**)img[2]);
  free(img);
  
  return(0);
}

void error(char *name)
{
    printf("usage:  %s  image.tiff \n\n",name);
    printf("this program reads in a 24-bit color TIFF image.\n");
    printf("It then horizontally filters the green component, adds noise,\n");
    printf("and writes out the result as an 8-bit image\n");
    printf("with the name 'green.tiff'.\n");
    printf("It also generates an 8-bit color image,\n");
    printf("that swaps red and green components from the input image");
    exit(1);
}

