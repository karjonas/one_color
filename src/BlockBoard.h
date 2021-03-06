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

#ifndef __BLOCKBOARD_H__
#define __BLOCKBOARD_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

static const int MAX_ROWS=100;
static const int MAX_COLS=100;
static const int MAX_COLORS=8;

class BlockBoard
{
public:
    BlockBoard(int rows, int cols, int colors, int width, int height);
    void draw_blocks_center(int x, int y);
    ~BlockBoard();
    bool remove_blocks();
    int strongest_color();
    int get_cols() const { return cols;};
    int get_rows() const { return rows;};
    int get_colors() const { return colors;};
    void init(int colors_per_block[]);
 
private:
    int rows;
    int cols;
    int colors;
    int width;
    int height;

    int block_color[MAX_ROWS][MAX_COLS];
    int num_blocks_color[MAX_COLORS];

    int block_size;

};

#endif
