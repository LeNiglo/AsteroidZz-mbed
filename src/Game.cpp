#include "Game.hpp"

Game::Game()
{
	this->videoMode = Game::findVideoMode();
	this->soundManager = new SoundManager();
	this->aiManager = new AIManager();
	this->player = new Player();
	this->asteroids = std::list<Asteroid*>();
	this->score = 0;
	this->nextKiai = 0;
	this->kiaiTime = false;
	this->paused = false;
	if (!this->soundManager->init()) {
		std::cerr << "Can't load all sounds." << std::endl;
	}
	if (!this->font.loadFromFile("./resources/ChaparralPro-Regular.otf")) {
		std::cerr << "Can't find the font to load." << std::endl;
	}
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(50);
	this->scoreText.setColor(sf::Color::White);
	this->scoreText.setStyle(sf::Text::Bold);
	this->scoreText.setPosition(15, 0);
	this->window = new sf::RenderWindow(this->videoMode, WINDOW_TITLE);
	sf::Vector2f center = this->window->getView().getCenter();
	sf::Listener::setPosition(center.x, center.y, 100.0f);
	sf::Listener::setDirection(0, 0, -1.0f);
	sf::Listener::setGlobalVolume(100.0f);
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->soundManager;
	delete this->aiManager;
	std::list<Asteroid*>::iterator it = this->asteroids.begin();
	while (it != this->asteroids.end()) {
		Asteroid *ptr = *it;
		it = this->asteroids.erase(it);
		delete ptr;
	}
	std::cout << "Game finished, score = " << this->score << "." << std::endl;
}

void					Game::loop()
{
	this->window->setVerticalSyncEnabled(true);
	this->window->setKeyRepeatEnabled(false);
	this->window->setMouseCursorVisible(false);
	this->delta = this->next = 0;
	this->soundManager->getKiai()->play();
	while (this->window->isOpen() && this->player->isAlive()) {
		if (!this->eventHandling()) {
			continue;
		}
		if (!this->paused) {
			this->factory();
			this->move();
		}
		this->draw();

	}
}

bool					Game::eventHandling()
{
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
			return false;
		}
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
				case sf::Keyboard::Escape:
					window->close();
					return false;
				case sf::Keyboard::Space:
					this->player->toggleClock();
					this->paused = !this->paused;
					break;
				default:
					break;
			}
		}
	}
	return true;
}

void 					Game::move()
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

void 					Game::draw()
{
	this->window->clear();
	std::list<Asteroid*>::iterator it;
	for (it = this->asteroids.begin(); it != this->asteroids.end(); it++) {
		(*it)->draw(window);
	}
	this->player->draw(window, this);

	std::stringstream ss;
	ss << "SCORE: " << this->score;
	if (this->player->getAmmo() > 0) {
		ss << "\nAMMO: " << this->player->getAmmo();
	} else {
		ss << "\nRELOADING ...";
	}
	if (this->kiaiTime) {
		ss << "\nKIAI TIME !";
	}
	if (this->paused) {
		ss << "\nPAUSED ...";
	}
	this->scoreText.setString(ss.str());
	this->window->draw(this->scoreText);

	if (this->kiaiTime) {
		// Shiny Overlay
	}
	this->window->display();
}

void 					Game::factory()
{
	if (this->delta >= this->next) {
		this->asteroids.push_back(new Asteroid(this));
		this->next = rand() % (ASTEROID_CYCLES / (this->kiaiTime ? 5 : 1)) + 1;
		this->delta = 0;
	} else {
		++this->delta;
	}

	++this->score;
	if (this->score > KIAI_THRESHOLD && this->score % (KIAI_THRESHOLD + this->nextKiai) < KIAI_DURATION) {
		if (this->kiaiTime == false) {
			this->soundManager->getKiai()->play();
		}
		this->kiaiTime = true;
	} else {
		if (this->kiaiTime == true) {
			this->nextKiai = rand() % KIAI_THRESHOLD;
		}
		this->kiaiTime = false;
	}
}

void					Game::checkShot(Shot *shot)
{
	Asteroid *a = NULL;
	Asteroid *b = NULL;

	std::list<Asteroid*>::iterator it;
	for (it = this->asteroids.begin(); it != this->asteroids.end(); it++) {
		if (shot->intersects(*it)) {
			this->score += ASTEROID_POINTS + (this->kiaiTime ? (*it)->getSize() * 2 : (*it)->getSize());
			shot->destroy();
			if (!Asteroid::createNews(*it, &a, &b)) {
				a = b = NULL;
			}
			this->soundManager->getDestroy()->setPosition((*it)->getX(), (*it)->getY(), 0);
			this->soundManager->getDestroy()->play();
			(*it)->destroy();
			break;
		}
	}

	if (a != NULL && b != NULL) {
		this->asteroids.push_back(a);
		this->asteroids.push_back(b);
	}
}

sf::VideoMode			Game::findVideoMode()
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

Player*					Game::getPlayer() const
{
	return this->player;
}

sf::VideoMode			Game::getVideoMode() const
{
	return this->videoMode;
}

bool					Game::getKiaiTime() const
{
	return this->kiaiTime;
}

unsigned long int		Game::getScore() const
{
	return this->score;
}

SoundManager*			Game::getSoundManager() const
{
	return this->soundManager;
}

AIManager*				Game::getAiManager() const
{
	return this->aiManager;
}
