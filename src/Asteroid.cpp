#include "Asteroid.hpp"

Asteroid::Asteroid(const Game *game)
{
	this->size = ASTEROID_SIZE + static_cast<int>(game->getScore() / ASTEROID_RATIO);
	this->body = new sf::RectangleShape(sf::Vector2f(this->size, this->size));
	this->body->setFillColor(sf::Color(100 + rand() % 156, 100 + rand() % 156, 100 + rand() % 156));

	this->a = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX)) - 0.5f;
	this->b = rand() % (game->getVideoMode().height + 2 * this->size) - this->size;
	if (rand() % 2 == 1) {
		this->direction = true;
		this->x = -this->size;
	} else {
		this->direction = false;
		this->x = static_cast<int>(game->getVideoMode().width);
	}
}

Asteroid::Asteroid(const int &size, const int &x, const bool &direction, const float &a, const short int &b)
{
	this->size = size;
	this->a = a;
	this->b = b;
	this->direction = direction;
	this->x = x;
	this->body = new sf::RectangleShape(sf::Vector2f(this->size, this->size));
	this->body->setFillColor(sf::Color(100 + rand() % 156, 100 + rand() % 156, 100 + rand() % 156));
}

Asteroid::~Asteroid()
{
	delete this->body;
}

bool					Asteroid::createNews(const Asteroid *old, Asteroid **a, Asteroid **b)
{
	if (old->getSize() < ASTEROID_SIZE * ASTEROID_SPLIT) {
		return false;
	}

	*a = new Asteroid((old->getSize() / ASTEROID_SPLIT), (old->getX() + ((old->getSize() - (old->getSize() / ASTEROID_SPLIT)) / 2)), old->getDirection(), old->getA(), (old->getB() + ((old->getSize() - (old->getSize() / ASTEROID_SPLIT)) / 2)));
	*b = new Asteroid((old->getSize() / ASTEROID_SPLIT), (old->getX() + ((old->getSize() - (old->getSize() / ASTEROID_SPLIT)) / 2)), old->getDirection(), -old->getA(), ((old->getB() + ((old->getSize() - (old->getSize() / ASTEROID_SPLIT)) / 2)) + 2 * old->getA() * (old->getX() + ((old->getSize() - (old->getSize() / ASTEROID_SPLIT)) / 2))));
	return true;
}

void					Asteroid::draw(sf::RenderWindow *window)
{
	this->body->setPosition(this->x, this->getY());
	window->draw(*this->body);
}

bool					Asteroid::move(Player *player, const Game *game)
{
	this->x += (this->direction ? 1 : -1) * (game->getKiaiTime() ? 2 : 1) * WINDOW_SPEED;

	if (this->intersects(player)) {
		player->hit(game);
	}

	if (this->x > static_cast<int>(game->getVideoMode().width) || this->x < -this->size) {
		return false;
	} else {
		return true;
	}
}

bool					Asteroid::intersects(const Player *player)
{
	sf::IntRect r1(this->x, this->getY(), this->size, this->size);
	sf::IntRect r2(player->getX(), player->getY(), PLAYER_SIZE_X, PLAYER_SIZE_Y);
	return r1.intersects(r2);
}

void					Asteroid::destroy()
{
	this->x = -1000;
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

int						Asteroid::getSize() const
{
	return this->size;
}

bool					Asteroid::getDirection() const
{
	return this->direction;
}

float					Asteroid::getA() const
{
	return this->a;
}

float					Asteroid::getB() const
{
	return this->b;
}
