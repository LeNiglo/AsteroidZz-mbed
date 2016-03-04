#ifndef _ASTEROID_HPP_
# define _ASTEROID_HPP_

# include "variables.h"
# include "includes.h"

# include "Player.hpp"

class Asteroid
{
public:
	Asteroid(const Game*);
	Asteroid(const int&, const int&, const bool&, const float&, const short int&);
	~Asteroid();
	static bool					createNews(const Asteroid*, Asteroid**, Asteroid**);
	void						draw(sf::RenderWindow*);
	bool						move(Player*, const Game*);
	sf::RectangleShape 			*getBody() const;
	int							getX() const;
	int							getY() const;
	int							getSize() const;
	bool						getDirection() const;
	float						getA() const;
	float						getB() const;
	void						destroy();
private:
	bool						intersects(const Player*);
private:
	int							size;
	int							x;
	bool						direction;
	float						a;
	short int					b;
	sf::RectangleShape 			*body;
};

# include "Game.hpp"

#endif /* _ASTEROID_HPP_ */
