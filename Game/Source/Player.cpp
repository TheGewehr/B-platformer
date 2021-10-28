#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "Audio.h"
#include "Scene.h"
#include "SDL/include/SDL_scancode.h"
#include <stdio.h>
#include <string>
#include <math.h>

//#include "Particles.h"
//#include "Collisions.h"
//#include "Enemies.h"
//#include "Fonts.h"

Player::Player(bool startEnabled) : Module() 
{
	float idleSpeed = 0.01f;
	float animSpeed = 0.15f;
	float hitSpeed = 0.1f;
	float deathSpeed = 0.1f;

	iFrameTimerReference = 180;
	iFrameTimer = iFrameTimerReference;
	in_iFrame = false;

	backTimerReference = 180;
	backTimer = backTimerReference;

	// IDLE animation right
	rightIdleAnim.PushBack({ 6, 15, 19, 33 });
	rightIdleAnim.PushBack({ 54, 15, 19, 33 });
	rightIdleAnim.PushBack({ 101, 15, 20, 33 });
	rightIdleAnim.PushBack({ 149, 15, 19, 33 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = idleSpeed;

	// Walking animation right
	walkingRigthAnim.PushBack({ 9, 63, 23, 33 });
	walkingRigthAnim.PushBack({ 58, 62, 20, 34 });
	walkingRigthAnim.PushBack({ 105, 61, 17, 35 });
	walkingRigthAnim.PushBack({ 151, 63, 19, 33 });
	walkingRigthAnim.PushBack({ 201, 62, 17, 34 });
	walkingRigthAnim.PushBack({ 250, 61, 21, 35 });
	walkingRigthAnim.loop = true;
	walkingRigthAnim.speed = idleSpeed;

	// Running animation right
	runningRigthAnim.PushBack({ 4, 111, 25, 33 });
	runningRigthAnim.PushBack({ 56, 113, 25, 31 });
	runningRigthAnim.PushBack({ 100, 113, 25, 31 });
	runningRigthAnim.PushBack({ 148, 112, 26, 32 });
	runningRigthAnim.PushBack({ 200, 113, 26, 31 });
	runningRigthAnim.PushBack({ 244, 113, 26, 31 });
	runningRigthAnim.loop = true;
	runningRigthAnim.speed = idleSpeed;

	// Jump animation right
	rightIdleAnim.PushBack({ 147, 8, 21, 41 });
	rightIdleAnim.PushBack({ 178, 8, 22, 42 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = idleSpeed;

	// IDLE animation right
	rightIdleAnim.PushBack({ 147, 8, 21, 41 });
	rightIdleAnim.PushBack({ 178, 8, 22, 42 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = idleSpeed;

	// IDLE animation right
	rightIdleAnim.PushBack({ 147, 8, 21, 41 });
	rightIdleAnim.PushBack({ 178, 8, 22, 42 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = idleSpeed;
}

Player::~Player() 
{

}

bool Player::Update() 
{

}

bool Player::PostUpdate()
{

}

void Player::OnCollision(Collider* c1, Collider* c2) 
{

}


void Player::SetAnimation(Animation &toChange) 
{

}