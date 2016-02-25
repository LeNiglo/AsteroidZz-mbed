#ifndef _ASTEROID_HPP_
# define _ASTEROID_HPP_

# include "variables.h"
# include "includes.h"

# include "Player.hpp"

class Asteroid
{
public:
	Asteroid();
	~Asteroid();
	void					draw(sf::RenderWindow*);
	bool					move(Player&);
	bool					intersects(const Player&);
	sf::RectangleShape 		*getBody() const;
	int						getX() const;
	int						getY() const;
private:
	bool					intersect(const Player&);
private:
	int						x;
	bool					direction;
	float					a;
	unsigned short int		b;
	sf::RectangleShape 		*body;
};

#endif /* _ASTEROID_HPP_ */
