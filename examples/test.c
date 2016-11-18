/*
 * Filename   : test.c
 *
 * Created    : 18.11.2016
 *
 * Modified   : vie 18 nov 2016 10:29:27 CET
 *
 * Author     : jatorre
 *
 * Purpose    : Test correlation. Creates a sinusoidal matrix
 *  
 * Compile    : gcc -lm test.c -o test
 *
 */

#include <stdio.h>
#include <math.h>

#define NSteps 1000
#define NNodes   10

int main()
{
  int mu, nu;
  FILE *oFile;
  oFile = fopen("test.dat", "w");
  for (mu=0;mu<NSteps;mu++)
  {
    for (nu=0;nu<NNodes;nu++)
      fprintf(oFile, "%10.5e\t", sin(20*3.14159*(double) (mu*(nu+1))/((double) NSteps*NNodes)));
    fprintf(oFile,"\n");
  }
  fclose(oFile);
}
