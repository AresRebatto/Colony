#ifndef TERMINAL_H
#define TERMINAL_H
void move_cursor(int row, int col);
void put_pixel(int row, int col, char c);
void disableRawMode();
void enableRawMode();
void terminal_rerender(char *, int, int);
#endif
