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
#include "MainLoop.h"

MainLoop::MainLoop() :
    color_selector(2,400, 80)
{
    state = SPLASH_SCREEN;
    font = al_load_ttf_font("data/PressStart2P.ttf",72,0 );
    font_splash_big = al_load_ttf_font("data/PressStart2P.ttf",48,0 );
    font_splash_small = al_load_ttf_font("data/PressStart2P.ttf",24,0 );
    alpha = 255;
    selected_color = 0;
    done_selecting = false;
    win = al_load_sample( "data/level_win.wav" );
    alert = al_load_sample( "data/alert.wav" );
};

bool MainLoop::tick()
{
    switch(state) {
    case SPLASH_SCREEN:
        break;
    case INSTRUCTIONS:
        if (countdown_value-- < 0)
        {
            state = LEVEL_NAME;
            level.next_level();
            start_countdown(1);
        }
        break;
    case LEVEL_NAME:
        if (countdown_value-- < 0)
        {
            state = COUNTDOWN;
            start_countdown(10);

            color_selector.set_num_colors(level.get_num_colors());
            done_selecting=false;
        }
        break;
    case COUNTDOWN:
        strongest_color = level.strongest_color();

        if (done_selecting)
        {
            state = REMOVE_BLOCKS;
            break;
        }
        if (countdown_value <= 0)
        {
            state = REMOVE_BLOCKS;
            break;
        }

        countdown_value--;
        alpha = (countdown_value%60) > 30 ? 255 : (countdown_value%60)*(255/30);
        switch (countdown_value/60)
        {
        case 9: countdown_text[0] = ' '; break;
        case 8: countdown_text[0] = ' '; break;
        case 7: countdown_text[0] = ' '; break;
        case 6: countdown_text[0] = ' '; break;
        case 5: countdown_text[0] = ' '; break;
        case 4: countdown_text[0] = '5'; break;
        case 3: countdown_text[0] = '4'; break;
        case 2: countdown_text[0] = '3'; break;
        case 1: countdown_text[0] = '2'; break;
        default: countdown_text[0] = '1'; break;
        }
        
        if (countdown_value/60 > 0 && countdown_value/60 < 6 && (countdown_value % 60) == 0)
        {
            al_play_sample(alert, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE,NULL);
        }
        
        break;
    case REMOVE_BLOCKS:
    {
        bool removed = level.remove_blocks();
        int c = color_selector.get_selected_color();
        if (!removed && strongest_color == c)
        {
            state = NEXT_LEVEL;
            al_play_sample(win, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE,NULL);
        }
        else if (!removed)
        {
            state = GAME_OVER;      
        }
        break;
    }
    case GAME_OVER:
    {
        break;
    }

    case NEXT_LEVEL:
    {

        state = LEVEL_NAME;
        level.next_level();
        start_countdown(2);

        break;
    }
    
    }
    return false;
}

void MainLoop::key_pressed(int key)
{
    if ( state == COUNTDOWN )
    {
        switch (key)
        {
        case ALLEGRO_KEY_RIGHT:
            if(!done_selecting)
                color_selector.select_color_right();
            break;
        case ALLEGRO_KEY_LEFT:
            if(!done_selecting)
                color_selector.select_color_left();
            break;
        
        case ALLEGRO_KEY_ENTER:
            done_selecting = true;
            break;
        case ALLEGRO_KEY_SPACE:
            done_selecting = true;
            break;
        }
    }
    if ( state == SPLASH_SCREEN )
    {
        switch (key)
        {
        case ALLEGRO_KEY_ENTER:
            state = INSTRUCTIONS;
            start_countdown(2);
            break;
        }
    }
    if ( state == GAME_OVER )
    {
        switch (key)
        {
        case ALLEGRO_KEY_ENTER:
            state = LEVEL_NAME;
            level = Level();
            level.next_level();
            done_selecting = false;
            start_countdown(2);
            break;
        }
    }
}


void MainLoop::start_countdown(int i)
{
    countdown_value = 60 * i;
}

void MainLoop::draw()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    switch(state) {
    case SPLASH_SCREEN:
        al_draw_text
        (
            font_splash_big,
            al_map_rgba(255,255,255,alpha),
            640/2,
            (100),
            ALLEGRO_ALIGN_CENTRE,
            "ONE COLOR!"
        );
        al_draw_text
        (
            font_splash_small,
            al_map_rgba(255,255,255,125),
            640/2,
            (200),
            ALLEGRO_ALIGN_CENTRE,
            "ENTER: START"
        );

        al_draw_text
        (
            font_splash_small,
            al_map_rgba(255,255,255,125),
            640/2,
            (250),
            ALLEGRO_ALIGN_CENTRE,
            "ESCAPE: EXIT"
        );
        break;
    case INSTRUCTIONS:
        al_draw_text
        (
            font_splash_small,
            al_map_rgba(255,255,255,alpha),
            640/2,
            (200),
            ALLEGRO_ALIGN_CENTRE,
            "CHOOSE THE"
        );
        al_draw_text
        (
            font_splash_small,
            al_map_rgba(255,255,255,alpha),
            640/2,
            (240),
            ALLEGRO_ALIGN_CENTRE,
            "STRONGEST COLOR"
        );

        break;

    case LEVEL_NAME:
        
        al_draw_text
        (
            font_splash_big,
            al_map_rgba(255,255,255,255),
            640/2,
            (100),
            ALLEGRO_ALIGN_CENTRE,
            level.get_level_string()
        );
        break;

    case COUNTDOWN:
        level.draw_blocks_center(320, 180);
        
        al_draw_text
        (
            font,
            al_map_rgba(255,255,255,alpha),
            640/2,
            (480/3),
            ALLEGRO_ALIGN_CENTRE,
            countdown_text
        );
        
        color_selector.draw_center(320,390);
        break;
    case REMOVE_BLOCKS:
        level.draw_blocks_center(320,180);
        break;
    case GAME_OVER:
        al_draw_text
        (
            font_splash_big,
            al_map_rgba(255,255,255,255),
            640/2,
            (100),
            ALLEGRO_ALIGN_CENTRE,
            "GAME OVER!"
        );
        
        al_draw_text
        (
            font_splash_small,
            al_map_rgba(255,255,255,255),
            640/2,
            (200),
            ALLEGRO_ALIGN_CENTRE,
            "YOU REACHED"
        );


        al_draw_text
        (
            font_splash_small,
            al_map_rgba(255,255,255,255),
            640/2,
            (240),
            ALLEGRO_ALIGN_CENTRE,
            level.get_level_string()
        );

        al_draw_text
        (
            font_splash_small,
            al_map_rgba(255,255,255,125),
            640/2,
            (280),
            ALLEGRO_ALIGN_CENTRE,
            "ENTER: RETRY"
        );

        al_draw_text
        (
            font_splash_small,
            al_map_rgba(255,255,255,125),
            640/2,
            (320),
            ALLEGRO_ALIGN_CENTRE,
            "ESCAPE: EXIT"
        );
        break;
    case NEXT_LEVEL:
        break;
    }

}
 

MainLoop::~MainLoop()
{
    al_destroy_sample(win);
    al_destroy_sample(alert);
};

