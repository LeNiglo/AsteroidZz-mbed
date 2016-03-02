#ifndef _SHOT_HPP_
# define _SHOT_HPP_

# include "variables.h"
# include "includes.h"

# include "Asteroid.hpp"

class Shot {
public:
	Shot(const int&, const int&, const int&, const int&);
	~Shot();
	void				destroy();
	bool 				move(Game*);
	bool				intersects(const Asteroid*);
	void 				draw(sf::RenderWindow*);
private:
	int					x;
	int					y;
	int					incX;
	int					incY;
	sf::RectangleShape	*body;
};

#endif /* _SHOT_HPP_ */
