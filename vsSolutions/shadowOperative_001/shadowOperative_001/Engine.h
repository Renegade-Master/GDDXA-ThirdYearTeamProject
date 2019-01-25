/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <list>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Door.h"
#include "Enemy.h"
#include "EnemyGenerator.h"
#include "HUD.h"
#include "Item.h"
#include "LevelManager.h"
#include "ParticleSystem.h"
#include "Player.h"
#include "SoundManager.h"
#include "TextureHolder.h"
#include "TutorialManager.h"
#include "Bullet.h"
#include "gunBattery.h"
#include "ToggleSwitch.h"
#include "Camera.h"

class Engine {
public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();
private:
	// Get the screen resolution and create an SFML window and View
	sf::Vector2f resolution;

	//  Is the Player using a controller?
	bool m_usingController = true;

	// Handle events
	sf::Event m_event;

	// The Tutorial System
	//TutorialManager tm;

	// Game States
	enum class GameState { MAIN_MENU, PLAYING, PAUSED, LEVEL_SELECT, SETTINGS, LOADING };
	GameState m_GameState = GameState::MAIN_MENU;

	// Main Menu Pages
	enum class SettingsPage { LIST, GRAPHICS, AUDIO, GAMEPLAY};
	SettingsPage m_SettingsPage = SettingsPage::LIST;

	//	Varaibles for tracking Window information
	sf::Uint32 m_windowedStatus = sf::Style::Default;
	unsigned int m_frameRate = 60;
	bool m_vSyncActive = false;

	void refreshWindow();

	// The texture holder
	TextureHolder th;

	// create a particle system
	ParticleSystem m_PS;

	// Player (PlayerCharacters)
	Player m_Player;

	//Enemy Generator

	//Enemy list
	std::list<Enemy*> m_EnemyList;

	//Item list
	std::list<Item*> m_ItemList;

	//Door list
	std::list<Door*> m_DoorList;

	//switch list
	std::list<ToggleSwitch*> m_SwitchList;

	//camera List
	std::list<Camera*> m_CameraList;

	//Level Manager
	LevelManager m_LM;

	// Create a SoundManager
	SoundManager m_SM;

	//The door
	bool doorValid;

	// The HUD
	Hud m_Hud;
	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 500;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	// The force pushing the characters down
	const int GRAVITY = 300;

	// A regular RenderWindow
	sf::RenderWindow m_Window;

	// The main Views
	sf::View m_MainView;
	sf::View m_MiniMap;

	// Two views for the background
	sf::View m_BGMainView;
	sf::View m_BGMiniMap;

	//  One view for the HUD
	sf::View m_HudView;

	// Declare a sprite and a Texture for the background
	sf::Sprite m_BackgroundSprite;
	sf::Texture m_BackgroundTexture;

	// Declare a sprite and a Texture for the background in the Menu
	sf::Sprite m_MenuBackgroundSprite;
	sf::Texture m_MenuBackgroundTexture;
	
	// Varaibles for the GIF background
	sf::Image m_animatedBackgroundImage;
	int m_animatedBackgroundFrame = 0;
	int m_animatedBackgroundMaxFrames = 142;

	// Declare a shader for the background
	sf::Shader m_RippleShader;

	// Is character 1 or 2 the current focus?
	bool m_Character1 = true;

	// How much time is left in the current level
	float m_TimeRemaining;
	sf::Time m_GameTimeTotal;

	// Is it time for a new/first level?
	bool m_NewLevelRequired = true;

	// The vertex array for the level design
	sf::VertexArray m_VALevel;

	// The 2d array with the map for the level
	// A pointer to a pointer
	int** m_ArrayLevel = NULL;

	// Texture for the background and the level tiles
	sf::Texture m_TextureTiles;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();

	// Load a new Level
	void loadLevel();

	// Spawn Enemies
	void enemySpawn();

	// Spawn Items
	void ItemSpawn();

	//Spawn Doors
	void doorSpawn();

	//spawn Switches
	void spawnSwitches();

	//spawn camera
	void spawnCamera();
	// Run will call all the private functions
	bool detectCollisions(PlayableCharacter& character);

	// Make a vector of the best places to emit sounds from
	void populateEmitters(std::vector <sf::Vector2f>& vSoundEmitters,
		int** arrayLevel);

	// A vector of Vector2f for the fire emiiter locations
	std::vector <sf::Vector2f> m_FireEmitters;

	// Button Lists
	void initButtons();
	sf::Font m_buttonFont;

	//	Main Menu
	std::list<GUI::Button> m_mainMenuButtons;
	//	Paused
	std::list<GUI::Button> m_pausedButtons;
	//	Settings
	std::list<GUI::Button> m_settingsButtons;
	//		Graphics Settings
	std::list<GUI::Button> m_graphicsSettingsButtons;
	//		Audio Settings
	std::list<GUI::Button> m_audioSettingsButtons;
	//		Gameplay Settings
	std::list<GUI::Button> m_gameplaySettingsButtons;

	//Bullets
	Bullet bullets[5];
	int currentBullet = 0;
	sf::Time m_SinceLastShot;

	// Where is the mouse in relation to world coordinates
	sf::Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	sf::Vector2i mouseScreenPosition;

	void doorUpdate(float dtAsSeconds, ToggleSwitch *Switch);

	double calcDistance(sf::Vector2f posOne, sf::Vector2f posTwo);
};
#endif // !ENGINE_H