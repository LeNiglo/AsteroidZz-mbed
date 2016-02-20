#include "Player.hpp"

Player::Player()
{
	this->name = WINDOW_TITLE;
	this->x = 0;
	this->y = 0;
	this->shape = new sf::CircleShape(100.f);
	this->shape->setFillColor(sf::Color::Green);

	try {
		this->serial = new SerialReader(SERIAL_PORT);
		if (!this->serial->init()) {
			throw "SerialReader init failed.";
		}
	} catch(boost::system::system_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

Player::Player(const std::string &name)
{
	this->name = name;
	this->x = 0;
	this->y = 0;
	this->shape = new sf::CircleShape(100.f);
	this->shape->setFillColor(sf::Color::Green);

	try {
		this->serial = new SerialReader(SERIAL_PORT);
		if (!this->serial->init()) {
			throw "SerialReader init failed.";
		}
	} catch(boost::system::system_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

Player::Player(const Player &p)
{
	this->name = p.getName();
	this->x = p.getX();
	this->y = p.getY();
	this->shape = new sf::CircleShape(100.f);
	this->shape->setFillColor(sf::Color::Green);

	try {
		this->serial = new SerialReader(SERIAL_PORT);
		if (!this->serial->init()) {
			throw "SerialReader init failed.";
		}
	} catch(boost::system::system_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
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
	try {
		this->serial->poke();
		std::string accel = this->serial->getLine();
		std::cout << accel << std::endl;

		std::istringstream s(accel);
		std::string sX, sY, sZ;
		int vX, vY, vZ;
		getline(s, sX,';');
		getline(s, sY,';');
		getline(s, sZ,';');
		vX = boost::lexical_cast<int>(sX);
		vY = boost::lexical_cast<int>(sY);
		vZ = boost::lexical_cast<int>(sZ);
		std::cout << vX << std::endl << vY << std::endl << vZ << std::endl;
		this->x += vX / 1000;
		this->y += vY / 1000;
	} catch(boost::bad_lexical_cast& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return true;
}

void 			Player::draw(sf::RenderWindow *window)
{
	this->shape->setPosition(this->x, this->y);
	window->draw(*	this->shape);
}
