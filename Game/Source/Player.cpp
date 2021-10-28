#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "Audio.h"
#include "Scene.h"
#include "Globals.h"
#include "Collider.h"

#include "SDL/include/SDL_scancode.h"
#include <stdio.h>
#include <string>
#include <math.h>

//#include "Particles.h"
//#include "Enemies.h"
//#include "Fonts.h"

Player::Player(bool startEnabled) : Module(startEnabled)
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

	// Jumping animation right
	jumpingRigthAnim.PushBack({ 9, 209, 16, 31 });
	jumpingRigthAnim.PushBack({ 54, 208, 18, 32 });
	jumpingRigthAnim.PushBack({ 100, 206, 20, 34 });
	jumpingRigthAnim.PushBack({ 148, 201, 19, 34 });
	jumpingRigthAnim.PushBack({ 195, 198, 19, 39 });
	jumpingRigthAnim.PushBack({ 243, 200, 20, 34 });
	jumpingRigthAnim.loop = true;
	jumpingRigthAnim.speed = idleSpeed;

	// Getting hit right
	hitFromRightAnim.PushBack({ 6, 255, 19, 33 });
	hitFromRightAnim.PushBack({ 55, 255, 19, 33 });
	hitFromRightAnim.PushBack({ 103, 255, 18, 33 });
	hitFromRightAnim.loop = false;
	hitFromRightAnim.speed = hitSpeed;

	// Death animation right
	deathFromRightAnim.PushBack({ 6, 303, 19, 33 });
	deathFromRightAnim.PushBack({ 52, 308, 23, 28 });
	deathFromRightAnim.PushBack({ 99, 312, 32, 24 });
	deathFromRightAnim.PushBack({ 147, 318, 35, 18 });
	deathFromRightAnim.PushBack({ 195, 321, 34, 15 });
	deathFromRightAnim.PushBack({ 243, 324, 35, 12 });
	deathFromRightAnim.loop = true;
	deathFromRightAnim.speed = deathSpeed;
}

Player::~Player()
{

}

bool Player::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	// Add textures
	texture = app->tex->Load("Assets/sprites/GraveRobber.png");

	xposition = 550;
	yposition = 1400;

	lastDirection = 2;
	return ret;
}

update_status Player::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

}

update_status Player::PostUpdate()
{

}

void Player::OnCollision(Collider* c1, Collider* c2)
{

}


void Player::SetAnimation(Animation& toChange)
{

}