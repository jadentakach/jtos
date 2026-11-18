#define VGA_MEMORY ((unsigned char*)0xA0000)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

/*
void outb(unsigned short port, unsigned char value) {
	__asm volatile (
		"outb %0, %1"
		:
		: "a"(value), "Nd"(port)
	);
}

unsigned char inb(unsigned short port) {
	unsigned char result;

	__asm__ volatile (
		"inb %1, %0"
		: "=a"(result)
		: "Nd"(port)
	);

	return result;
}

void keyboard_init() {
	outb(0x64, 0xAE);
}

int keyboard_available() {
	return inb(0x64) & 1;
}

int keyboard_read() {
	if (!keyboard_available()) return -1;

	return inb(0x60);
}*/

void put_pixel(int x, int y, unsigned short color) {
	VGA_MEMORY[y * SCREEN_WIDTH + x] = color;
}

// xb - x bounds
// yb - y bounds
void put_map(int xb, int yb, unsigned char map[yb][xb]) {
	for (int i = 0; i < xb; i++) {
		for (int j = 0; j < yb; j++) {
			put_pixel(i, j, map[j][i]);
		}
	}

}

// x1 - initial x point
// x2 - end x point
// w - width
void put_xline(int x1, int x2, int y, int w, unsigned short color) {
	for (int j = 0; j < w; j++) {
		for (int i = x1; i < x2; i++) {
			put_pixel(i, y+j, color);
		}
	}
}

// y1 - initial y point
// y2 - end y point
// w - width
void put_yline(int y1, int y2, int x, int w, unsigned short color) {
	for (int j = 0; j < w; j++) {
		for (int i = y1; i < y2; i++) {
			put_pixel(x+j, i, color);
		}
	}
}

void fill_screen(unsigned short color) {
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT; j++) {
			put_pixel(i, j, color);
		}
	}
}

void clear_screen() {
	fill_screen(0x0);
}

typedef struct character {
	int width;
	int font_size;
	unsigned char pattern[width][font_size];
};

unsigned char msg[5][5] = {
	{0x04, 0x04, 0x04, 0x04, 0x04},
	{0x04, 0x0E, 0x0E, 0x0E, 0x04},
	{0x04, 0x04, 0x0E, 0x04, 0x04},
	{0x04, 0x04, 0x0E, 0x04, 0x04},
	{0x04, 0x0E, 0x0E, 0x04, 0x04}
};

void main() {
	fill_screen(0x0E);
	put_xline(25, 75, 50, 5, 0x5);
}
