#ifndef TERMINAL
#define TERMINAL
void move_cursor(int row, int col);
void put_pixel(int row, int col, char c);
void disableRawMode();
void enableRawMode();
void terminal_rerender(char *, int, int);
#endif
