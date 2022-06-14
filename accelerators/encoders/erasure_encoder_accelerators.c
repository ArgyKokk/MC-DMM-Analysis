inline char add(const char left,
  const char right) {
  return left ^ right;
}

/// Performs the multiply operation in GF2^8.
inline char multiply(const char left,
  const char right) {
  return product_table[left][right];
}

void compute(const size_t total_packets_to_encode,
  const size_t symbol_size,
    const size_t symbols_num,
      char coeff_matrix_local[TOTAL_PACKETS_NUM][SYMBOLS_NUM],
      char inp_local[SYMBOLS_NUM * MAX_GRANULARITY],
      char output[TOTAL_PACKETS_NUM * MAX_GRANULARITY]) {

#if scheme==1
  char * temp;
  int heap;
  temp = (char * ) MemluvAlloc(MAX_GRANULARITY, 0, & heap);
#else
  char temp[MAX_GRANULARITY]= {0};
#endif

#if scheme==1
  for (size_t i = 0; i < total_packets_to_encode; i++) {
    for (int i = 0; i < symbol_size; i++) {
      if(CheckFlag(heap)){ temp = (char*) UpdateAddress((void*)temp,MAX_GRANULARITY,heap); while(CheckFlag(heap));}
      temp[i] = 0;
    }

    for (size_t j = 0; j < symbols_num; j++) {
      for (size_t ii = 0; ii < symbol_size; ii++) {
    	if(CheckFlag(heap)){temp = (char*) UpdateAddress((void*)temp,MAX_GRANULARITY,heap); while(CheckFlag(heap));}
    	char temp_local = temp[ii];
        temp_local = add(temp_local, multiply(coeff_matrix_local[i][j], inp_local[j * symbol_size + ii]));
      }
    }
    for (int ii = 0; ii < symbol_size; ii++) {
      if(CheckFlag(heap)){temp = (char*) UpdateAddress((void*)temp,MAX_GRANULARITY,heap); while(CheckFlag(heap));}
      char temp_local = temp[ii];
      output[i * symbol_size + ii] = temp_local;

    }
  }
  MemluvFree((void * ) temp, MAX_GRANULARITY, heap);
#else
  for (size_t i = 0; i < total_packets_to_encode; i++) {
    for (int i = 0; i < symbol_size; i++) {
      temp[i] = 0;
    }

    for (size_t j = 0; j < symbols_num; j++) {
      for (size_t ii = 0; ii < symbol_size; ii++) {
        temp[ii] = add(temp[ii], multiply(coeff_matrix_local[i][j], inp_local[j * symbol_size + ii]));
      }
    }
    for (int ii = 0; ii < symbol_size; ii++) {
      output[i * symbol_size + ii] = temp[ii];

    }
  }
#endif

}

void wrapper(const size_t total_packets_to_encode,
  const size_t symbols_num,
    const size_t symbol_size,
      char coeff_matrix_local[TOTAL_PACKETS_NUM][SYMBOLS_NUM],
      char inp_local[SYMBOLS_NUM * MAX_GRANULARITY],
      char output[TOTAL_PACKETS_NUM * MAX_GRANULARITY]) {
  compute(total_packets_to_encode, symbol_size, symbols_num, coeff_matrix_local, inp_local, output);

}

