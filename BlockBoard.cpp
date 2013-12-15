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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "BlockBoard.h"
#include "ColorList.h"

BlockBoard::BlockBoard
(
    int rows,
    int cols,
    int colors,
    int width,
    int height
) :
    rows(rows),
    cols(cols),
    colors(colors),
    width(width),
    height(height)
{    
}

void BlockBoard::init(int blocks_per_color[])
{
    assert(cols < MAX_COLS);
    assert(rows < MAX_ROWS);
    assert(colors > 1);
    
    // Calculate block size
    block_size = height/rows < width/cols ? height/rows : width/cols;

    assert(sizeof(blocks_per_color) >= (uint)colors);
    
    int total_blocks = 0;
    int added_blocks_per_color[sizeof(blocks_per_color)];
    for(int i = 0; i < colors; i++)
    {
        total_blocks += blocks_per_color[i];
        added_blocks_per_color[i] = 0;
        num_blocks_color[i] = 0;
    }
    
    assert(total_blocks == rows*cols);
    
    srand(time(NULL));
    
    // Shuffle colors
    for(int i = 0; i < colors; i++)
    {
        int rnd = rand() % colors;
        int tmp = blocks_per_color[i];
        blocks_per_color[i] = blocks_per_color[rnd];
        blocks_per_color[rnd] = tmp;
    }
    
    for(int row = 0; row < rows; row++)
    {
        srand(rand());
        for (int col = 0; col < cols; col++) 
        {
            bool done = false;
            while (!done)
            {
                int rnd = rand() % total_blocks;
                int val = 0;
                int color = 0;

                for (int i = 0; i < colors; i++)
                {
                    val += blocks_per_color[i];
                    if (rnd < val)
                    {
                        color = i;
                        break;
                    }
                }
                
                if (added_blocks_per_color[color] < blocks_per_color[color])
                {
                    done = true;
                }
                else
                {
                    continue;
                }
                num_blocks_color[color] = num_blocks_color[color] + 1;
                block_color[row][col] = color;
                added_blocks_per_color[color] = added_blocks_per_color[color]+1;
            }
        }
    }

    
}

void BlockBoard::draw_blocks_center(int x, int y)
{
    int x_offset = x - (cols*block_size)/2;
    int y_offset = y - (rows*block_size)/2;
        
    for(int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++) 
        {
            int x = x_offset + block_size*col;
            int y = y_offset + block_size*row;
            int color = block_color[row][col];
            if(color == -1) continue;
            ALLEGRO_COLOR allegro_color = ColorList::get_color(color);      
            
            al_draw_filled_rectangle(x, y, x+block_size, y+block_size, allegro_color);
        }
    }
}

int BlockBoard::strongest_color()
{
    bool unique = true;
    int strongest = 0;

    for(int i = 1; i < colors; i++)
    {
        if (num_blocks_color[i] > num_blocks_color[strongest])
        {
            strongest = i;
            unique = true;
        }
        else if(num_blocks_color[i] == num_blocks_color[strongest])
        {
            unique = false;
        }
    }
    
    assert(unique);
    return strongest;
    
}

bool BlockBoard::remove_blocks()
{
    bool color_removed[colors];
    int num_colors_left = 0;
    for(int i = 0; i < colors; i++)
    {
        color_removed[i] = false;
        if (num_blocks_color[i] > 0)
        {
            num_colors_left++;
        }
    }
    
    if (num_colors_left == 1)
    {
        return false;
    }
    
    for(int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++) 
        {
            int color = block_color[row][col];
            if (color >= 0 && !color_removed[color])
            {
                block_color[row][col] = -1;
                num_blocks_color[color] = num_blocks_color[color] - 1;
                color_removed[color] = true;
            }
        }
    }
    return true;
}

BlockBoard::~BlockBoard(){};
