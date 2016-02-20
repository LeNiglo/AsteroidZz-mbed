#ifndef _GAME_HPP_
# define _GAME_HPP_

# include "variables.h"
# include "includes.h"
# include "Player.hpp"

class Game
{
public:
	Game();
	Game(const Game&);
	~Game();

	void					loop();
	Player					*getPlayer() const;
	sf::VideoMode			getVideoMode() const;
private:
	static sf::VideoMode	findVideoMode();
private:
	Player					*player;
	sf::RenderWindow		*window;
	sf::VideoMode			videoMode;
};

#endif /* _GAME_HPP_ */
