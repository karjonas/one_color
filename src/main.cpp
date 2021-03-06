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
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "BlockBoard.h"
#include "MainLoop.h"

bool done;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* display;

void abort_game(const char* message)
{
    printf("%s \n", message);
    exit(1);
}
 
void init(void)
{
    if (!al_init())
        abort_game("Failed to initialize allegro");
 
    if (!al_install_keyboard())
        abort_game("Failed to install keyboard");
    if (!al_init_primitives_addon())
        abort_game("Failed to install primitives");
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon 


    if(!al_install_audio()){
        abort_game("failed to initialize audio!\n");
    }
 
    if(!al_init_acodec_addon()){
       abort_game("failed to initialize audio codecs!\n");
    }
 
    if (!al_reserve_samples(1)){
        abort_game("failed to reserve samples!\n");
    }
 
    timer = al_create_timer(1.0 / 60);
    if (!timer)
        abort_game("Failed to create timer");
 
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(640, 480);
    if (!display)
        abort_game("Failed to create display");
 
    event_queue = al_create_event_queue();
    if (!event_queue)
        abort_game("Failed to create event queue");
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
    done = false;
}
 
void shutdown(void)
{
    if (timer)
        al_destroy_timer(timer);
    
    if (display)
        al_destroy_display(display);
 
    if (event_queue)
        al_destroy_event_queue(event_queue);

    al_shutdown_primitives_addon();
}
 
void game_loop(void)
{
    bool redraw = true;
    al_start_timer(timer);
    MainLoop main_loop = MainLoop();
    while (!done)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
 
        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            done = main_loop.tick();
            redraw = true;            
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                done = true;
            }
            else {
                main_loop.key_pressed(event.keyboard.keycode);
            }
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
          done = true;
        }
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            main_loop.draw();
            al_flip_display();
        }
    }
}
 
int main(int argc, char* argv[])
{
    init();
    game_loop();
    shutdown();
}
