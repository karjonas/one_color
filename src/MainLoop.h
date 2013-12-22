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

#ifndef __MAINLOOP_H__
#define __MAINLOOP_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "BlockBoard.h"
#include "ColorSelector.h"
#include "Level.h"

enum LOOPSTATE {SPLASH_SCREEN, INSTRUCTIONS, LEVEL_NAME, COUNTDOWN, REMOVE_BLOCKS, GAME_OVER, NEXT_LEVEL};

class MainLoop
{
public:
    MainLoop();
    bool tick();
    void key_pressed(int key);
    void start_countdown(int i);
    void draw();
    ~MainLoop();

private:
    Level level;
    ColorSelector color_selector;
    enum LOOPSTATE state;
    ALLEGRO_FONT *font;
    ALLEGRO_FONT *font_splash_big;
    ALLEGRO_FONT *font_splash_small;
    
    ALLEGRO_SAMPLE *win;
    ALLEGRO_SAMPLE *alert;
    int selected_color;
    int strongest_color;
    int alpha;
    int countdown_value;
    char countdown_text[4];
    bool done_selecting;
};

#endif
