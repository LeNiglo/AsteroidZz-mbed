#ifndef _SOUNDMANAGER_HPP_
# define _SOUNDMANAGER_HPP_

# include "variables.h"
# include "includes.h"

class SoundManager
{
public:
	SoundManager() {
		this->kiai = new sf::Sound();
		this->kiai->setRelativeToListener(true);
		this->kiai->setPosition(0, 0, 0);
		this->reload = new sf::Sound();
		this->reload->setRelativeToListener(true);
		this->reload->setPosition(0, 0, 0);
		this->destroy = new sf::Sound();
		this->destroy->setMinDistance(100.0f);
		this->destroy->setAttenuation(0.25f);
		this->shot = new sf::Sound();
		this->shot->setMinDistance(200.0f);
		this->shot->setAttenuation(0.1f);
	}
	~SoundManager() {
		delete this->kiai;
		delete this->reload;
		delete this->destroy;
		delete this->shot;
	}
	bool			init()
	{
		bool success = true;
		success &= this->kiaiBuffer.loadFromFile("./resources/kiai.wav");
		success &= this->reloadBuffer.loadFromFile("./resources/reload.wav");
		success &= this->destroyBuffer.loadFromFile("./resources/destroy.wav");
		success &= this->shotBuffer.loadFromFile("./resources/shot.wav");

		if (success) {
			this->kiai->setBuffer(this->kiaiBuffer);
			this->kiai->setVolume(40);
			this->reload->setBuffer(this->reloadBuffer);
			this->reload->setVolume(80);
			this->destroy->setBuffer(this->destroyBuffer);
			this->destroy->setVolume(60);
			this->shot->setBuffer(this->shotBuffer);
			this->shot->setVolume(40);
		}
		return success;
	}
	sf::Sound*		getKiai()
	{
		return this->kiai;
	}
	sf::Sound*		getReload()
	{
		return this->reload;
	}
	sf::Sound*		getDestroy()
	{
		return this->destroy;
	}
	sf::Sound*		getShot()
	{
		return this->shot;
	}
private:
	sf::SoundBuffer	kiaiBuffer;
	sf::Sound		*kiai;
	sf::SoundBuffer	reloadBuffer;
	sf::Sound		*reload;
	sf::SoundBuffer destroyBuffer;
	sf::Sound		*destroy;
	sf::SoundBuffer shotBuffer;
	sf::Sound		*shot;
};

#endif /* _SOUNDMANAGER_HPP_ */
