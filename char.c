#pragma once
#include "kernel.h"

void putchar(character* c) {
	put_map(5, 5, c->design);
}
