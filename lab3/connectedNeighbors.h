#ifndef CONNECTEDNEIGHBORS_H_
#define CONNECTEDNEIGHBORS_H_

void connectedNeighbors(
			pixel s,
			double T,
			unsigned char **img,
			int width,
			int height,
			int *M,
			pixel c[4]);

void connectedSet(
		  pixel s,
		  double T,
		  unsigned char **img,
		  int width,
		  int height,
		  int ClassLabel,
		  unsigned int **seg,
		  int *NumConPixels);
#endif // CONNECTEDNEIGHBORS_H_
