void* UpdateAddress(void* address, uint_t nbytes ,uint_t heap_id) {
#ifdef __SYNTHESIS__
#pragma AP inline
#endif
	switch ( heap_id ) {

	case 1:
		return ((void*)CurUpdateAddress(address, nbytes ,&MemLuvCore1));
		break;
	default:
		return ((void*)CurUpdateAddress(address, nbytes ,&MemLuvCore0));
		break;
	}
}

uint8_t CheckFlag(uint_t heap_id)
{
	switch (heap_id){
		case 1:
			return MemLuvCore1.compactionFlag;
		default:
			return MemLuvCore0.compactionFlag;
	}
}
