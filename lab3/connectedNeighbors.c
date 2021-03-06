#include "connectedNeighbors.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
  int m,n;
}pixel;x

void connectedNeighbors(
			pixel s,
			double T,
			unsigned char **img,
			int width,
			int height,
			int *M,
			pixel c[4]) {
  int j;
  for(j=0;j<4;j++){
    c[j].m,c[j].n=NULL,NULL;
  }
  
  int count = 0;
  
  if (fabs(**img[s.m][s.n]-**img[s.m-1][ s.n])<=T) && (s.m-1 >0){
      count++;
      c[0].m,c[0].n=s.m-1, s.n;
    }
  if (fabs(**img[s.m][s.n]-**img[s.m+1][ s.n])<=T) && (s.m+1<width){
        count++;
	 c[1].m,c[1].n=s.m+1, s.n;
    }
  if (fabs(**img[s.m][s.n]-**img[s.m][ s.n-1])<=T) && (s.n-1 >0){
        count++;
	 c[2].m,c[2].n=s.m, s.n-1;
    }
  if (fabs(**img[s.m][s.n]-**img[s.m][ s.n+1])<=T) && (s.n+1<height){
        count++;
	 c[3].m,c[3].n=s.m, s.n+1;
    }
  *M =count;
}

void connectedSet(
		  pixel s,
		  double T,
		  unsigned char **img,
		  int width,
		  int height,
		  int ClassLabel,
		  unsigned int **seg,
		  int *NumConPixels){
  int i,j;
  int B[width*height][2];
  for (i = 0; i<width*height;i++)
    for(j =0; j<2; j++){
      B[i][j]=NULL;
    }
  i=0;
  j = i;
  B[i][0]= s.m;
  B[i][1]=s.n;
  while (B[j][0] !=NULL){
    void connectedNeighbors(pixel s,
			double T,
			unsigned char **img,
			int width,
			int height,
			int *M,
			    pixel c[4]);

    
    if(c[0].m != NULL  && seg[s.m-1][ s.n]==0){
      seg[s.m-1][s.n]=ClassLabel;
	i++;
	B[i][0]=s.m-1;
	B[i][1]=s.n;
    }
    if (c[1].m != NULL && seg[s.m+1][ s.n]==0){
      seg[s.m+1][s.n]=ClassLabel;
        i++;
	B[i][0]=s.m+1;
	B[i][1]=s.n;
    }
    if( c[2].m !=NULL && seg[s.m][ s.n-1]==0){
      seg[s.m][s.n-1]=ClassLabel;
	i++;
	B[i][0]=s.m;
	B[i][1]=s.n-1;
    }
    if (c[3].m !=NULL && seg[s.m][ s.n+1]==0){
        seg[s.m][s.n+1]=ClassLabel;
	i++;
	B[i][0]=s.m;
	B[i][1]=s.n+1;
    }
    B[j][0], B[j][1]=NULL,NULL;
    j++;
    s.m=B[j][0];
    s.n=B[j][1];
    *NumConPixels += *M;
  }

}
