Rev#003
-------
- User can now select the kind of FFT to be computed, either the correlation
  of the deviation, either the correlation of the variables themselves.

Rev#002
-------
- The program now computes the correlation of the deviations, i.e.,
  <(x(0)-xmean)(y(t)-ymean)>

Rev#001
-------
- The program now uses FFT to perform the cross-correlation
- Output is saved as a binary file
- Now the program needs `argv[1]` and `argv[2]` as input matrix files
