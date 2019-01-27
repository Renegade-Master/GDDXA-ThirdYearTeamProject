/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/27	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef COMMAND_H
#define COMMAND_H

//#include "PlayableCharacter.h"
#include "Player.h"
#include "Enemy.h"

/**
*	Parent/Superclass
*/
class Command {
public:
	virtual ~Command() {}
	virtual void execute(PlayableCharacter& pc) = 0;
};

/**
*
*/
class cmd_RunLeft : public Command {
public:
	virtual void execute(PlayableCharacter& pc) { pc.m_Direction = PlayableCharacter::Direction::LEFT; }
};

/**
*
*/
class cmd_RunRight : public Command {
public:
	virtual void execute(PlayableCharacter& pc) { pc.m_Direction = PlayableCharacter::Direction::RIGHT; }
};

/**
*
*/
class cmd_Jump : public Command {
public:
	virtual void execute(PlayableCharacter& pc) { pc.m_Action = PlayableCharacter::Action::JUMPING; }
};

/**
*
*/
class cmd_Shoot : public Command {
public:
	virtual void execute(PlayableCharacter& pc) { pc.m_Action = PlayableCharacter::Action::ATTACKING; }
};

/**
*
*/
class cmd_ToggleAim : public Command {
public:
	virtual void execute(PlayableCharacter& pc) { /*	NOT SURE WHAT TO DO HERE	*/; }
};

#endif // !COMMAND_H