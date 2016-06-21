/*
 * Filename   : correlation.c
 *
 * Created    : 09.05.2016
 *
 * Modified   : vie 20 may 2016 19:17:36 CEST
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

  for (int mu=0;mu<NCols;mu++)
  {
    gsl_vector_view imu = gsl_matrix_column(Input,mu);
    out1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NRows);
    pin1 = fftw_plan_dft_r2c_1d(NRows, &imu.vector->data, out1, flags);
    fftw_execute(pin1);
    for (int nu=0;nu<NCols;nu++)
    {
      gsl_vector_view inu = gsl_matrix_column(Input,nu);
  
      out2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NRows);
      //pin2 = fftw_plan_dft_r2c_1d(int N, double *in2, fftw_complex *out2, unsigned flags);
      pin2 = fftw_plan_dft_r2c_1d(NRows, &inu.vector->data, out2, flags);
      fftw_execute(pin2);


    
    } 

  }     
  // TODO: Split the matrix into cols. Each col is a different double *in;

  // TODO: Loop. Foreach pair *in1, *in2;

  // INIT FFTW3 WORKPLACE
  
  fftw_complex * out1, out2;
  fftw_plan      pin, pout;

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
