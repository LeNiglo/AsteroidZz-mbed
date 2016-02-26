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
	bool					getKiaiTime() const;
	unsigned long int		getScore() const;
	void					checkShot(Shot*);
private:
	static sf::VideoMode	findVideoMode();
private:
	Player					*player;
	sf::RenderWindow		*window;
	sf::VideoMode			videoMode;
	sf::Font				font;
	sf::Text				scoreText;
	std::list<Asteroid*>	asteroids;
	unsigned long int		score;
	bool					kiaiTime;
	unsigned int			nextKiai;
	unsigned int			delta;
	unsigned short int		next;
};

#endif /* _GAME_HPP_ */
