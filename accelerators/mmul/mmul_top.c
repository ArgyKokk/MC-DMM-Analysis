#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memluv.h"
#include "global.h"

#include "accelerators.c"
#define M 100

#define dmm_scheme 1


void accelerators(float A1[M*M], float B1[M*M], float* C1, float A2[N*N], float B2[N*N], float* C2)
{

  k1(A1,B1,C1);
  k1(A2,B2,C2);
}


