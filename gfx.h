#define VGA_MEMORY ((unsigned char*)0xA0000)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

void put_pixel(int x, int y, unsigned char color);
void put_map(int xb, int yb, unsigned char map[yb][xb]);
void put_xline(int x1, int x2, int y, int w, unsigned char color);
void put_yline(int y1, int y2, int x, int w, unsigned char color);
void fill_screen(unsigned char color);
void clear_screen();
