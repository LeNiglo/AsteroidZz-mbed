#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include "variables.h"
# include "includes.h"

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
private:
	SerialReader	*serial;
	std::string		name;
	int				x;
	int				y;

};

#endif /* _PLAYER_HPP_ */
