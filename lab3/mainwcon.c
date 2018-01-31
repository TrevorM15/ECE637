
#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include "tiff.h"
#include "allocate.h"
#include "typeutil.h"

void error(char *name);

typedef struct pixel pixel;

  struct pixel{
    int m,n;
  };
  
void connectedNeighbors(pixel s,double T,unsigned char **img,int width,int height, int *M,pixel c[4]) {
  
  int count = 0;
  
  if (fabs(img[s.m][s.n]-img[s.m-1][s.n])<=T && s.m-1 >0){
      count++;
      c[0].m=s.m-1;
      c[0].n=s.n;
    }
if (fabs(img[s.m][s.n]-img[s.m+1][ s.n])<=T && s.m+1<width){
        count++;
	c[0].m=s.m+1;
      c[0].n=s.n;
    }
if (fabs(img[s.m][s.n]-img[s.m][ s.n-1])<=T && s.n-1 >0){
        count++;
	c[0].m=s.m;
      c[0].n=s.n-1;
    }
if (fabs(img[s.m][s.n]-img[s.m][ s.n+1])<=T && s.n+1<height){
        count++;
	c[0].m=s.m;
	c[0].n=s.n+1;
    }
  *M =count;
}

void connectedSet( pixel s,double T,unsigned char **img,int width,int height,int ClassLabel,unsigned int **seg,int *NumConPixels){
  int i,j,*M;
  pixel c[4];
  int  **B;
  B = (int **)malloc(width*height*sizeof(int));
  for (i=0; i<2; i++){
    B[i] = (int*)malloc(2*sizeof(int));
  }
  for (i = 0; i<width*height;i++)
    for(j =0; j<2; j++){
      B[i][j]=-1;
    }
  i=0;
  M=0;
  j = i;
  B[i][0]= s.m;
  B[i][1]=s.n;
  while (B[j][0] !=-1){

    for(j=0;j<4;j++){
      c[j].m = -1;
      c[j].n=-1;
    }
     connectedNeighbors( s,T,img,width,height, M, &c[4]);

    
    if(c[0].m != -1  && seg[s.m-1][ s.n]==0){
      seg[s.m-1][s.n]=ClassLabel;
	i++;
	B[i][0]=s.m-1;
	B[i][1]=s.n;
    }
    if (c[1].m != -1 && seg[s.m+1][ s.n]==0){
      seg[s.m+1][s.n]=ClassLabel;
        i++;
	B[i][0]=s.m+1;
	B[i][1]=s.n;
    }
    if( c[2].m !=-1 && seg[s.m][ s.n-1]==0){
      seg[s.m][s.n-1]=ClassLabel;
	i++;
	B[i][0]=s.m;
	B[i][1]=s.n-1;
    }
    if (c[3].m !=-1 && seg[s.m][ s.n+1]==0){
        seg[s.m][s.n+1]=ClassLabel;
	i++;
	B[i][0]=s.m;
	B[i][1]=s.n+1;
    }
    B[j][0]=-1;
    B[j][1]= -1;
    j++;
    s.m=B[j][0];
    s.n=B[j][1];
    *NumConPixels += *M;
  }

}

int main (int argc, char **argv) 
{
  FILE *fp;
  struct TIFF_img iImg,Y;
  unsigned char **img;
  int32_t i,j;
  int ClassLabel;
  int T =1;  
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
 seg = (unsigned int **)malloc(iImg.height*sizeof(unsigned int));
  for (i=0; i<iImg.width;i++){
    seg[i] = (unsigned int *)malloc(iImg.width*sizeof(unsigned int));
  }
    /* fill arrays */
  for ( i = 0; i < iImg.height; i++ )
  for ( j = 0; j < iImg.width; j++ ) {
    img[i][j] = iImg.mono[i][j];
    seg[i][j]=-1;
  }
  
  /* segment the entire image*/
  numRegions =0;
  ClassLabel=1;
  T=1;
  for(i=67; i<68; i++) /*change for full seg case */
    for (j = 45; j<46; j++){
      /*
    for(i=0; i<iImg.height; i++) 
    for (j = 0; j<iImg.width; j++){
      */ 
      s.m =i;
      s.n=j;
      NumConPixels=0;
      if(seg[i][j]==-1){
	connectedSet( s,T,img,iImg.width,iImg.height,ClassLabel,seg,&NumConPixels);
	  ClassLabel++;
	if(NumConPixels >= 100){
	  numRegions++;
	}else{
	  connectedSet( s,T,img,iImg.width,iImg.height,0,seg,&NumConPixels);
	}
	  }
    }

  /*  output top 256 connected segments to output tiff img Y */
  for ( i = 0; i < iImg.height; i++ )
  for ( j = 0; j < iImg.width; j++ ) {
      Y.mono[i][j] = seg[i][j];
  }

  /* set up structure for output segmented image */
  /* Note that the type is 'g' rather than 'c' */
  get_TIFF ( &Y, iImg.height, iImg.width, 'g' );
  
  
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
  free((void**)seg);
   free_img((void**)img);
    

  return(0);
}

void error(char *name)
{
    printf("usage:  %s  image.tiff \n\n",name);
    printf("this program reads in a 24-bit color TIFF image.\n");
    exit(1);
}

