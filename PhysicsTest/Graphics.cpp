#include "Graphics.h"
#include <SDL.h>

#include <iostream>

void Drawer::init(int width, int height) 
{
	screen_width = width;
	screen_height = height;
	//init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	//create window
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	//create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL_ErrorL %s\n", SDL_GetError());
	}
}




void Drawer::draw_example() 
{
	//clear screebn
	SDL_SetRenderDrawColor(renderer, 0x0F, 0x1F, 0x1F, 0xFF);
	SDL_RenderClear(renderer);

	SDL_RenderDrawLine(renderer, 320, 200, 300, 240);

	for (int i=1; i < 10; i++) {
		SDL_SetRenderDrawColor(renderer, 0xFF, i*10, 0x00, 0xFF);
		SDL_RenderDrawLine(renderer, i * 10, i * 10, 100, i * 10);

	}

	SDL_RenderPresent(renderer);
}


void Drawer::loop_example()
{
	SDL_bool done = SDL_FALSE;
	bool simulating = true;
	while (!done) {
		SDL_Event event;

		if (simulating) { };

		draw_example();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				done = SDL_TRUE;
			}
			else if (event.type == SDL_KEYDOWN) {
				simulating = !simulating;
			}

			SDL_Delay(1000 / 30);
		}
	}
}


void Drawer::close() 
{
	//Destroy window    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}