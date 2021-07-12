
#include "Graphics.h"
#include "Physics.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int, char*);
void loop(Drawer, World);
void draw(Drawer, World);



int main(int argc, char* args[])
{
	
	Drawer drawer = Drawer();
	World world = World();
	world.makeTestObject();

	drawer.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	loop(drawer, world);
	drawer.close();

	return 0;
}


void loop(Drawer drawer, World world) {
	SDL_bool done = SDL_FALSE;
	bool simulating = false;

	int mouse_x;
	int mouse_y;
	node* closest_node;
	 
	while (!done) {
		SDL_Event event;

		if (simulating) { world.applyPhysicsLoop(1000 / 30); }

		draw(drawer, world);

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				done = SDL_TRUE;
			}
			else if (event.type == SDL_KEYDOWN) {
				simulating = !simulating;
			}

			SDL_Delay(1);
		}

		if (SDL_GetMouseState(&mouse_x, &mouse_y)) {
			closest_node = world.getNearestNode(Eigen::Vector2d(mouse_x, mouse_y));
			closest_node->pos = Eigen::Vector2d(mouse_x, mouse_y);
		}
	}
}

void draw(Drawer drawer, World world) {

	drawer.draw_background();

	std::vector<int> xs;
	std::vector<int> ys;
	world.getNodesPos(&xs, &ys);
	drawer.draw_nodes(xs,ys);

	std::vector<int> x1s;
	std::vector<int> y1s;
	std::vector<int> x2s;
	std::vector<int> y2s;
	world.getRodsPos(&x1s, &y1s, &x2s, &y2s);
	drawer.draw_rods(x1s,y1s,x2s,y2s);

	drawer.draw_present();
}

