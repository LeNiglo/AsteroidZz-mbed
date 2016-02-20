#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include "variables.h"
# include "includes.h"
# include <boost/lexical_cast.hpp>

# include "SerialReader.hpp"

class Player
{
public:
	Player();
	Player(const std::string&);
	Player(const Player&);
	~Player();
	std::string		getName() const;
	int				getX() const;
	int				getY() const;
	bool			move();
	void			draw(sf::RenderWindow*);
private:
	SerialReader	*serial;
	std::string		name;
	int				x;
	int				y;
	sf::CircleShape	*shape;
};

#endif /* _PLAYER_HPP_ */
