

void compaction(MemLuvCore *CurMemLuvCore)
{
#pragma HLS INLINE OFF
#pragma HLS ALLOCATION function instances=compaction limit=1
	printf("compaction \n");
	printf("--------------\n" );
//	printf("Freelist total bits: %d \n",CurMemLuvCore->freelist_total_bits);
//	printf("Freelist element size: %d \n",sizeof(FREELIST_UINT_T));
//	printf("Freelist size: %d \n",MEMLUV_DEPTH*sizeof(CORE_UINT_T)/(sizeof(FREELIST_UINT_T)*8));
	uint_t i, max_marked_bit_flag=0;
  // A RAM memory of 1-bit words and MEMLUV_DEPTH (HEAP SIZE) depth
	uint8_t heapInfo[MEMLUV_DEPTH];

	//----------------
  // set compaction flag to '1' and stall the accelerators
	CurMemLuvCore->compactionFlag = 1;

	// Pass the heap and check the positions that are occupied
	LOOP1_COMP:for(i=CurMemLuvCore->freelist_total_bits; i> 0; i=i-sizeof(CORE_UINT_T))
	{
	//	#pragma HLS LOOP_TRIPCOUNT min=512 max=2048
		uint8_t note;
		if (MemluvTestBitFreelist(CurMemLuvCore->freelist, i-1) == 1)
			note = 1;
		else
			note = 0;
			int index = i / sizeof(CORE_UINT_T) -1;
	  	heapInfo[index] = note;
	}
	for(int i=0; i< MEMLUV_DEPTH; i++)

		 int holeSize = 0;
		 int slotCounter = 0;
		 CORE_UINT_T* startAddress = NULL;
		 CORE_UINT_T* stopAddress = NULL;
		 int stopHole = 0;

		 for(int i=0; i< MEMLUV_DEPTH; i++)
		 {
			 // if a hole is spotted
			 if(heapInfo[i]==0) 	slotCounter++;
			 else
			 {
				 if(slotCounter > holeSize){
				 		holeSize = slotCounter;
				 		startAddress = CurMemLuvCore->base + i-holeSize;
				 		stopAddress = CurMemLuvCore->base+i-1;
						stopHole = i;
			 		}
				 slotCounter = 0;
			 }
		 }

		 for(int j=stopHole; j<MEMLUV_DEPTH; j++)
		 {

			 if(heapInfo[j]==1)  // if occupied then move it n (holesize) positions upwards
			 {
				 CurMemLuvCore->core[j-holeSize] = CurMemLuvCore->core[j];
				 CurMemLuvCore->offsets[j] = -holeSize; // update the offset table
				 // set the j - holesize bits as occupied and the j bits as free
				 for(int i=0; i< sizeof(CORE_UINT_T); i++)
				 {
					 MemluvClearBitFreelist(CurMemLuvCore->freelist, j * sizeof(CORE_UINT_T) + i );
					 MemluvSetBitFreelist(CurMemLuvCore->freelist, (j-holeSize) * sizeof(CORE_UINT_T) + i);
				 }
			 }
		 }
}
