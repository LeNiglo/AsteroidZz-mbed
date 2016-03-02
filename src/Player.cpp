#include "Player.hpp"

Player::Player() : Player(WINDOW_TITLE) { }

Player::Player(const std::string &name)
{
	this->name = name;
	this->x = (WINDOW_X - PLAYER_SIZE_X) / 2;
	this->y = (WINDOW_Y - PLAYER_SIZE_Y) / 2;
	this->life = 1;
	this->ammo = PLAYER_SHOT_AMMO;
	this->shots = std::list<Shot*>();
	this->body = new sf::RectangleShape(sf::Vector2f(PLAYER_SIZE_X - 1, PLAYER_SIZE_Y - 1));
	this->body->setOutlineColor(sf::Color::White);
	this->body->setOutlineThickness(1);
	this->initSerial();
}

Player::~Player()
{
	delete this->body;
	delete this->serial;
	std::cout << "Player " << this->name << " deleted." << std::endl;
}

bool				Player::initSerial()
{
	try {
		this->serial = new SerialReader();
		if (!this->serial->init()) {
			std::cerr << "SerialReader init failed." << std::endl;
			this->life = -1;
			return false;
		}
		return true;
	} catch(std::exception& e) {
		this->serial = NULL;
		std::cerr << "Error: " << e.what() << std::endl;
		this->life = -1;
		return false;
	}
}

void 				Player::hit()
{
	--this->life;
}

void				Player::move(Game *game)
{
	try {
		t_accel data;
		this->getAccelData(&data);

		if (abs(data.y) > ACCEL_THRESHOLD) { this->x += (float) data.y * (data.fire ? 2 : 1) / ACCEL_SCALE; }
		if (abs(data.x) > ACCEL_THRESHOLD) { this->y += (float) data.x * (data.fire ? 2 : 1) / ACCEL_SCALE; }

		this->x = (this->x + PLAYER_SIZE_X > static_cast<int>(game->getVideoMode().width) ? static_cast<int>(game->getVideoMode().width) - PLAYER_SIZE_X : (this->x < 0 ? 0 : this->x));
		this->y = (this->y + PLAYER_SIZE_Y > static_cast<int>(game->getVideoMode().height) ? static_cast<int>(game->getVideoMode().height) - PLAYER_SIZE_Y : (this->y < 0 ? 0 : this->y));

		this->handleShots(game, &data);
		std::list<Shot*>::iterator it = this->shots.begin();
		while (it != this->shots.end()) {
			if (!(*it)->move(game)) {
				Shot *ptr = *it;
				it = this->shots.erase(it);
				delete ptr;
			} else {
				++it;
			}
		}
	} catch(boost::bad_lexical_cast& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void 				Player::handleShots(Game *game, t_accel *data)
{
	if (this->ammo > 0) {
		if (this->pClock.getElapsedTime().asMilliseconds() > PLAYER_SHOT_DELTA) {
			if (data->up || data->right || data->down || data->left) {
				this->shoot(data);
				game->getSoundManager()->playShot();
				this->pClock.restart();
			}
		}
	} else {
		if (this->pClock.getElapsedTime().asMilliseconds() > (PLAYER_SHOT_DELTA * PLAYER_SHOT_AMMO)) {
			this->ammo = PLAYER_SHOT_AMMO;
			game->getSoundManager()->playReload();
		}
	}
}

void 				Player::shoot(t_accel *data)
{
	int incX = data->right ? 5 : data->left ? -5 : 0;
	int incY = data->up ? -5 : data->down ? 5 : 0;
	int posX = this->x + (PLAYER_SIZE_X - PLAYER_SHOT_SIZE) / 2;
	int posY = this->y + (PLAYER_SIZE_Y - PLAYER_SHOT_SIZE) / 2;
	this->shots.push_back(new Shot(posX, posY, incX, incY));
	--this->ammo;
}

void				Player::getAccelData(t_accel *data)
{
	this->serial->poke();
	std::istringstream s(this->serial->getLine());
	std::string sX, sY, sZ, sUp, sRight, sDown, sLeft, sFire;

	getline(s, sX, ';');
	data->x = boost::lexical_cast<int>(sX);

	getline(s, sY, ';');
	data->y = boost::lexical_cast<int>(sY);

	getline(s, sZ, ';');
	data->z = boost::lexical_cast<int>(sZ);

	getline(s, sUp, ';');
	data->up = boost::lexical_cast<bool>(sUp) == 0 ? false : true;

	getline(s, sRight, ';');
	data->right = boost::lexical_cast<bool>(sRight) == 0 ? false : true;

	getline(s, sDown, ';');
	data->down = boost::lexical_cast<bool>(sDown) == 0 ? false : true;

	getline(s, sLeft, ';');
	data->left = boost::lexical_cast<bool>(sLeft) == 0 ? false : true;

	getline(s, sFire, ';');
	data->fire = boost::lexical_cast<bool>(sFire) == 0 ? false : true;
}

void 				Player::draw(sf::RenderWindow *window, const Game *game)
{
	std::list<Shot*>::iterator it = this->shots.begin();
	while (it != this->shots.end()) {
		(*it++)->draw(window);
	}
	if (game->getKiaiTime()) {
		this->body->setFillColor(sf::Color::Red);
	} else {
		this->body->setFillColor(sf::Color::Blue);
	}
	this->body->setPosition(this->x, this->y);
	window->draw(*this->body);
}

/**
*	GETTERS
*/

bool				Player::isAlive()
{
	return this->life > 0;
}

std::string			Player::getName() const
{
	return this->name;
}

int					Player::getX() const
{
	return boost::numeric_cast<int>(this->x);
}

int					Player::getY() const
{
	return boost::numeric_cast<int>(this->y);
}

int					Player::getLife() const
{
	return this->life;
}

int					Player::getAmmo() const
{
	return this->ammo;
}

sf::RectangleShape*	Player::getBody() const
{
	return this->body;
}
