#include "Game.hpp"

int main()
{
	Game *g = new Game();
	g->loop();
	delete g;
	return EXIT_SUCCESS;
}
