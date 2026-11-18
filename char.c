#pragma once
#include "kernel.h"

void draw_char(character* c) {
	put_map(5, 5, c->design);
}
