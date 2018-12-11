/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include <assert.h>
#include "Tutorial.h"

Tutorial* Tutorial::m_s_Instance = nullptr;

Tutorial::Tutorial() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

std::string& Tutorial::GetTutorial(sf::Vector2i const& position) {
	std::string temp = "NULL";
	return *(&temp);
}