void krnl_encoder(char coeff_matrix[TOTAL_PACKETS_NUM * SYMBOLS_NUM],
  char inp[SYMBOLS_NUM * MAX_GRANULARITY],
  size_t total_packets_to_encode,
  size_t symbols_num,
  size_t symbol_size,
  char output[TOTAL_PACKETS_NUM * MAX_GRANULARITY]) {

  #pragma HLS INTERFACE m_axi port = coeff_matrix offset = slave bundle = gmem0
  #pragma HLS INTERFACE m_axi port = inp offset = slave bundle = gmem1
  #pragma HLS INTERFACE m_axi port = output offset = slave bundle = gmem2


#if scheme==1
  char * inp_local;
  int heap;
  inp_local = (char * ) MemluvAlloc(SYMBOLS_NUM * MAX_GRANULARITY, 0, & heap);
#else
  char inp_local[SYMBOLS_NUM*MAX_GRANULARITY];
#endif

  char coeff_matrix_local[TOTAL_PACKETS_NUM][SYMBOLS_NUM];
  total_packets_to_encode = TOTAL_PACKETS_NUM;
  symbol_size = MAX_GRANULARITY;
  symbols_num = SYMBOLS_NUM;

#if scheme==1
  for (int i = 0; i < symbols_num; i++) {
    #pragma HLS loop_tripcount min = 5 max = 5
    //#pragma HLS PIPELINE II=1
    for (int j = 0; j < symbol_size; j++) {
      #pragma HLS loop_tripcount min = 20000 max = 20000
      if(CheckFlag(heap)) { inp_local = (char*) UpdateAddress((void*)inp_local,MAX_GRANULARITY,heap); while(CheckFlag(heap)); }
      inp_local[i * symbol_size + j] = inp[i * symbol_size + j];
    }
  }
#else
  for (int i = 0; i < symbols_num; i++) {
    #pragma HLS loop_tripcount min = 5 max = 5
    //#pragma HLS PIPELINE II=1
    for (int j = 0; j < symbol_size; j++) {
      #pragma HLS loop_tripcount min = 20000 max = 20000
      inp_local[i * symbol_size + j] = inp[i * symbol_size + j];
    }
  }
#endif

  for (int i = 0; i < total_packets_to_encode; i++) {
    #pragma HLS loop_tripcount min = 6 max = 6
    for (int j = 0; j < symbols_num; j++) {
      #pragma HLS loop_tripcount min = 5 max = 5
      coeff_matrix_local[i][j] = coeff_matrix[i * symbols_num + j];
    }
  }

  wrapper(total_packets_to_encode, symbols_num, symbol_size, coeff_matrix_local, inp_local, output);
#if scheme==1
  MemluvFree((void * ) inp_local, MAX_GRANULARITY * SYMBOLS_NUM, heap);
#endif
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
inline char add1(const char left,
  const char right) {
  return left ^ right;
}

/// Performs the multiply operation in GF2^8.
inline char multiply1(const char left,
  const char right) {
  return product_table[left][right];
}

void compute1(const size_t total_packets_to_encode,
  const size_t symbol_size,
    const size_t symbols_num,
      char coeff_matrix_local[TOTAL_PACKETS_NUM][SYMBOLS_NUM],
      char inp_local[SYMBOLS_NUM * MAX_GRANULARITY],
      char output[TOTAL_PACKETS_NUM * MAX_GRANULARITY]) {

#if scheme==1
  char * temp;
  int heap;
  temp = (char * ) MemluvAlloc(MAX_GRANULARITY, 0, & heap);
#else
  char temp[MAX_GRANULARITY]= {0};
#endif

#if scheme==1
  for (size_t i = 0; i < total_packets_to_encode; i++) {
    for (int i = 0; i < symbol_size; i++) {
      if(CheckFlag(heap)){ temp = (char*) UpdateAddress((void*)temp,MAX_GRANULARITY,heap); while(CheckFlag(heap));}
      temp[i] = 0;
    }

    for (size_t j = 0; j < symbols_num; j++) {
      for (size_t ii = 0; ii < symbol_size; ii++) {
    	if(CheckFlag(heap)){temp = (char*) UpdateAddress((void*)temp,MAX_GRANULARITY,heap); while(CheckFlag(heap));}
    	char temp_local = temp[ii];
        temp_local = add1(temp_local, multiply1(coeff_matrix_local[i][j], inp_local[j * symbol_size + ii]));
      }
    }
    for (int ii = 0; ii < symbol_size; ii++) {
      if(CheckFlag(heap)){temp = (char*) UpdateAddress((void*)temp,MAX_GRANULARITY,heap); while(CheckFlag(heap));}
      char temp_local = temp[ii];
      output1[i * symbol_size + ii] = temp_local;

    }
  }
  MemluvFree((void * ) temp, MAX_GRANULARITY, heap);
#else
  for (size_t i = 0; i < total_packets_to_encode; i++) {
    for (int i = 0; i < symbol_size; i++) {
      temp[i] = 0;
    }

    for (size_t j = 0; j < symbols_num; j++) {
      for (size_t ii = 0; ii < symbol_size; ii++) {
        temp[ii] = add1(temp[ii], multiply1(coeff_matrix_local[i][j], inp_local[j * symbol_size + ii]));
      }
    }
    for (int ii = 0; ii < symbol_size; ii++) {
      output[i * symbol_size + ii] = temp[ii];

    }
  }
#endif

}

void wrapper1(const size_t total_packets_to_encode,
  const size_t symbols_num,
    const size_t symbol_size,
      char coeff_matrix_local[TOTAL_PACKETS_NUM][SYMBOLS_NUM],
      char inp_local[SYMBOLS_NUM * MAX_GRANULARITY],
      char output[TOTAL_PACKETS_NUM * MAX_GRANULARITY]) {
  compute(total_packets_to_encode, symbol_size, symbols_num, coeff_matrix_local, inp_local, output);

}

void krnl_encoder1(char coeff_matrix[TOTAL_PACKETS_NUM * SYMBOLS_NUM],
  char inp[SYMBOLS_NUM * MAX_GRANULARITY],
  size_t total_packets_to_encode,
  size_t symbols_num,
  size_t symbol_size,
  char output[TOTAL_PACKETS_NUM * MAX_GRANULARITY]) {

  #pragma HLS INTERFACE m_axi port = coeff_matrix offset = slave bundle = gmem0
  #pragma HLS INTERFACE m_axi port = inp offset = slave bundle = gmem1
  #pragma HLS INTERFACE m_axi port = output offset = slave bundle = gmem2


#if scheme==1
  char * inp_local;
  int heap;
  inp_local = (char * ) MemluvAlloc(SYMBOLS_NUM * MAX_GRANULARITY, 0, & heap);
#else
  char inp_local[SYMBOLS_NUM*MAX_GRANULARITY];
#endif

  char coeff_matrix_local[TOTAL_PACKETS_NUM][SYMBOLS_NUM];
  total_packets_to_encode = TOTAL_PACKETS_NUM;
  symbol_size = MAX_GRANULARITY;
  symbols_num = SYMBOLS_NUM;

#if scheme==1
  for (int i = 0; i < symbols_num; i++) {
    #pragma HLS loop_tripcount min = 5 max = 5
    //#pragma HLS PIPELINE II=1
    for (int j = 0; j < symbol_size; j++) {
      #pragma HLS loop_tripcount min = 20000 max = 20000
      if(CheckFlag(heap)) { inp_local = (char*) UpdateAddress((void*)inp_local,MAX_GRANULARITY,heap); while(CheckFlag(heap)); }
      inp_local[i * symbol_size + j] = inp[i * symbol_size + j];
    }
  }
#else
  for (int i = 0; i < symbols_num; i++) {
    #pragma HLS loop_tripcount min = 5 max = 5
    //#pragma HLS PIPELINE II=1
    for (int j = 0; j < symbol_size; j++) {
      #pragma HLS loop_tripcount min = 20000 max = 20000
      inp_local[i * symbol_size + j] = inp[i * symbol_size + j];
    }
  }
#endif

  for (int i = 0; i < total_packets_to_encode; i++) {
    #pragma HLS loop_tripcount min = 6 max = 6
    for (int j = 0; j < symbols_num; j++) {
      #pragma HLS loop_tripcount min = 5 max = 5
      coeff_matrix_local[i][j] = coeff_matrix[i * symbols_num + j];
    }
  }

 wrapper1(total_packets_to_encode, symbols_num, symbol_size, coeff_matrix_local, inp_local, output);
#if scheme==1
  MemluvFree((void * ) inp_local, MAX_GRANULARITY * SYMBOLS_NUM, heap);
#endif
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
inline char add2(const char left,
  const char right) {
  return left ^ right;
}

/// Performs the multiply operation in GF2^8.
inline char multiply2(const char left,
  const char right) {
  return product_table[left][right];
}

void compute2(const size_t total_packets_to_encode,
  const size_t symbol_size,
    const size_t symbols_num,
      char coeff_matrix_local[TOTAL_PACKETS_NUM][SYMBOLS_NUM],
      char inp_local[SYMBOLS_NUM * MAX_GRANULARITY],
      char output[TOTAL_PACKETS_NUM * MAX_GRANULARITY]) {

#if scheme==1
  char * temp;
  int heap;
  temp = (char * ) MemluvAlloc(MAX_GRANULARITY, 0, & heap);
#else
  char temp[MAX_GRANULARITY]= {0};
#endif

#if scheme==1
  for (size_t i = 0; i < total_packets_to_encode; i++) {
    for (int i = 0; i < symbol_size; i++) {
      if(CheckFlag(heap)){ temp = (char*) UpdateAddress((void*)temp,MAX_GRANULARITY,heap); while(CheckFlag(heap));}
      temp[i] = 0;
    }

    for (size_t j = 0; j < symbols_num; j++) {
      for (size_t ii = 0; ii < symbol_size; ii++) {
    	if(CheckFlag(heap)){temp = (char*) UpdateAddress((void*)temp,MAX_GRANULARITY,heap); while(CheckFlag(heap));}
    	char temp_local = temp[ii];
        temp_local = add2(temp_local, multiply2(coeff_matrix_local[i][j], inp_local[j * symbol_size + ii]));
      }
    }
    for (int ii = 0; ii < symbol_size; ii++) {
      if(CheckFlag(heap)){temp = (char*) UpdateAddress((void*)temp,MAX_GRANULARITY,heap); while(CheckFlag(heap));}
      char temp_local = temp[ii];
      output[i * symbol_size + ii] = temp_local;

    }
  }
  MemluvFree((void * ) temp, MAX_GRANULARITY, heap);
#else
  for (size_t i = 0; i < total_packets_to_encode; i++) {
    for (int i = 0; i < symbol_size; i++) {
      temp[i] = 0;
    }

    for (size_t j = 0; j < symbols_num; j++) {
      for (size_t ii = 0; ii < symbol_size; ii++) {
        temp[ii] = add2(temp[ii], multiply2(coeff_matrix_local[i][j], inp_local[j * symbol_size + ii]));
      }
    }
    for (int ii = 0; ii < symbol_size; ii++) {
      output[i * symbol_size + ii] = temp[ii];

    }
  }
#endif

}

void wrapper2(const size_t total_packets_to_encode,
  const size_t symbols_num,
    const size_t symbol_size,
      char coeff_matrix_local[TOTAL_PACKETS_NUM][SYMBOLS_NUM],
      char inp_local[SYMBOLS_NUM * MAX_GRANULARITY],
      char output[TOTAL_PACKETS_NUM * MAX_GRANULARITY]) {
  compute2(total_packets_to_encode, symbol_size, symbols_num, coeff_matrix_local, inp_local, output);

}

void krnl_encoder2(char coeff_matrix[TOTAL_PACKETS_NUM * SYMBOLS_NUM],
  char inp[SYMBOLS_NUM * MAX_GRANULARITY],
  size_t total_packets_to_encode,
  size_t symbols_num,
  size_t symbol_size,
  char output[TOTAL_PACKETS_NUM * MAX_GRANULARITY]) {

  #pragma HLS INTERFACE m_axi port = coeff_matrix offset = slave bundle = gmem0
  #pragma HLS INTERFACE m_axi port = inp offset = slave bundle = gmem1
  #pragma HLS INTERFACE m_axi port = output offset = slave bundle = gmem2


#if scheme==1
  char * inp_local;
  int heap;
  inp_local = (char * ) MemluvAlloc(SYMBOLS_NUM * MAX_GRANULARITY, 0, & heap);
#else
  char inp_local[SYMBOLS_NUM*MAX_GRANULARITY];
#endif

  char coeff_matrix_local[TOTAL_PACKETS_NUM][SYMBOLS_NUM];
  total_packets_to_encode = TOTAL_PACKETS_NUM;
  symbol_size = MAX_GRANULARITY;
  symbols_num = SYMBOLS_NUM;

#if scheme==1
  for (int i = 0; i < symbols_num; i++) {
    #pragma HLS loop_tripcount min = 5 max = 5
    //#pragma HLS PIPELINE II=1
    for (int j = 0; j < symbol_size; j++) {
      #pragma HLS loop_tripcount min = 20000 max = 20000
      if(CheckFlag(heap)) { inp_local = (char*) UpdateAddress((void*)inp_local,MAX_GRANULARITY,heap); while(CheckFlag(heap)); }
      inp_local[i * symbol_size + j] = inp[i * symbol_size + j];
    }
  }
#else
  for (int i = 0; i < symbols_num; i++) {
    #pragma HLS loop_tripcount min = 5 max = 5
    //#pragma HLS PIPELINE II=1
    for (int j = 0; j < symbol_size; j++) {
      #pragma HLS loop_tripcount min = 20000 max = 20000
      inp_local[i * symbol_size + j] = inp[i * symbol_size + j];
    }
  }
#endif

  for (int i = 0; i < total_packets_to_encode; i++) {
    #pragma HLS loop_tripcount min = 6 max = 6
    for (int j = 0; j < symbols_num; j++) {
      #pragma HLS loop_tripcount min = 5 max = 5
      coeff_matrix_local[i][j] = coeff_matrix[i * symbols_num + j];
    }
  }

  wrapper2(total_packets_to_encode, symbols_num, symbol_size, coeff_matrix_local, inp_local, output);
#if scheme==1
  MemluvFree((void * ) inp_local, MAX_GRANULARITY * SYMBOLS_NUM, heap);
#endif
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
