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
#ifndef HEADER_SEEN

#define HEADER_SEEN

/* #############################################################################
#  Shared functions 
############################################################################# */

#include <fftw3.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include <stdio.h>
#include <time.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

/* #############################################################################
#  Parameters of the simulation 
############################################################################# */

#include "params.h"

/* #############################################################################
#  IO functions that appears in io.c 
############################################################################# */

// Print a timestamp and some info

void PrintMsg(char *msg);

// Print an initial message

void PrintInitInfo(void);

// Check if the user enters argv[1]

int CheckInput(int argc);

#endif
