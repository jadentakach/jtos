#include "gfx.h"

void put_pixel(int x, int y, unsigned char color) {
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
void put_xline(int x1, int x2, int y, int w, unsigned char color) {
        for (int j = 0; j < w; j++) {
                for (int i = x1; i < x2; i++) {
                        put_pixel(i, y+j, color);
                }
        }
}

// y1 - initial y point
// y2 - end y point
// w - width
void put_yline(int y1, int y2, int x, int w, unsigned char color) {
        for (int j = 0; j < w; j++) {
                for (int i = y1; i < y2; i++) {
                        put_pixel(x+j, i, color);
                }
        }
}

void fill_screen(unsigned char color) {
        for (int i = 0; i < SCREEN_WIDTH; i++) {
                for (int j = 0; j < SCREEN_HEIGHT; j++) {
                        put_pixel(i, j, color);
                }
        }
}

void clear_screen() {
        fill_screen(0x0);
}
