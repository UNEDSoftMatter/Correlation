/* #############################################################################
#  Parameters of the simulation 
############################################################################# */

#define NSteps  1000
#define NNodes    10

#define true  1
#define false 0

#define __BINARY_OUTPUT__ false

// If __SUBSTRACT_AVG == true, then FFT of the deviations with respect to the mean
// will be computed, i.e.,
// < (x-\overline{x})(x(t)-\overline{x}) >
// If __SUBSTRACT_AVG == false, then FFT will be computed, i.e.,
// < x x(t) >

#define __SUBSTRACT_AVG__ false
