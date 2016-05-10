/*
 * Filename   : correlation.c
 *
 * Created    : 09.05.2016
 *
 * Modified   : mar 10 may 2016 19:32:12 CEST
 *
 * Author     : jatorre
 *
 * Purpose    : To compute correlations 
 *
 */

#include "correlation.h"
#include "params.h"

int main(int argc, char * argv[])
{
  PrintInitInfo();

  // Checkpoint: We need an input filename
  if (CheckInput(argc))
    return 1;

  char str[100]; 
  char * filestr = argv[1];
  
  PrintMsg("INIT");
  
  gsl_matrix * Input  = gsl_matrix_calloc (NRows,NCols);
  
  FILE *iFile;
  PrintMsg("Reading input matrix");
  strcpy (str, "./data/");
  strcat (str, filestr);
  printf("\tInput file: %s\n", str);
  iFile = fopen(str, "r");
    gsl_matrix_fscanf(iFile, Input);
  fclose(iFile);

  // TODO: Split the matrix into cols. Each col is a different double *in;

  // TODO: Loop. Foreach pair *in1, *in2;

  // INIT FFTW3 WORKPLACE
  
  fftw_complex * out1, out2;
  fftw_plan      pin, pout;

  out1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NRows);
  pin1 = fftw_plan_dft_r2c_1d(int N, double *in1, fftw_complex *out1, unsigned flags);
  fftw_execute(pin1);
  
  out2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NRows);
  pin2 = fftw_plan_dft_r2c_1d(int N, double *in2, fftw_complex *out2, unsigned flags);
  fftw_execute(pin2);

  // TODO: Multiply pin1*pin2=out3 (NOTE THAT THEY ARE COMPLEX VECTORS!) 

  pout = fftw_plan_dft_c2r_1d(int N, fftw_complex *out3, double *out, unsigned flags);

  // TODO: Print the correlation
  // TODO: Check the normalization

  // FREE MEMORY
  
  fftw_free(out);

  gsl_matrix_free(Input);

  PrintMsg("EOF");

  return 0;
}
