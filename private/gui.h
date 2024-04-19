#include <stdio.h>
#include <ncurses/ncurses.h>

#ifndef GUI_H
#define GUI_H
void print_menu_1(WINDOW *win1, int h1);
void print_menu_2(WINDOW *win2, int x, int y);
void start(WINDOW *win);

void profile(WINDOW *win);
void flights(WINDOW *win);
void trains(WINDOW *win);
void buses(WINDOW *win);
void wayfarer(WINDOW *win);

#endif
