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

#include "PlayableCharacter.h"
#include "SoundManager.h"
//#include "Enemy.h"
//#include "Player.h"

/**
*	Parent/Superclass
*/
class Command {
public:
	virtual ~Command() { /*delete this;*/ }
	virtual void execute(PlayableCharacter& pc) = 0;
};

/**
*
*/
class cmd_Null : public Command {
public:
	virtual void execute(PlayableCharacter& pc) {
		pc.m_Direction = PlayableCharacter::Direction::IDLE;
	}
};

/**
*
*/
class cmd_RunLeft : public Command {
public:
	virtual void execute(PlayableCharacter& pc) { 
		pc.m_Direction = PlayableCharacter::Direction::LEFT;

		if (pc.m_Action != PlayableCharacter::Action::FALLING
			&& pc.m_Action != PlayableCharacter::Action::JUMPING) {

			pc.m_Action = PlayableCharacter::Action::RUNNING;

		}
	}
};

/**
*
*/
class cmd_RunRight : public Command {
public:
	virtual void execute(PlayableCharacter& pc) {
		pc.m_Direction = PlayableCharacter::Direction::RIGHT;

		if (pc.m_Action != PlayableCharacter::Action::FALLING
			&& pc.m_Action != PlayableCharacter::Action::JUMPING) {

			pc.m_Action = PlayableCharacter::Action::RUNNING;

		}
	}
};

/**
*
*/
class cmd_Jump : public Command {
public:
	virtual void execute(PlayableCharacter& pc) { 
		//pc.m_Action = PlayableCharacter::Action::JUMPING;
		// Character hasn't jumped too many times
		if (pc.m_jumpCounter < pc.maxJumps) {
			pc.m_jumpDuration = 0.0f;
			pc.m_Action = PlayableCharacter::Action::JUMPING;
			pc.m_jumpCounter++;
		}
	}
};

/**
*
*/
class cmd_Shoot : public Command {
public:
	virtual void execute(PlayableCharacter& pc) {
		pc.m_Action = PlayableCharacter::Action::ATTACKING;
		pc.shooting = true;
	}
};

/**
*
*/
class cmd_ToggleAim : public Command {
public:
	virtual void execute(PlayableCharacter& pc) {
		pc.toggleTargeting();
	}
};

/*
*	Move Aim Location to the left using Right analog stick
*/
class cmd_AimLeft : public Command {
public:
	virtual void execute(PlayableCharacter& pc) {
		if (pc.isTargeting()) {
			pc.targetingLaser.updateLine(pc.m_Position,
				sf::Vector2f(pc.target.x -= 5, pc.target.y));
		}
	}
};                   
/*
*	Move Aim Location to the right using Right analog stick
*/
class cmd_AimRight : public Command {
public:
	virtual void execute(PlayableCharacter& pc) {
		if (pc.isTargeting()) {
			pc.targetingLaser.updateLine(pc.m_Position,
				sf::Vector2f(pc.target.x += 5, pc.target.y));
		}
	}
};
/*
*	Move Aim Location up using Right analog stick
*/
class cmd_AimUp : public Command {
public:
	virtual void execute(PlayableCharacter& pc) {
		if (pc.isTargeting()) {
			pc.targetingLaser.updateLine(pc.m_Position,
				sf::Vector2f(pc.target.x, pc.target.y -= 5));
		}
	}
};
/*
*	Move Aim Location Down using Right analog stick
*/
class cmd_AimDown : public Command {
public:
	virtual void execute(PlayableCharacter& pc) {
		if (pc.isTargeting()) {
			pc.targetingLaser.updateLine(pc.m_Position,
				sf::Vector2f(pc.target.x, pc.target.y += 5));
		}
	}
};

/*
*	Move Aim Location UP Left using Right analog stick
*/
class cmd_LEFT_UP : public Command {
public:
	virtual void execute(PlayableCharacter& pc) {
		if (pc.isTargeting()) {
			pc.targetingLaser.updateLine(pc.m_Position,
				sf::Vector2f(pc.target.x-=5, pc.target.y += 5));
		}
	}
};
/*
*	Move Aim Location Down Left using Right analog stick
*/
class cmd_LEFT_DOWN : public Command {
public:
	virtual void execute(PlayableCharacter& pc) {
		if (pc.isTargeting()) {
			pc.targetingLaser.updateLine(pc.m_Position,
				sf::Vector2f(pc.target.x -= 5, pc.target.y -= 5));
		}
	}
};
/*
*	Move Aim Location Down RIGHT using Right analog stick
*/
class cmd_RIGHT_DOWN : public Command {
public:
	virtual void execute(PlayableCharacter& pc) {
		if (pc.isTargeting()) {
			pc.targetingLaser.updateLine(pc.m_Position,
				sf::Vector2f(pc.target.x += 5, pc.target.y += 5));
		}
	}
};
/*
*	Move Aim Location Down RIGHT using Right analog stick
*/
class cmd_RIGHT_UP : public Command {
public:
	virtual void execute(PlayableCharacter& pc) {
		if (pc.isTargeting()) {
			pc.targetingLaser.updateLine(pc.m_Position,
				sf::Vector2f(pc.target.x += 5, pc.target.y -= 5));
		}
	}
};
#endif // !COMMAND_H