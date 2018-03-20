#ifndef SEG2_H_
#define SEG2_H_

typedef struct pixel pixel;

  struct pixel{
    int m,n;
  };
  
void connectedNeighbors(pixel s,double T,unsigned char **img,int width,int height, int *M,struct pixel *c);

void connectedSet( pixel s,double T,unsigned char **img,int width,int height,int ClassLabel,unsigned int **seg,int *NumConPixels);

void rmSet( pixel s,double T,unsigned char **img,int width,int height,int ClassLabel,unsigned int **seg,int *NumConPixels);

#endif
