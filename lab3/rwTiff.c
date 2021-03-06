#include "rwTiff.h"

void readTiff(fp,&input_img){
  
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

}

void writeTiff(fp, &output_img, filename){
  /* open Y image file */
  if ( ( fp = fopen ( filename, "wb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file %s ", &filename\n);
    exit ( 1 );
  }

  /* write Y image */
  if ( write_TIFF ( fp, &output_img ) ) {
    fprintf ( stderr, "error writing TIFF file %s\n", argv[2] );
    exit ( 1 );
  }

  /* close Y image file */
  fclose ( fp );
    

}
