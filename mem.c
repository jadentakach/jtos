#include "mem.h"

static unsigned char pool[POOL_SIZE];
static unsigned int offset = 0;

void* jtalloc(unsigned int size) {
	if ((size + offset) > POOL_SIZE) return (void*)0;
	void* ptr = &pool[offset];
	offset += size;
	return ptr;
}
