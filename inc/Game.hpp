#ifndef _GAME_HPP_
# define _GAME_HPP_

# include "variables.h"
# include "includes.h"
# include "Player.hpp"
# include "Asteroid.hpp"

class Game
{
public:
	Game();
	~Game();

	void					loop();
	void					draw();
	void					move();
	void					factory();
	bool					eventHandling();
	Player					*getPlayer() const;
	sf::VideoMode			getVideoMode() const;
private:
	static sf::VideoMode	findVideoMode();
private:
	Player					*player;
	sf::RenderWindow		*window;
	sf::VideoMode			videoMode;
	std::list<Asteroid*>	asteroids;
	unsigned int			delta;
	unsigned short int		next;
};

#endif /* _GAME_HPP_ */
