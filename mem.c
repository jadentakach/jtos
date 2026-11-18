#include "mem.h"

void* jtalloc(unsigned int size) {
	if ((size + offset) > POOL_SIZE) return NULL;
	void* ptr = &pool[offset];
	offset += size;
	return ptr;
}
