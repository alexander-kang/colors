SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

# gcc -o test test.c `sdl2-config --cflags --libs`
