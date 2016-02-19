#include "Game.hpp"

Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), WINDOW_TITLE);
	this->player = new Player();
}

Game::Game(const Game &g)
{
	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), WINDOW_TITLE);
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
	sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (this->window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->draw(shape);
        window->display();
    }
}

Player*			Game::getPlayer() const
{
	return this->player;
}
