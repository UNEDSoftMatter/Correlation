/*
 * Filename   : example3.c
 *
 * Created    : 18.11.2016
 *
 * Modified   : mar 18 abr 2017 12:55:33 CEST
 *
 * Author     : jatorre
 *
 * Purpose    : Test correlation. Creates a sinusoidal matrix
 *  
 * Compile    : gcc -lm example3.c -o example3
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
  oFile = fopen("example3.dat", "w");
  double T = NSteps;

  for (mu=0;mu<NSteps;mu++)
  {
    fprintf(oFile, "%20.15e\t", sin(2*3.1415926*((double) (mu))/T));
    fprintf(oFile, "%20.15e\t", sin(3*3.1415926*((double) (mu))/T));
    fprintf(oFile,"\n");
  }
  fclose(oFile);
}
