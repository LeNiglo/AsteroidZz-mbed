#include "Game.hpp"

int main()
{
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	for (std::size_t i = 0; i < modes.size(); ++i)
	{
	    sf::VideoMode mode = modes[i];
	    std::cout << "Mode #" << i << ": "
	              << mode.width << "x" << mode.height << " - "
	              << mode.bitsPerPixel << " bpp" << std::endl;
	}

    Game *g = new Game();
	g->loop();
	delete g;
    return EXIT_SUCCESS;
}
