#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include "variables.h"
# include "includes.h"
# include <boost/lexical_cast.hpp>

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
	void				move();
	void 				hit();
	void				draw(sf::RenderWindow*);
	bool				isAlive();
	std::string			getName() const;
	int					getX() const;
	int					getY() const;
	int					getLife() const;
	sf::RectangleShape	*getBody() const;
private:
	bool				initSerial();
	void				getAccelData(t_accel*);
private:
	SerialReader		*serial;
	std::string			name;
	float				x;
	float				y;
	int					life;
	sf::RectangleShape	*body;
};


#endif /* _PLAYER_HPP_ */
