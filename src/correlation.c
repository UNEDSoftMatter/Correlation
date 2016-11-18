/*
 * Filename   : correlation.c
 *
 * Created    : 09.05.2016
 *
 * Modified   : vie 18 nov 2016 10:28:18 CET
 *
 * Author     : jatorre
 *
 * Purpose    : To compute correlations 
 *
 */
#include "correlation.h"

int main(int argc, char * argv[])
{
  PrintInitInfo();

  PrintMsg("INIT");

  char str[100]; 
  memset(str, '\0',sizeof(str));

  char * f1 = argv[1];
  char * f2 = argv[2];
  
  PrintMsg("INIT");
  
  gsl_matrix *  iMatrix1 = gsl_matrix_calloc (NSteps,NNodes);
  gsl_matrix *  iMatrix2 = gsl_matrix_calloc (NSteps,NNodes);
  gsl_matrix * CCFMatrix = gsl_matrix_calloc (NSteps,NNodes*NNodes);
  
  PrintMsg("Reading input matrices");
  FILE *iFile;
  
  sprintf(str, "./%s", f1);
  printf("\tInput file: %s\n", str);
  iFile = fopen(str, "r");
  #if __BINARY_OUTPUT__
    gsl_matrix_fread(iFile,iMatrix1);
  #else
    gsl_matrix_fscanf(iFile,iMatrix1);
  #endif
  fclose(iFile);

  sprintf(str, "./%s", f2);
  printf("\tInput file: %s\n", str);
  iFile = fopen(str, "r");
  #if __BINARY_OUTPUT__
    gsl_matrix_fread(iFile,iMatrix2);
  #else
    gsl_matrix_fscanf(iFile,iMatrix2);
  #endif
  fclose(iFile);

  // Define auxiliar vectors needed to perform DFT
  gsl_vector * v1   = gsl_vector_calloc(NSteps);
  gsl_vector * v2   = gsl_vector_calloc(NSteps);
  gsl_vector * v3   = gsl_vector_calloc(NSteps);

  // Define auxiliar complex vectors needed to perform DFT
  // Also set to zero all the elements
  //
  // fftw_complex *out is a struct where
  // out[0] is the real part
  // out[1] is the imaginary part
  // Eg.: Real part of element i can be accessed with out[i][0]
  fftw_complex *out1;
  out1 = (fftw_complex *)fftw_malloc(sizeof (fftw_complex)*NSteps);
  memset(out1,0,sizeof (fftw_complex)*NSteps);

  fftw_complex *out2;
  out2 = (fftw_complex *)fftw_malloc(sizeof (fftw_complex)*NSteps);
  memset(out2,0,sizeof (fftw_complex)*NSteps); 
  
  fftw_complex *out3;
  out3 = (fftw_complex *)fftw_malloc(sizeof (fftw_complex)*NSteps);
  memset(out3,0,sizeof (fftw_complex)*NSteps); 

  // LOOP OVER ALL MU-COLUMNS
  for (int mu=0;mu<NNodes;mu++)
  {
    // Prepare a plan to perform a DFT from V1 vector to OUT1 complex vector
    fftw_plan pin1 = fftw_plan_dft_r2c_1d(NSteps, v1->data, out1, FFTW_MEASURE);
    memset(out1,0,sizeof (fftw_complex)*NSteps); 

    // Select the proper column and perform the current plan
    gsl_vector_view MuCol = gsl_matrix_column(iMatrix1,mu);
    gsl_vector_memcpy(v1,&MuCol.vector);
    // Substract the mean value (i.e., compute the FFT of the deviations)
    double v1mean = gsl_stats_mean(v1->data,v1->stride,NSteps);
    gsl_vector_add_constant(v1,-v1mean);
    fftw_execute(pin1);
   
    // LOOP AGAIN OVER ALL NU-COLUMNS
    for (int nu=0;nu<NNodes;nu++)
    {
      // Prepare another plan to perform a DFT from V2 vector to OUT2 complex vector
      fftw_plan pin2 = fftw_plan_dft_r2c_1d(NSteps, v2->data, out2, FFTW_MEASURE);
      memset(out2,0,sizeof (fftw_complex)*NSteps); 

      // Select the proper column and perform the current plan
      gsl_vector_view NuCol = gsl_matrix_column(iMatrix2,nu);
      gsl_vector_memcpy(v2,&NuCol.vector);
      // Substract the mean value (i.e., compute the FFT of the deviations)
      double v2mean = gsl_stats_mean(v2->data,v2->stride,NSteps);
      gsl_vector_add_constant(v2,-v2mean);
      fftw_execute(pin2);
    
      // Prepare a third plan to perform an IFT from OUT3 complex vector to V3 vector
      fftw_plan pout = fftw_plan_dft_c2r_1d(NSteps, out3, v3->data, FFTW_MEASURE);
      memset(out3,0,sizeof (fftw_complex)*NSteps); 

      // Compute the pointwise product OUT3=OUT1*OUT2^* 
      // OUT1 = a1 + b1*I (OUT1[0] = a1, OUT1[1] = b1)
      // OUT2 = a2 + b2*I (OUT2[0] = a2, OUT2[1] = b2)
      // OUT3 = (a1*a2 + b1*b2) + (-a1*b2 + a2*b1)I
      for (int i=0;i<NSteps;i++)
      {
        out3[i][0] =  out1[i][0]*out2[i][0] + out1[i][1]*out2[i][1];
        out3[i][1] = -out1[i][0]*out2[i][1] + out1[i][1]*out2[i][0];
      }
      gsl_vector_set_zero(v3);

      // Execute the plan
      fftw_execute(pout);

      // Each FFT transformation introduces a scale factor of NSteps
      // We fix that by scaling the output vector properly
      gsl_vector_scale(v3,1.0/((double)NSteps*NSteps));

      // Add the computed MU-NU cross-correlation to the proper column
      // of the output matrix
      gsl_vector_view MuNuCol = gsl_matrix_column(CCFMatrix,NNodes*mu+nu);
      gsl_vector_memcpy(&MuNuCol.vector,v3);
      
      fftw_destroy_plan(pin2);
      fftw_destroy_plan(pout);
    }
    fftw_destroy_plan(pin1);
  }

  #if __BINARY_OUTPUT__
    // PRINT CROSS CORRELATION MATRIX
    PrintMsg("Saving output matrix in binary form");
    sprintf(str, "./FFT-cf-%s-%s.dat", f1, f2);
    printf("\tOutput file: %s\n", str);
    FILE *oFile;
    oFile = fopen(str, "w");
      gsl_matrix_fwrite(oFile,CCFMatrix);
    fclose(oFile);
  #else
    // PRINT CROSS CORRELATION MATRIX
    PrintMsg("Saving output matrix in plain text form");
    sprintf(str, "./FFT-cf-%s-%s.dat", f1, f2);
    printf("\tOutput file: %s\n", str);
    FILE *oFile;
    oFile = fopen(str, "w");
      // By using FFT, total length of the correlation function is NSteps/2
      for (int i=0;i<CCFMatrix->size1/2;i++)
      {
        for (int j=0;j<CCFMatrix->size2;j++)
          fprintf(oFile, "%10.5e\t",gsl_matrix_get(CCFMatrix,i,j));
        fprintf(oFile, "\n");
      }
    fclose(oFile);
  #endif

  // FREE MEMORY
  fftw_free(out1);
  fftw_free(out2);
  fftw_free(out3);
 
  gsl_vector_free(v1);
  gsl_vector_free(v2);
  gsl_vector_free(v3);

  gsl_matrix_free( iMatrix1);
  gsl_matrix_free( iMatrix2);
  gsl_matrix_free(CCFMatrix);

  PrintMsg("EOF. How about a nice game of chess?");
  return 0;
}
