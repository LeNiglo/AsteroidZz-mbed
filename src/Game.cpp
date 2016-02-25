#include "Game.hpp"

Game::Game()
{
	this->videoMode = Game::findVideoMode();
	this->window = new sf::RenderWindow(this->videoMode, WINDOW_TITLE);
	this->player = new Player();
	this->asteroids = std::list<Asteroid*>();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	std::cout << "Game finished." << std::endl;
}

void			Game::loop()
{
	this->window->setVerticalSyncEnabled(true);
	this->delta = this->next = 0;
	while (this->window->isOpen() && this->player->isAlive()) {
		if (!this->eventHandling()) {
			break;
		}
		this->move();
		this->draw();
		this->factory();
	}
}

bool			Game::eventHandling()
{
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
			return false;
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				window->close();
				return false;
			}
		}
	}
	return true;
}

void 			Game::move()
{
	this->player->move();
	std::list<Asteroid*>::iterator it;
	for (it = this->asteroids.begin(); it != this->asteroids.end(); it++) {
		if (!(*it)->move(*this->player)) {
			Asteroid *ptr = *it;
			this->asteroids.erase(it);
			delete ptr;
		}
	}

}

void 			Game::draw()
{
	this->window->clear();
	std::list<Asteroid*>::iterator it;
	for (it = this->asteroids.begin(); it != this->asteroids.end(); it++) {
		(*it)->draw(window);
	}
	this->player->draw(window);
	this->window->display();
}

void 			Game::factory()
{
	if (this->delta >= this->next) {
		this->asteroids.push_back(new Asteroid());
		this->next = rand() % ASTEROID_CYCLES + 1;
		this->delta = 0;
	} else {
		++this->delta;
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

/**
*	GETTERS
*/

Player*			Game::getPlayer() const
{
	return this->player;
}

sf::VideoMode	Game::getVideoMode() const
{
	return this->videoMode;
}
