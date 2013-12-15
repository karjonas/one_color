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
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "ColorSelector.h"
#include "ColorList.h"

ColorSelector::ColorSelector(int num_colors, int width, int height)
:
    num_colors(num_colors),
    width(width),
    height(height)
{
    selected_color = num_colors/2;
    block_size = height < width/num_colors ? height : width/num_colors; 
    sample = al_load_sample( "beep.wav" );

};

void ColorSelector::set_num_colors(int n)
{
    num_colors = n;
    selected_color = num_colors/2;
    block_size = height < width/num_colors ? height : width/num_colors;
}

void ColorSelector::draw_center(int x, int y)
{
    int x_offset = x - (num_colors*block_size)/2;
    int y_offset = y - block_size/2;

    for (int color = 0; color < num_colors; color++) 
    {
        int x = x_offset + block_size*color;
        int y = y_offset;
        ALLEGRO_COLOR allegro_color = ColorList::get_color(color);
        
        al_draw_filled_rectangle
        (
            x,
            y,
            x+block_size,
            y+block_size,
            allegro_color
        );
        if (selected_color == color)
        {
            al_draw_rectangle
            (
                x,
                y,
                x+block_size,
                y+block_size,
                ColorList::white(),
                block_size/5
            );
        }
    }

    for (int color = 0; color < num_colors; color++) 
    {
        if (selected_color != color)
        {
            continue;
        }
        int x = x_offset + block_size*color;
        int y = y_offset;
        
        al_draw_rectangle
        (
            x,
            y,
            x+block_size,
            y+block_size,
            ColorList::white(),
            block_size/5
        );
    }
}

void ColorSelector::select_color(int color)
{
    assert(color < num_colors);
    selected_color = color;
}

void ColorSelector::select_color_right()
{
    al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    selected_color = (selected_color + 1) % num_colors;
}

void ColorSelector::select_color_left()
{
    al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    if (selected_color == 0)
        selected_color = num_colors - 1;
    else
        selected_color--;

}

ColorSelector::~ColorSelector()
{
    al_destroy_sample(sample);
};

