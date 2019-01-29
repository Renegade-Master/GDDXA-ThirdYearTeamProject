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

#include <sstream>

#include "Bullet.h"
#include "Button.h"
#include "Constants.h"
#include "Door.h"
#include "EnemyGenerator.h"
#include "gunBattery.h"
#include "HUD.h"
#include "InputHandler.h"
#include "LaserPointer.h"
#include "LevelManager.h"
#include "Player.h"
#include "ToggleSwitch.h"

class Engine {
public:
	// Default constructor
	Engine();

	// Run the game loop
	void run();
private:
	// Get the screen resolution and create an SFML window and View
	sf::Vector2f resolution;

	// Handle events
	sf::Event m_event;

	// Game States
	enum class GameState { MAIN_MENU, LEVEL_SELECT, LOADING, READYUP, PLAYING, PAUSED, SETTINGS, ENDGAME};
	//Game State variable
	GameState m_GameState = GameState::MAIN_MENU;

	// Main Menu Pages
	enum class SettingsPage { LIST, GRAPHICS, AUDIO, GAMEPLAY};
	//Current settings page
	SettingsPage m_SettingsPage = SettingsPage::LIST;

	//	Varaibles for tracking Window information
	sf::Uint32 m_windowedStatus = sf::Style::Default;
	//Framerate variable
	unsigned int m_frameRate = 60;
	//V-Sync Active/Inactive?
	bool m_vSyncActive = false;
	//Refresehes Window when window variables have changed
	void refreshWindow();

	// The texture holder
	TextureHolder th;

	// Player (PlayerCharacters)
	Player m_Player;

	//Enemy list
	std::list<Enemy*> m_EnemyList;

	//Item list
	std::list<Item*> m_ItemList;

	//Door list
	std::list<Door*> m_DoorList;

	//switch list
	std::list<ToggleSwitch*> m_SwitchList;

	//	Input Handler
	InputHandler m_IH;

	//camera List
	std::list<Camera*> m_CameraList;

	//Laserpointer list
	std::list<LaserPointer*> m_LaserPointerList;

	//Level Manager
	LevelManager m_LM;

	// Create a SoundManager
	SoundManager m_SM;

	//	The door
	bool doorValid;

	// The HUD
	Hud m_Hud;
	
	//How Long Since last HUD update?
	int m_FramesSinceLastHUDUpdate = 0;
	
	//At what point should the Hud be refreshed
	int m_TargetFramesPerHUDUpdate = 60;
	
	// A regular RenderWindow
	sf::RenderWindow m_Window;

	// The main Views
	sf::View m_MainView;
	sf::View m_MiniMap;

	// Two views for the background
	//Main view for background/Window
	sf::View m_BGMainView;
	//MiniMap view for MiniMap Background/Window
	sf::View m_BGMiniMap;

	//  One view for the HUD
	sf::View m_HudView;

	// Declare a sprite for the background
	sf::Sprite m_BackgroundSprite;
	//Declare a Texture for the background
	sf::Texture m_BackgroundTexture;

	// Declare a sprite and a Texture for the background in the Menu
	sf::Sprite m_MenuBackgroundSprite;
	//Background Texture for the Menu
	sf::Texture m_MenuBackgroundTexture;
	
	// Varaibles for the GIF background
	sf::Image m_animatedBackgroundImage;
	//Current Frame of animated background
	int m_animatedBackgroundFrame = 0;
	//Maximum Number of frames for animated background
	int m_animatedBackgroundMaxFrames = 1129;

	// Declare a sprite for the background in the EndCredits
	sf::Sprite m_EndBackgroundSprite;
	//End Credits background Texture
	sf::Texture m_EndBackgroundTexture;

	// Varaibles for the EndCredits GIF background
	sf::Image m_endAnimatedBackgroundImage;
	//Current Frame for animation background in end credits
	int m_endAnimatedBackgroundFrame = 38;
	//Maximum frames for animation background for end credits
	int m_endAnimatedBackgroundMaxFrames = 203;

	// How much time is left in the current level
	float m_TimeRemaining;
	//Current runt time of the game
	sf::Time m_GameTimeTotal;
	//Current run time of the frame
	sf::Time dt;
	//Float holds the run time for this frame displayed in seconds
	float dtAsSeconds;

	// The vertex array for the level design
	sf::VertexArray m_VALevel;

	// The 2d array with the map for the level
	// A pointer to a pointer
	int** m_ArrayLevel = nullptr;

	// Texture for the background and the level tiles
	sf::Texture m_TextureTiles;

	// Private functions for internal use only
	//Input function handles player inpit
	void input();
	//Update updates all Assets for the current frame
	void update(float dtAsSeconds);
	//Draw the current Frame to the screen
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

	//Spawn Laserpointer 
	void spawnLasers();
	// Run will call all the private functions
	bool detectCollisions(PlayableCharacter& character);

	// A vector of Vector2f for the fire emiiter locations
	//std::vector <sf::Vector2f> m_FireEmitters;

	// Where is the mouse in relation to world coordinates
	sf::Vector2f mouseWorldPosition;
	
	// Where is the mouse in relation to screen coordinates
	sf::Vector2i mouseScreenPosition;

	// Button Lists
	void initButtons();
	sf::Font m_buttonFont;

	//	Main Menu
	std::list<GUI::Button> m_mainMenuButtons;
	//	Paused
	std::list<GUI::Button> m_pausedButtons;
	//	Level Select
	std::list<GUI::Button> m_levelSelectButtons;
	//	Settings
	std::list<GUI::Button> m_settingsButtons;
	//	Graphics Settings
	std::list<GUI::Button> m_graphicsSettingsButtons;
	//	Audio Settings
	std::list<GUI::Button> m_audioSettingsButtons;
	//	Gameplay Settings
	std::list<GUI::Button> m_gameplaySettingsButtons;

	//Bullets
	Bullet bullets[5];	//	Max bullets in play
	//Number of Bullets currently in flight
	int currentBullet = 0;
	//How long since the last bullet was fired
	sf::Time m_SinceLastShot;

	//update door states
	void doorUpdate(float dtAsSeconds, ToggleSwitch *Switch);
	
	//calculate distance from enemy to player
	float calcDistance(sf::Vector2f posOne, sf::Vector2f posTwo);	
};
#endif // !ENGINE_H