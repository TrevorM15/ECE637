#include <math.h>
#include <stdlib.h>
typedef struct pixel pixel;

  struct pixel{
    int m,n;
  };

void connectedNeighbors(pixel s,double T,unsigned char **img,int width,int height, int *M,struct pixel *c) {
  
  int count = 0;
  
  if (fabs(img[s.m][s.n]-img[s.m-1][s.n])<=T && s.m-1 >0){
      count++;
      c[0].m=s.m-1;
      c[0].n=s.n;
    }
if (fabs(img[s.m][s.n]-img[s.m+1][ s.n])<=T && s.m+1<width){
        count++;
	c[1].m=s.m+1;
	c[1].n=s.n;
    }
if (fabs(img[s.m][s.n]-img[s.m][ s.n-1])<=T && s.n-1 >0){
        count++;
	c[2].m=s.m;
	c[3].n=s.n-1;
    }
if (fabs(img[s.m][s.n]-img[s.m][ s.n+1])<=T && s.n+1<height){
        count++;
	c[3].m=s.m;
	c[3].n=s.n+1;
    }
 *M =count;
}

void connectedSet( pixel s,double T,unsigned char **img,int width,int height,int ClassLabel,unsigned int **seg,int *NumConPixels){
  int i,j,*M;
  pixel c[4];
  double  **B;
  B = (double **)malloc(height*width*sizeof(double));
  for (i=0; i<height*width; i++){
    B[i] = (double*)malloc(2*sizeof(double));
  }
  for (i = 0; i<width*height;i++)
  for(j =0; j<2; j++){
      B[i][j]=-1;
    }
  i=0;
  *M=0;
  j = i;
  B[i][0]= s.m;
  B[i][1]=s.n;
  while (B[j][0] !=-1){

    for(j=0;j<4;j++){
      c[j].m = -1;
      c[j].n=-1;
    }
    connectedNeighbors( s,T,img,width,height, M, c);

    
    if(c[0].m != -1  && seg[s.m-1][ s.n]==65000){
      seg[s.m-1][s.n]=ClassLabel;
	i++;
	B[i][0]=s.m-1;
	B[i][1]=s.n;
    }
    if (c[1].m != -1 && seg[s.m+1][ s.n]==65000){
      seg[s.m+1][s.n]=ClassLabel;
        i++;
	B[i][0]=s.m+1;
	B[i][1]=s.n;
    }
    if( c[2].m !=-1 && seg[s.m][ s.n-1]==65000){
      seg[s.m][s.n-1]=ClassLabel;
	i++;
	B[i][0]=s.m;
	B[i][1]=s.n-1;
    }
    if (c[3].m !=-1 && seg[s.m][ s.n+1]==65000){
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
