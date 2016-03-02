#include "Shot.hpp"

Shot::Shot(const int &oX, const int &oY, const int &dX, const int &dY)
{
	this->x = oX;
	this->y = oY;
	this->incX = dX;
	this->incY = dY;
	this->body = new sf::RectangleShape(sf::Vector2f(PLAYER_SHOT_SIZE, PLAYER_SHOT_SIZE));
	this->body->setFillColor(sf::Color::White);
}

Shot::~Shot()
{

}

void			Shot::destroy()
{
	this->x = -1000;
}

bool 		Shot::move(Game *game)
{
	this->x += incX * WINDOW_SPEED;
	this->y += incY * WINDOW_SPEED;

	game->checkShot(this);

	if (this->x > static_cast<int>(game->getVideoMode().width) || this->x < 0) {
		return false;
	} else if (this->y > static_cast<int>(game->getVideoMode().height) || this->y < 0) {
		return false;
	} else {
		return true;
	}
}

bool		Shot::intersects(const Asteroid *asteroid)
{
	sf::IntRect r1(asteroid->getX(), asteroid->getY(), asteroid->getSize(), asteroid->getSize());
	sf::IntRect r2(this->x, this->y, PLAYER_SHOT_SIZE, PLAYER_SHOT_SIZE);
	return r1.intersects(r2);
}

void 		Shot::draw(sf::RenderWindow *window)
{
	this->body->setPosition(this->x, this->y);
	window->draw(*this->body);
}
