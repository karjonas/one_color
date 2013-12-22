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
#include "ColorList.h"

ALLEGRO_COLOR ColorList::get_color(int i)
{
	int alpha = 255;
	assert(i >= 0 && i <= 6);
	switch(i)
	{
	case 0: return al_map_rgba(255,0,0,alpha);
	case 1: return al_map_rgba(0,255,0,alpha);
	case 2: return al_map_rgba(0,0,255,alpha);
	case 3: return al_map_rgba(255,255,0,alpha);
	case 4: return al_map_rgba(255,0,255,alpha);
	case 5: return al_map_rgba(0,255,255,alpha);
	case 6: return al_map_rgba(255,255,255,alpha);
	}	
	return al_map_rgba(0,0,0,255);
};

ALLEGRO_COLOR ColorList::white()
{
	return al_map_rgba(255,255,255,255);
}
