#include "Game.hpp"

int main()
{
	srand(time(NULL));
	Game *g = new Game();
	g->loop();
	delete g;
	return EXIT_SUCCESS;
}
