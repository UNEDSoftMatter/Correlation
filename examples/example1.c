/*
 * Filename   : example1.c
 *
 * Created    : 18.11.2016
 *
 * Modified   : mar 18 abr 2017 12:54:48 CEST
 *
 * Author     : jatorre
 *
 * Purpose    : Test correlation. Creates a sinusoidal matrix
 *  
 * Compile    : gcc -lm example1.c -o example1
 *
 */

#include <stdio.h>
#include <math.h>

#define NSteps  1000
#define NNodes     2 

int main()
{
  int mu, nu;
  FILE *oFile;
  oFile = fopen("example1.dat", "w");
  double T = NSteps;

  for (mu=0;mu<NSteps;mu++)
  {
    fprintf(oFile, "%20.15e\t", sin(2*3.1415926*((double) (mu))/T));
    fprintf(oFile, "%20.15e\t", sin(2*3.1415926*((double) (mu))/T));
    fprintf(oFile,"\n");
  }
  fclose(oFile);
}
