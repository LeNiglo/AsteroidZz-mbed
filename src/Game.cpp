#include "Game.hpp"

Game::Game()
{
	this->videoMode = Game::findVideoMode();
	this->window = new sf::RenderWindow(this->videoMode, WINDOW_TITLE);
	this->player = new Player();
	this->asteroids = std::list<Asteroid*>();
	this->score = 0;
	this->nextKiai = 0;
	this->kiaiTime = false;
	if (!this->font.loadFromFile("./resources/ChaparralPro-Regular.otf")) {
		std::cerr << "Can't find the font" << std::endl;
	}
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(50);
	this->scoreText.setColor(sf::Color::White);
	this->scoreText.setStyle(sf::Text::Bold);
	this->scoreText.setPosition(15, 0);
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	std::cout << "Game finished." << std::endl;
}

void				Game::loop()
{
	this->window->setVerticalSyncEnabled(true);
	this->delta = this->next = 0;
	while (this->window->isOpen() && this->player->isAlive()) {
		if (!this->eventHandling()) {
			continue;
		}
		this->move();
		this->draw();
		this->factory();
	}
}

bool				Game::eventHandling()
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

void 				Game::move()
{
	this->player->move(this);
	std::list<Asteroid*>::iterator it = this->asteroids.begin();
	while (it != this->asteroids.end()) {
		if (!(*it)->move(this->player, this)) {
			Asteroid *ptr = *it;
			it = this->asteroids.erase(it);
			delete ptr;
		} else {
			++it;
		}
	}

}

void 				Game::draw()
{
	this->window->clear();
	std::list<Asteroid*>::iterator it;
	for (it = this->asteroids.begin(); it != this->asteroids.end(); it++) {
		(*it)->draw(window);
	}
	this->player->draw(window);

	std::stringstream ss;
	ss << "SCORE: " << this->score;
	this->scoreText.setString(ss.str());

	this->window->draw(this->scoreText);

	if (this->kiaiTime) {
		// Shiny Overlay
	}
	this->window->display();
}

void 				Game::factory()
{
	if (this->delta >= this->next) {
		this->asteroids.push_back(new Asteroid(this));
		this->next = rand() % (ASTEROID_CYCLES / (this->kiaiTime ? 10 : 1)) + 1;
		this->delta = 0;
	} else {
		++this->delta;
	}

	++this->score;
	if (this->score > KIAI_THRESHOLD && this->score % (KIAI_THRESHOLD + this->nextKiai) < KIAI_DURATION) {
		this->kiaiTime = true;
	} else {
		if (this->kiaiTime == true) {
			this->nextKiai = rand() % KIAI_THRESHOLD;
		}
		this->kiaiTime = false;
	}
}

sf::VideoMode		Game::findVideoMode()
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

Player*				Game::getPlayer() const
{
	return this->player;
}

sf::VideoMode		Game::getVideoMode() const
{
	return this->videoMode;
}

bool				Game::getKiaiTime() const
{
	return this->kiaiTime;
}

unsigned long int	Game::getScore() const
{
	return this->score;
}
