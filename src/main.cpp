#include "Game.hpp"
#include "config.h"

int main()
{
	srand(time(NULL));
	std::cout << "Version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
	Game *g = new Game();
	g->loop();
	delete g;
	return EXIT_SUCCESS;
}
