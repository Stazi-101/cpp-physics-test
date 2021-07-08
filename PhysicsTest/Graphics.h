#pragma once

#include <SDL.h>



class Drawer
{
private:
	int screen_width;
	int screen_height;

	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	void init(int, int);
	void draw_example();
	void loop_example();
	void close();
};