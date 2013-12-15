CXX=g++
CFLAGS=
LDFLAGS=-L/usr/lib -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec
INCLUDE=-I. -I/usr/include/allegro5

OBJS=main.cpp Level.cpp ColorList.cpp ColorSelector.cpp BlockBoard.cpp MainLoop.cpp
OUT=one_color

all: one_color

clean:
	rm -rf *.o one_color

one_color: $(OBJS)
	$(CXX) $(OBJS) -o $(OUT) $(INCLUDE) $(CFLAGS) $(LDFLAGS)
