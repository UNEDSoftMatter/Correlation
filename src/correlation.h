/*
 * Filename   : correlation.h
 *
 * Created    : 09.05.2016
 *
 * Modified   : lun 09 may 2016 20:48:18 CEST
 *
 * Author     : jatorre
 *
 * Purpose    : Headers for correlation.c
 *
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <complex.h>
#include <fftw3.h>
#include <gsl/gsl_matrix.h>

/* #############################################################################
#  IO functions that appears in io.c 
############################################################################# */

// Print a timestamp and some info

void PrintMsg(char *msg);

// Print an initial message

void PrintInitInfo(void);

// Check if the user enters argv[1]

int CheckInput(int argc);
