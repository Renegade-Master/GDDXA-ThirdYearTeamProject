/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Door.h"


	void Door::DoorState()
	{
		door = false;

		if (door == true)
		{
			m_ItemSprite = sf::Sprite(TextureHolder::GetTexture(
				"graphics/DoorOpen.png"));
		}
		else if (door == false)
		{
			m_ItemSprite = sf::Sprite(TextureHolder::GetTexture(
				"graphics/DoorUnlocked.png"));
		}
	}

