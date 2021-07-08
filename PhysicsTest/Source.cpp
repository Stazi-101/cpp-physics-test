
#include "Graphics.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char* args[])
{
	
	Drawer drawer = Drawer();

	drawer.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	drawer.loop_example();
	drawer.close();

	return 0;
}