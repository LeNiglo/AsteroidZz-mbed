#include "Asteroid.hpp"

Asteroid::Asteroid()
{
	this->body = new sf::RectangleShape(sf::Vector2f(ASTEROID_SIZE_X, ASTEROID_SIZE_Y));
	this->body->setFillColor(sf::Color::Blue);

	this->a = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX)) - 0.5f;
	this->b = rand() % WINDOW_Y;
	if (rand() % 2 == 1) {
		this->direction = true;
		this->x = 0;
	} else {
		this->direction = false;
		this->x = WINDOW_X;
	}
}

Asteroid::~Asteroid()
{
	delete this->body;
}

void					Asteroid::draw(sf::RenderWindow *window)
{
	this->body->setPosition(this->x, this->getY());
	window->draw(*this->body);
}

bool					Asteroid::move(Player &player)
{
	this->x += this->direction ? 1 : -1;

	if (this->intersects(player)) {
		std::cout << "TOUCHED !" << std::endl;
		player.hit();
	}

	if (this->x > WINDOW_X || this->x < 0) {
		return false;
	} else {
		return true;
	}
}

bool					Asteroid::intersects(const Player &player)
{
	sf::IntRect r1(this->x, this->getY(), ASTEROID_SIZE_X, ASTEROID_SIZE_Y);
	sf::IntRect r2(player.getX(), player.getY(), PLAYER_SIZE_X, PLAYER_SIZE_Y);
	return r1.intersects(r2);
}

/**
 *	GETTERS
 */

sf::RectangleShape*		Asteroid::getBody() const
{
	return this->body;
}

int						Asteroid::getX() const
{
	return this->x;
}

int						Asteroid::getY() const
{
	return static_cast<int>(this->a * this->x + this->b);
}
