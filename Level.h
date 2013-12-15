/*
The MIT License (MIT)

Copyright (c) 2013 Jonas Karlsson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "BlockBoard.h"
#include "ColorSelector.h"

class Level
{
public:
    Level();
    ~Level();
    int strongest_color() {return board.strongest_color();};
    bool remove_blocks() {return board.remove_blocks();};
    void draw_blocks_center(int x, int y) {board.draw_blocks_center(x,y);};
    void next_level();
    int get_num_colors() {return num_colors;};
    const char* get_level_string();

private:
    char to_char(int i);
    void create_level(int rows, int cols, int num_colors, int percent_diff);
    void create_level_string();
    BlockBoard board;
    char level_string[10];
    int blocks_per_color[10];
    int level_number;
    int num_colors;
};

#endif
