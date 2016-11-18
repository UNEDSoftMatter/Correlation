# CORRELATION

This program  reads a matrix and  computes the  (cross) correlation  function of
all the columns.

In  examples  directory  there is  an  example.  By  compiling  and  execute the
program, a data matrix \(N\times M\) is created so that
      
\[ 
A_{\mu\nu} = \sin \left(\frac{20 \pi \mu(\nu+1)}{N M} \right)
\]

Correlation uses GSL and FFTW.

Info
----
http://www.fftw.org/fftw3_doc/One_002dDimensional-DFTs-of-Real-Data.html#One_002dDimensional-DFTs-of-Real-Data
http://www.fftw.org/fftw3_doc/Complex-One_002dDimensional-DFTs.html#Complex-One_002dDimensional-DFTs

