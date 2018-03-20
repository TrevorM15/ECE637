
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
  int32_t i,j,k,l,m;
  int lambda =1.5;
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
  double ***img2 = (double ***)malloc(3*sizeof(double **));
  double ***img3 = (double ***)malloc(3*sizeof(double **));
  int pad_width = input_img.width+lfilt-1;
  int pad_height = input_img.height+lfilt-1;
  for (i = 0; i<3; i++){
    img[i]= (double **)get_img(pad_width,pad_height,sizeof(double));
    img2[i]= (double **)get_img(pad_width,pad_height,sizeof(double));
    img3[i]= (double **)get_img(pad_width,pad_height,sizeof(double));
  }
    for (k = 0; k < 3; k++)
    for ( i = 0; i < pad_height; i++ )
      for ( j = 0; j < pad_width; j++ ) {
	img[k][i][j] =0;
  }

    /* copy components to double array */
     
    for (k = 0; k < 3; k++)
    for ( i =0; i < input_img.height; i++ )
      for ( j = 0; j < input_img.width; j++ ) {
	img[k][i+hfilt][j+hfilt] = input_img.color[k][i][j];
  }
    
        /* make second copy */
    
    for (k = 0; k < 3; k++)
    for ( i =0; i < pad_height; i++ )
      for ( j = 0; j < pad_width; j++ ) {
	img2[k][i][j] = img[k][i][j];
	img3[k][i][j] = img[k][i][j];
      }
 
    
 /* low-pass filter image channels */
 
    for (k =0; k < 3; k++){
      for ( i =hfilt; i < input_img.height+hfilt; i++ ){
	for ( j = hfilt; j < input_img.width+hfilt; j++ ) {
	  img[k][i][j]=0; 
	  for (l = -hfilt; l<hfilt+1;l++){
	    for (m = -hfilt;m<hfilt+1;m++){
	      if((l!=0)||(m!=0)){
	      img[k][i][j] +=img[k][i+l][j+m]/(lfilt*lfilt);
	      }
	    }
	  }
	}
      }
    } 
    /* create high-pass filter */
  
    for (k =0; k < 3; k++)
      for ( i =hfilt; i < input_img.height+hfilt; i++ )
	for ( j = hfilt; j < input_img.width+hfilt; j++ ){
	  img2[k][i][j] = img2[k][i][j]+lambda*(img2[k][i][j]-img[k][i][j]);
	  if (img2[k][i][j] >255) {
	    img2[k][i][j] =255;
	  } else if(img2[k][i][j]<0){
	    img2[k][i][j]=0;

	  }
	}
  /* set up structure for output color image */
  /* Note that the type is 'c' rather than 'g' */
  get_TIFF ( &color_img, input_img.height, input_img.width, 'c' );

  /* construct color image from filtered channels */
  for (k = 0; k<3; k++){
    for ( i = hfilt; i <input_img.height+hfilt; i++ ){
      for ( j = hfilt; j < input_img.width+hfilt; j++ ) {
          color_img.color[k][i-hfilt][j-hfilt] = img2[k][i][j];
      }
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

  free_img((void**)img[0]);
  free_img((void**)img[1]);
  free_img((void**)img[2]);
  free(img);
  free_img((void**)img2[0]);
  free_img((void**)img2[1]);
  free_img((void**)img2[2]);
  free(img2);
  free_img((void**)img3[0]);
  free_img((void**)img3[1]);
  free_img((void**)img3[2]);
  free(img3);
  
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

