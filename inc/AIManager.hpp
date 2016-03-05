#ifndef _AIMANAGER_HPP_
# define _AIMANAGER_HPP_

# include "variables.h"
# include "includes.h"
# include "selene.h"

# define LUA_FILE "./resources/ai.lua"

class 				AIManager
{
public:
	AIManager();
private:
	sel::State		state;
};

#endif /* _AIMANAGER_HPP_ */
