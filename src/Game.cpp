#include "Game.hpp"

Game::Game()
{
	this->videoMode = Game::findVideoMode();
	this->window = new sf::RenderWindow(this->videoMode, WINDOW_TITLE);
	this->player = new Player();
}

Game::Game(const Game &g)
{
	this->videoMode = g.getVideoMode();
	this->window = new sf::RenderWindow(this->videoMode, WINDOW_TITLE);
	this->player = g.getPlayer();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	std::cout << "Game finished." << std::endl;
}

void			Game::loop()
{
	while (this->window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			window->close();
		}
		this->player->move();
		window->clear();
		this->player->draw(window);
		window->display();
	}
}

sf::VideoMode	Game::findVideoMode()
{
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	std::size_t i = modes.size();
	do {
		--i;
		if (modes[i].width >= WINDOW_X) {
			std::cout << modes[i].width << "x" << modes[i].height << std::endl;
			return sf::VideoMode(modes[i].width, modes[i].height);
		}
	} while(i != 0);
	return sf::VideoMode(WINDOW_X, WINDOW_Y);
}

Player*			Game::getPlayer() const
{
	return this->player;
}

sf::VideoMode	Game::getVideoMode() const
{
	return this->videoMode;
}
