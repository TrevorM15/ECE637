#include "connectedNeighbors.h"
#include <math.h>


typedef struct {
  int m,n;
}pixel;

void connectedNeighbors(
			pixel s,
			double T,
			unsigned char **img,
			int width,
			int height,
			int *M,
			pixel c[4]) {
  int count = 0;
  if (abs(**img[s.m][s.n]-**img[s.m-1][ s.n])<=T) && (s.m-1 >1){
      count++;
      c[0].m,c[0].n=s.m-1, s.n;
    }
  if (abs(**img[s.m][s.n]-**img[s.m+1][ s.n])<=T) && (s.m+1<width){
        count++;
	 c[1].m,c[1].n=s.m+1, s.n;
    }
  if (abs(**img[s.m][s.n]-**img[s.m][ s.n-1])<=T) && (s.n-1 >1){
        count++;
	 c[2].m,c[2].n=s.m, s.n-1;
    }
  if (abs(**img[s.m][s.n]-**img[s.m][ s.n+1])<=T) && (s.n+1<height){
        count++;
	 c[3].m,c[3].n=s.m, s.n+1;
    }
  *M = count;
  return *M;
  return c;
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


}
