/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Door.h"
#include "TextureHolder.h"

	void Door::DoorState()
	{
		door = false;

		if (door == true)
		{
			m_Sprite = sf::Sprite(TextureHolder::GetTexture(
				"graphics/opendoor.png"));
		}
		else if (door == false)
		{
			m_Sprite = sf::Sprite(TextureHolder::GetTexture(
				"graphics/closedoor.png"));
		}
	}

