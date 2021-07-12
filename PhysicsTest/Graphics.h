#pragma once

#include <SDL.h>
#include <vector>


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

	void draw_background();
	void draw_nodes(std::vector<int>, std::vector<int>);
	void draw_rods(std::vector<int>, std::vector<int>, std::vector<int>, std::vector<int>);
	void draw_present();

	void close();
};