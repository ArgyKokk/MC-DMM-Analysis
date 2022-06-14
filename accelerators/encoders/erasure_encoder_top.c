#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memluv.h"
#include "global.h"
#include "accelerators.c"

#define scheme 1

#include "encoding_tables.hpp"

#define TOTAL_PACKETS_NUM 6
#define SYMBOLS_NUM 5

#define MAX_GRANULARITY 20000


void accelerators(char coeff_matrix[TOTAL_PACKETS_NUM * SYMBOLS_NUM],
  char inp[SYMBOLS_NUM * MAX_GRANULARITY],
  size_t total_packets_to_encode,
  size_t symbols_num,
  size_t symbol_size,
  char output[TOTAL_PACKETS_NUM * MAX_GRANULARITY], char output1[TOTAL_PACKETS_NUM * MAX_GRANULARITY], char output2[TOTAL_PACKETS_NUM * MAX_GRANULARITY],
  char output3[TOTAL_PACKETS_NUM * MAX_GRANULARITY]) {

  krnl_encoder(coeff_matrix, inp, total_packets_to_encode, symbols_num, symbol_size, output);
  krnl_encoder1(coeff_matrix, inp, total_packets_to_encode, symbols_num, symbol_size, output1);
  krnl_encoder2(coeff_matrix, inp, total_packets_to_encode, symbols_num, symbol_size, output3);
}

