#include "Player.hpp"

Player::Player()
{
	this->name = WINDOW_TITLE;
	this->x = 0;
	this->y = 0;
	this->serial = new SerialReader(SERIAL_PORT);
	if (!this->serial->init()) {
		throw "SerialReader init failed.";
	}
}

Player::Player(const std::string &name)
{
	this->name = name;
	this->x = 0;
	this->y = 0;
	this->serial = new SerialReader(SERIAL_PORT);
	if (!this->serial->init()) {
		throw "SerialReader init failed.";
	}
}

Player::Player(const Player &p)
{
	this->name = p.getName();
	this->x = p.getX();
	this->y = p.getY();
	this->serial = new SerialReader(SERIAL_PORT);
	if (!this->serial->init()) {
		throw "SerialReader init failed.";
	}
}

Player::~Player()
{
	std::cout << "Player " << this->name << " deleted." << std::endl;
}

std::string		Player::getName() const
{
	return this->name;
}

int				Player::getX() const
{
	return this->x;
}

int				Player::getY() const
{
	return this->y;
}

bool			Player::move()
{
	return true;
}
