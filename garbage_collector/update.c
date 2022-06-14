void* CurUpdateAddress(void* Address, uint_t nbytes ,MemLuvCore *CurMemLuvCore )
{
#pragma AP inline
 
  int posC;
   
  LOOP1_CUR:for(int i=0; i< MEMLUV_DEPTH; i++)
  {
    #pragma HLS LOOP_TRIPCOUNT min=8 max=2048
    if((uint64_t)Address==(uint64_t)(CurMemLuvCore->base + i))
    {
      posC = i;
    }
  }
  printf("Address %p was moved %d positions and occupied %d slots\n",Address,CurMemLuvCore->offsets[posC], nbytes/sizeof(CORE_UINT_T));
  int offset = CurMemLuvCore->offsets[posC]; 
 
  LOOP2_CUR:for(int i=posC; i< (posC+nbytes / sizeof(CORE_UINT_T)); i++){
    #pragma HLS LOOP_TRIPCOUNT min=1 max=2048
    CurMemLuvCore->offsets[i] = 0;
  }
  
  int zeros = 0;
  LOOP3_CUR:for(int i=0; i< MEMLUV_DEPTH;i++){
    #pragma HLS LOOP_TRIPCOUNT min=8 max=2048
    printf("offset Address %p was moved %d slots \n",CurMemLuvCore->base + i,CurMemLuvCore->offsets[i]);
    if(CurMemLuvCore->offsets[i]==0)
      zeros++;
  }
   
  if(zeros==MEMLUV_DEPTH)
  {
    printf("RESETING FLAG \n");
    CurMemLuvCore->compactionFlag = 0;
  } 
   return (void*)(Address+offset * sizeof(CORE_UINT_T)); 

}
