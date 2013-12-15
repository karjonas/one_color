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
#include <allegro5/allegro.h> 
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Level.h"

Level::Level() :
    board(BlockBoard(3, 2, 2, 400, 280))
{
    int blocks_per_color[2] = {4,2};
    board.init(blocks_per_color);
    level_number = -1;
    num_colors = 2;
};

void Level::create_level_string()
{
    level_string[0] = 'L';
    level_string[1] = 'E';
    level_string[2] = 'V';
    level_string[3] = 'E';
    level_string[4] = 'L';
    level_string[5] = ' ';
    
    if (level_number >= 100)
    {
        level_string[6] = to_char((level_number%1000)/100);
        level_string[7] = to_char((level_number%100)/10);
        level_string[8] = to_char(level_number%10);
        level_string[9] = '\0';
    }
    else if (level_number >= 10)
    {
        
        level_string[6] = to_char((level_number%100)/10);
        level_string[7] = to_char(level_number%10);
        level_string[8] = '\0';
    }
    else
    {
        level_string[6] = to_char(level_number);
        level_string[7] = '\0';
    }
}


char Level::to_char(int i)
{
    switch(i)
    {
    case 9: return '9';
    case 8: return '8';
    case 7: return '7';
    case 6: return '6';
    case 5: return '5';
    case 4: return '4';
    case 3: return '3';
    case 2: return '2';
    case 1: return '1';
    }
    return '0';
}
const char* Level::get_level_string()
{
    return level_string;
}


void Level::create_level(int rows, int cols, int num_colors, int percent_diff)
{
    board = BlockBoard(rows, cols, num_colors, 400, 280);
    int base_percent = 100/num_colors;
    int win_color_percent = base_percent + percent_diff;
    int lose_color_percent =  base_percent - (percent_diff / (num_colors - 1));
    int total_blocks = rows*cols;
    int blocks_per_color[10];
    

    blocks_per_color[0] = (total_blocks * win_color_percent)/100;

    for(int i = 1; i < num_colors; i++)
    {
        blocks_per_color[i] = (total_blocks * lose_color_percent)/100;
    }

    int bsize = 0;
    for(int i = 0; i < num_colors; i++)
    {
        bsize += blocks_per_color[i];
    }

    int diff = bsize - total_blocks;
    if (diff < 0)
    {
        blocks_per_color[0] = blocks_per_color[0] - diff;
    }
    else
    {
        blocks_per_color[1] = blocks_per_color[1] - diff;
    }
            
    board.init(blocks_per_color);

    
}

void Level::next_level()
{
    level_number++;
    create_level_string();
    int prev_rows = board.get_rows();
    int prev_cols = board.get_cols();
    if (level_number < 3 ) {
        num_colors = 2;
        create_level(prev_rows + 1, prev_cols + 1, num_colors, 5);
    }
    else if (level_number < 5) {
        num_colors = 3;
        create_level(prev_rows - 1, prev_cols - 1, num_colors, 10);
    }
    else if (level_number < 10) {
        num_colors = 3;
        create_level(prev_rows + 1, prev_cols + 1, num_colors, 10);
    }
    else if (level_number == 10) {
        num_colors = 4;
        create_level(3, 3, num_colors, 10);
    }
    else if (level_number < 20) {
        num_colors = 4;
        create_level(prev_rows + 1 , prev_cols + 1, num_colors, 10);
    }
    else if (level_number == 20) {
        num_colors = 5;
        create_level(4,4, num_colors, 20);
    }
    else if (level_number < 25) {
        num_colors = 5;
        create_level(prev_rows, prev_cols + 1, num_colors, 10);
    }
    else if (level_number < 30) {
        num_colors = 5;
        create_level(prev_rows + 1, prev_cols, num_colors, 10);
    }
    else if (level_number == 30) {
        num_colors = 6;
        create_level(10, 6, num_colors, 10);
    }
    else if (level_number < 35)
    {
        num_colors = 6;
        create_level(prev_rows + 1,prev_cols + 1, num_colors, 5);
    }
    else if (level_number == 35)
    {
        num_colors = 7;
        create_level(6, 10, num_colors, 5);
    }
    else if (level_number < 45)
    {
        create_level(prev_rows + 1, prev_cols + 2, num_colors, 5);
    }
    else if (level_number == 45)
    {
        num_colors = 7;
        create_level(16, 30, num_colors, 5);
    }
    else
    {
        num_colors = 7;
        create_level(prev_rows + 1,prev_cols + 2, num_colors, 5);
    }

};

Level::~Level(){};

