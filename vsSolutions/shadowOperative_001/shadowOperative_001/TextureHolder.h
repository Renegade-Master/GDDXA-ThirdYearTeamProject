/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H

#include <assert.h>
#include <iostream>
#include <map>

#include <SFML/Graphics.hpp>

#include "Constants.h"

class TextureHolder {
public:
	TextureHolder() noexcept;
	static sf::Texture& GetTexture(std::string const& filename);

private:
	// A map container from the STL,
	// that holds related pairs of String and Texture
	std::map<std::string, sf::Texture> m_Textures;

	// A pointer of the same type as the class itself
	// the one and only instance
	static TextureHolder* m_s_Instance;
};

#endif