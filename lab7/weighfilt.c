
#include <math.h>
#include "tiff.h"
#include "allocate.h"
#include "typeutil.h"

void error(char *name);

int main (int argc, char **argv) 
{
  FILE *fp;
  struct TIFF_img input_img, color_img;
  int lfilt =5;
  int hfilt =(lfilt-1)/2;
  int pad_width, pad_height;
  int32_t i,j,l,m;
  double ** img;

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

  /* Allocate image of double precision floats and zero pad */


  pad_width = input_img.width+lfilt-1;
  pad_height = input_img.height+lfilt-1;
  img= (double **)get_img(pad_width,pad_height,sizeof(double));
  

    for ( i = 0; i < pad_height; i++ )
      for ( j = 0; j < pad_width; j++ ) {
	img[i][j] =0;
  }

    /* copy components to double array */
     

    for ( i =0; i < input_img.height; i++ )
      for ( j = 0; j < input_img.width; j++ ) {
	img[i+hfilt][j+hfilt] = input_img.mono[i][j];
  }

 /* filter image channels */
 
      for ( i =hfilt; i < input_img.height+hfilt; i++ ){
	for ( j = hfilt; j < input_img.width+hfilt; j++ ) {
	  img[i][j]=0;
	  for (l = -hfilt; l<hfilt+1;l++){
	    for (m = -hfilt;m<hfilt+1;m++){
	      img[i][j] +=img[i-l][j+m]/(lfilt*lfilt);
	    }
	  }
	    for (l = -hfilt+2; l<hfilt-1;l++){
	    for (m = -hfilt+2;m<hfilt-1;m++){
	      img[i][j] +=img[i-l][j+m]/(lfilt*lfilt);
	    }
	  }
	}
      }
   
        for ( i =hfilt; i < input_img.height+hfilt; i++ ){
	for ( j = hfilt; j < input_img.width+hfilt; j++ ) {
	  if (img[i][j]>255){
	    img[i][j]=255;
	  }
	  if (img[i][j]<0){
	    img[i][j]=0;
	  }
	}
	}
  /* set up structure for output color image */
  /* Note that the type is 'c' rather than 'g' */
  get_TIFF ( &color_img, input_img.height, input_img.width, 'g' );

  /* construct color image from filtered channels */
 
    for ( i = hfilt; i <input_img.height+hfilt; i++ ){
      for ( j = hfilt; j < input_img.width+hfilt; j++ ) {
          color_img.mono[i-hfilt][j-hfilt] = img[i][j];
      }
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

  free(img);
  
  return(0);
}

void error(char *name)
{
    printf("usage:  %s  image.tiff \n\n",name);
    printf("this program reads in a gray-scale TIFF image.\n");
    exit(1);
}

