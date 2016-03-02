#ifndef _SOUNDMANAGER_HPP_
# define _SOUNDMANAGER_HPP_

# include "variables.h"
# include "includes.h"

class SoundManager
{
public:
	bool			init()
	{
		bool success = true;
		success &= this->kiaiBuffer.loadFromFile("./resources/kiai.wav");
		success &= this->reloadBuffer.loadFromFile("./resources/reload.wav");
		success &= this->destroyBuffer.loadFromFile("./resources/destroy.wav");
		success &= this->shotBuffer.loadFromFile("./resources/shot.wav");

		if (success) {
			this->kiai.setBuffer(this->kiaiBuffer);
			this->kiai.setVolume(40);
			this->reload.setBuffer(this->reloadBuffer);
			this->reload.setVolume(80);
			this->destroy.setBuffer(this->destroyBuffer);
			this->destroy.setVolume(60);
			this->shot.setBuffer(this->shotBuffer);
			this->shot.setVolume(40);
		}
		return success;
	}
	void			playKiai()
	{
		this->kiai.play();
	}
	void			playReload()
	{
		this->reload.play();
	}
	void			playDestroy()
	{
		this->destroy.play();
	}
	void			playShot()
	{
		this->shot.play();
	}
private:
	sf::SoundBuffer	kiaiBuffer;
	sf::Sound		kiai;
	sf::SoundBuffer	reloadBuffer;
	sf::Sound		reload;
	sf::SoundBuffer destroyBuffer;
	sf::Sound		destroy;
	sf::SoundBuffer shotBuffer;
	sf::Sound		shot;
};

#endif /* _SOUNDMANAGER_HPP_ */
