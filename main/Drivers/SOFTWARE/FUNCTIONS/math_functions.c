#include "math_functions.h"

/********************************************************************************************/
float map(float Value, float InputMin, float InputMax, float OutputMin, float OutputMax) {
  return ((Value - InputMin) * (OutputMax - OutputMin)) / ((InputMax - InputMin) + OutputMin);
}
