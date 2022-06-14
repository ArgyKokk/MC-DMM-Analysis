void k1(float* A1, float* B1, float* C1)
{
  #pragma HLS INLINE OFF

#if dmm_scheme==1
  float * A1_local, * B1_local, * C1_local;
  int heap0, heap1, heap2;
  A1_local = (float *)MemluvAlloc(M*M * sizeof(float),0 ,&heap0);
  B1_local = (float *)MemluvAlloc(M*M * sizeof(float),0, &heap1);
  C1_local = (float *)MemluvAlloc(M*M * sizeof(float),0, &heap2);

  if(CheckFlag(heap0)) {while(CheckFlag(heap0)); A1_local = (float *) UpdateAddress((void*)A1_local,M*M*sizeof(float),heap0); }
  memcpy(A1_local,A1,M*M*sizeof(float));
  if(CheckFlag(heap1)) {while(CheckFlag(heap1)); B1_local = (float *) UpdateAddress((void*)B1_local,M*M*sizeof(float),heap1); }
  memcpy(B1_local,B1,M*M*sizeof(float));
  if(CheckFlag(heap2)){ C1_local = (float *) UpdateAddress((void*)C1_local,M*M*sizeof(float),heap2); while(CheckFlag(heap2));}
  memcpy(C1_local,C1,M*M*sizeof(float));

#else
  float A1_local[M*M];
  float B1_local[M*M];
  float C1_local[M*M];

  memcpy(A1_local,A1,M*M*sizeof(float));
  memcpy(B1_local,B1,M*M*sizeof(float));
  memcpy(C1_local,C1,M*M*sizeof(float));
#endif


  for(int i=0; i< M; i++)
  {
#if dmm_scheme==1
    for(int j=0; j< M; j++)
    {
      float temp = 0;
      for(int k=0; k < M; k++){

    	if(CheckFlag(heap0)) {while(CheckFlag(heap0)); A1_local = (float *) UpdateAddress((void*)A1_local,M*M*sizeof(float),heap0); }
    	float temp_A = A1_local[i*M+k];
    	if(CheckFlag(heap1)) {while(CheckFlag(heap1)); B1_local = (float *) UpdateAddress((void*)B1_local,M*M*sizeof(float),heap1); }
    	float temp_B = B1_local[k*M+j];
        temp += temp_A * temp_B;
      }
         if(CheckFlag(heap2)){ C1_local = (float *) UpdateAddress((void*)C1_local,M*M*sizeof(float),heap2); while(CheckFlag(heap2));}
         C1_local[i*M+j] = temp;
    }
#else
    for(int j=0; j< M; j++)
    {
      float temp = 0;
      for(int k=0; k < M; k++){
        temp += A1_local[i*M+k] * B1_local[k*M+j];
      }
         C1_local[i*M+j] = temp;
    }
#endif

  }
#if dmm_scheme==1
  if(CheckFlag(heap2)){C1_local = (float *) UpdateAddress((void*)A1_local,M*M*sizeof(float),heap2); while(CheckFlag(heap2));}
  memcpy(C1,C1_local,M*M*sizeof(float));
#else
  memcpy(C1,C1_local,M*M*sizeof(float));
#endif
  MemluvFree((void*)A1_local, M*M * sizeof(float), heap0);
  MemluvFree((void*)B1_local, M*M * sizeof(float), heap1);
  MemluvFree((void*)C1_local, M*M * sizeof(float), heap2);

}


void k2(float* A1, float* B1, float* C1)
{
  #pragma HLS INLINE OFF

#if dmm_scheme==1
  float * A1_local, * B1_local, * C1_local;
  int heap0, heap1, heap2;
  A1_local = (float *)MemluvAlloc(M*M * sizeof(float),0 ,&heap0);
  B1_local = (float *)MemluvAlloc(M*M * sizeof(float),0, &heap1);
  C1_local = (float *)MemluvAlloc(M*M * sizeof(float),0, &heap2);

  if(CheckFlag(heap0)) {while(CheckFlag(heap0)); A1_local = (float *) UpdateAddress((void*)A1_local,M*M*sizeof(float),heap0); }
  memcpy(A1_local,A1,M*M*sizeof(float));
  if(CheckFlag(heap1)) {while(CheckFlag(heap1)); B1_local = (float *) UpdateAddress((void*)B1_local,M*M*sizeof(float),heap1); }
  memcpy(B1_local,B1,M*M*sizeof(float));
  if(CheckFlag(heap2)){ C1_local = (float *) UpdateAddress((void*)C1_local,M*M*sizeof(float),heap2); while(CheckFlag(heap2));}
  memcpy(C1_local,C1,M*M*sizeof(float));

#else
  float A1_local[M*M];
  float B1_local[M*M];
  float C1_local[M*M];

  memcpy(A1_local,A1,M*M*sizeof(float));
  memcpy(B1_local,B1,M*M*sizeof(float));
  memcpy(C1_local,C1,M*M*sizeof(float));
#endif


  for(int i=0; i< M; i++)
  {
#if dmm_scheme==1
    for(int j=0; j< M; j++)
    {
      float temp = 0;
      for(int k=0; k < M; k++){

    	if(CheckFlag(heap0)) {while(CheckFlag(heap0)); A1_local = (float *) UpdateAddress((void*)A1_local,M*M*sizeof(float),heap0); }
    	float temp_A = A1_local[i*M+k];
    	if(CheckFlag(heap1)) {while(CheckFlag(heap1)); B1_local = (float *) UpdateAddress((void*)B1_local,M*M*sizeof(float),heap1); }
    	float temp_B = B1_local[k*M+j];
        temp += temp_A * temp_B;
      }
         if(CheckFlag(heap2)){ C1_local = (float *) UpdateAddress((void*)C1_local,M*M*sizeof(float),heap2); while(CheckFlag(heap2));}
         C1_local[i*M+j] = temp;
    }
#else
    for(int j=0; j< M; j++)
    {
      float temp = 0;
      for(int k=0; k < M; k++){
        temp += A1_local[i*M+k] * B1_local[k*M+j];
      }
         C1_local[i*M+j] = temp;
    }
#endif

  }
#if dmm_scheme==1
  if(CheckFlag(heap2)){C1_local = (float *) UpdateAddress((void*)A1_local,M*M*sizeof(float),heap2); while(CheckFlag(heap2));}
  memcpy(C1,C1_local,M*M*sizeof(float));
#else
  memcpy(C1,C1_local,M*M*sizeof(float));
#endif
  MemluvFree((void*)A1_local, M*M * sizeof(float), heap0);
  MemluvFree((void*)B1_local, M*M * sizeof(float), heap1);
  MemluvFree((void*)C1_local, M*M * sizeof(float), heap2);

}

