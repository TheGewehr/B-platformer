#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "App.h"
#include "Module.h"
#include "Animation.h"
#include "Input.h"
//#include "p2Point.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

#define PLAYER_LIFES_LEFT 3

struct SDL_Texture;
struct Collider;

class Player : public Module
{
public:
	// Constructor
	Player(bool startEnabled);

	// Destructor
	~Player();

	// Loads the necessary textures for the player
	bool Start();

	// Performs new input and handles player movement
	bool Update();

	//Performs the render call of the player sprite
	bool PostUpdate();

	void OnCollision(Collider* c1, Collider* c2);

public:
	// Position of the player in the map
	int xposition;
	int yposition;

	int GetPlayerPosition() const
	{
		return xposition;
		return yposition;;
	}

	// Camera
	SDL_Rect camera;
	int level;

	// Margin of movement
	int horizontalMargin = 1600;
	int verticalMargin = 480;

	// The speed in which we move the player (pixels per frame)
	int speed = 2;
	int diagonalSpeed = 1;

	//The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* curentAnimation = nullptr;

	// Set of animations
	// IDLE animations
	Animation rightIdleAnim;

	// Walking Animations
	Animation walkingRigthAnim;

	// Running Animations
	Animation runningRigthAnim;

	// Jumping Animations
	Animation jumpingRigthAnim;

	// Damage Animatios
	Animation hitFromRightAnim;

	// Death Animation
	Animation deathFromRightAnim;

	void SetAnimation(Animation& toChange);

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	int playerMaximumLife = 100;
	int playerLife = playerMaximumLife;
	int playerWidth = 10;
	int playerHeight = 7;
	int playerHeightOffset = 12;
	int playerWidthOffset = 2;

	// A countdown to when the player gets destroyed. After a while the game exits
	uint exitCountdown = 120;

	// Player keys
	KeyState keyUp;
	KeyState keyRight;
	KeyState keyDown;
	KeyState keyLeft;
	KeyState keyJump;

	KeyState lastHorizontalKey;
	KeyState lastVerticalKey;
	int lastDirection;

	int iFrameTimerReference;
	int iFrameTimer;
	bool in_iFrame;

	int canMoveCamera = true;

	// Exit
	int exit_counter;
	SDL_Texture* exitTexture;

	//return to enter credit scene
	int backTimerReference;
	int backTimer;
};

#endif //!__PLAYER_H__