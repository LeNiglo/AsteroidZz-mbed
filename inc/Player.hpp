#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include <boost/lexical_cast.hpp>
# include "variables.h"
# include "includes.h"

# include "SerialReader.hpp"

typedef	struct 			s_accel {
	int					x;
	int					y;
	int					z;
	bool				up;
	bool				right;
	bool				down;
	bool				left;
	bool				fire;
}						t_accel;

class Player
{
public:
	Player();
	Player(const std::string&);
	~Player();
	void					move(Game*);
	void 					hit();
	void 					handleShots(Game*, t_accel*);
	void					shoot(t_accel*);
	void					draw(sf::RenderWindow*, const Game*);
	sf::Time				toggleClock();
	bool					isAlive();
	std::string				getName() const;
	int						getX() const;
	int						getY() const;
	int						getLife() const;
	int						getAmmo() const;
	sf::RectangleShape		*getBody() const;
private:
	bool					initSerial();
	void					getAccelData(t_accel*);
private:
	SerialReader			*serial;
	std::list<Shot*>		shots;
	std::string				name;
	float					x;
	float					y;
	int						life;
	unsigned int			ammo;
	sf::RectangleShape		*body;
	sftools::Chronometer	pClock;
};

# include "Game.hpp"
# include "Shot.hpp"

#endif /* _PLAYER_HPP_ */
