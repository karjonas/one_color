CXX := gcc
CC_FLAGS := -lstdc++
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := -L/usr/lib -lallegro -lallegro_primitives -lallegro_font \
 -lallegro_ttf -lallegro_audio -lallegro_acodec
INCLUDE := -I./src -I/usr/include/allegro5
OUT := one_color

all: one_color

clean:
	rm -rf obj one_color

one_color: $(OBJ_FILES)
	$(CXX) $(CC_FLAGS) $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CC_FLAGS) -c -o $@ $<
