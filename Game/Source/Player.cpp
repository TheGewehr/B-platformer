#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "Audio.h"
#include "Scene.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>

//#include "Particles.h"
//#include "Enemies.h"
//#include "Fonts.h"

Player::Player() : Module()
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
	walkingRigthAnim.speed = animSpeed;

	// Running animation right
	runningRigthAnim.PushBack({ 4, 111, 25, 33 });
	runningRigthAnim.PushBack({ 56, 113, 25, 31 });
	runningRigthAnim.PushBack({ 100, 113, 25, 31 });
	runningRigthAnim.PushBack({ 148, 112, 26, 32 });
	runningRigthAnim.PushBack({ 200, 113, 26, 31 });
	runningRigthAnim.PushBack({ 244, 113, 26, 31 });
	runningRigthAnim.loop = true;
	runningRigthAnim.speed = 2 * animSpeed;

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
	deathFromRightAnim.loop = false;
	deathFromRightAnim.speed = deathSpeed;
}

Player::~Player()
{

}

bool Player::Start()
{
	// LOG("Loading player textures");

	bool ret = true;

	// Add textures
	texture = app->tex->Load("Assets/sprites/GraveRobber.png");

	currentAnimation = &rightIdleAnim;

	xposition = 15;
	yposition = 300;

	lastDirection = 5;

	colBox= app->collisions->AddCollider({ 20, 323, 16, 10 }, Collider::Type::PLAYER_COLLBOX, this);
	hitBox = app->collisions->AddCollider({ xposition, yposition, 20, 30 }, Collider::Type::PLAYER_HITBOX, this);

	return ret;
}

bool Player::Update()
{
	bool ret = true;
	
		


	///std::cout << "    " << xposition << "      " << yposition << std::endl;

	//colBox-xposition;

	///std::cout << "    " << colBox->rect.x << "      " << colBox->rect.y << std::endl;

	
	
	if (!destroyed) {
		// Left
		if ((keyUp == KeyState::KEY_IDLE)
			&& (keyLeft == KeyState::KEY_REPEAT)
			&& (keyDown == KeyState::KEY_IDLE)
			&& (keyRight == KeyState::KEY_IDLE))
		{
			lastDirection = 3;

			//if (!colCheck[2])
			//{
			//	xposition -= speed;
			//	SetAnimation(walkingRigthAnim);
			//	colCheck[2] = false;
			//}
			//else {
			//	SetAnimation(rightIdleAnim);
			//}
		}

		// Right
		if ((keyUp == KeyState::KEY_IDLE)
			&& (keyLeft == KeyState::KEY_IDLE)
			&& (keyDown == KeyState::KEY_IDLE)
			&& (keyRight == KeyState::KEY_REPEAT))
		{
			lastDirection = 7;

			//if (!colCheck[6])
			//{
			//	xposition += speed;
			//	SetAnimation(walkingRigthAnim);
			//	colCheck[5] = false;
			//}
			//else {
			//	SetAnimation(rightIdleAnim);
			//}
		}

		/*
		//Up
		
		if ((keyUp == KeyState::KEY_REPEAT)
			&& (keyLeft == KeyState::KEY_IDLE)
			&& (keyDown == KeyState::KEY_IDLE)
			&& (keyRight == KeyState::KEY_IDLE))
		{
			lastDirection = 1;

			if (!colCheck[0])
			{
				SetAnimation(upAnim);
				position.y -= speed;
				colCheck[0] = false;
			}
			else {
				SetAnimation(upIdleAnim);
			}
		}
		*/

		//Down
		/*
		if ((keyUp == KeyState::KEY_IDLE)
			&& (keyLeft == KeyState::KEY_IDLE)
			&& (keyDown == KeyState::KEY_REPEAT)
			&& (keyRight == KeyState::KEY_IDLE))
		{
			lastDirection = 5;

			if (!colCheck[4])
			{
				SetAnimation(downAnim);

				yposition += speed;
				colCheck[4] = false;
			}
			else {
				SetAnimation(downIdleAnim);
			}
		}
		*/
	}
	
	// Idle Animations 
	if ((keyUp == KeyState::KEY_IDLE)
		&& (keyLeft == KeyState::KEY_IDLE)
		&& (keyDown == KeyState::KEY_IDLE)
		&& (keyRight == KeyState::KEY_IDLE)
		) {

		switch (lastDirection) {

		case 1:

			SetAnimation(rightIdleAnim);
			break;

		case 2:

			SetAnimation(rightIdleAnim);
			break;

		}
	}

	// Death Animations
	if (destroyed == true)
	{
		backTimer--;
		currentAnimation->Reset();
		switch (lastDirection)
		{
		case 1:
			if (currentAnimation != &deathFromRightAnim)
				SetAnimation(deathFromRightAnim);
			break;

		case 2:
			if (currentAnimation != &deathFromRightAnim)
				SetAnimation(deathFromRightAnim);
			break;

		case 3:
			if (currentAnimation != &deathFromRightAnim)
				SetAnimation(deathFromRightAnim);
			break;

		case 4:
			if (currentAnimation != &deathFromRightAnim)
				SetAnimation(deathFromRightAnim);
			break;
		}
	}

	////////////////////////////////////////////
	//app->collisions->AddCollider({ xposition, yposition , 20,20}, Collider::Type::PLAYER_COLLBOX,this);
	//hitBox->SetPos(xposition, yposition + playerHeightOffset);
	
	//colBoxUp->SetPos(xposition, yposition - speed + playerHeightOffset);
	//colBoxUpLeft->SetPos(xposition - diagonalSpeed, yposition - diagonalSpeed + playerHeightOffset);
	//colBoxLeft->SetPos(xposition - speed, yposition + playerHeightOffset);
	//colBoxDownLeft->SetPos(xposition - diagonalSpeed, yposition + playerHeight + playerHeightOffset);
	//colBoxDown->SetPos(xposition, yposition + playerHeight + playerHeightOffset);
	//colBoxDownRight->SetPos(xposition + playerWidth, yposition + playerHeight + playerHeightOffset);
	//colBoxRight->SetPos(xposition + playerWidth, yposition + playerHeightOffset);
	//colBoxUpRight->SetPos(xposition + playerWidth, yposition - diagonalSpeed + playerHeightOffset);

	currentAnimation->Update();
	return ret;
}

bool Player::PostUpdate()
{
	if (backTimer > 0)
	{
		
		if (in_iFrame)
		{
			iFrameTimer--;
		
			if (((iFrameTimer % 10) >= 0) && ((iFrameTimer % 10) <= 5))
			{
				app->render->DrawTexture(texture, xposition + playerWidthOffset, yposition, &currentAnimation->GetCurrentFrame(), 1);
	
			}
	
			if (iFrameTimer <= 0) in_iFrame = !in_iFrame;
		}
		else
		{
			app->render->DrawTexture(texture, xposition + playerWidthOffset, yposition, &currentAnimation->GetCurrentFrame(), 1);
		}
	}
	
	return true;
}

void Player::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (app->collisions->colliders[i] == nullptr)
			continue;

		if (c1->type == Collider::PLAYER_COLLBOX && c2->type == Collider::WALL) {
			app->player->yposition -= GRAVITY;
		}
	}
}


void Player::SetAnimation(Animation& toChange)
{
	if (currentAnimation != &toChange) {

		toChange.Reset();
		currentAnimation = &toChange;
	}
}