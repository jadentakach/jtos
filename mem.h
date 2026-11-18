#define POOL_SIZE 1024

static unsigned char pool[POOL_SIZE];
static unsigned int offset = 0;

void* jtalloc(unsigned int size);
