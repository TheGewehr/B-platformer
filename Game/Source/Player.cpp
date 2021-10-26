#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "Audio.h"
#include "Scene.h"

#include <string>
#include <stdio.h>

//#include "Particles.h"
//#include "Enemies.h"
//#include "Collisions.h"
//#include "Fonts.h"
//#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"
#include <math.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

Player::Player(bool startEnabled) : Module()
{
	// idle animations - just one sprite
	float idleSpeed = 0.01f;
	float animSpeed = 0.15f;
	float hitSpeed = 0.1f;
	float deathSpeed = 0.1f;

	iFrameTimerReference = 180;
	iFrameTimer = iFrameTimerReference;
	in_iFrame = false;

	backTimerReference = 180;
	backTimer = backTimerReference;

	//animation idle left
	leftIdleAnim.PushBack({ 141, 102, 23, 41 });
	leftIdleAnim.PushBack({ 171, 102, 21, 40 });
	leftIdleAnim.loop = true;
	leftIdleAnim.speed = idleSpeed;

	//animation idle right 
	rightIdleAnim.PushBack({ 144, 286, 24, 41 });
	rightIdleAnim.PushBack({ 177, 287, 24, 41 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = idleSpeed;

	// Death Animations
	deathFromLeftAnim.PushBack({ 216, 448, 24, 35 });
	deathFromLeftAnim.PushBack({ 245, 450, 23, 35 });
	deathFromLeftAnim.PushBack({ 272, 452, 31, 35 });
	deathFromLeftAnim.PushBack({ 305, 457, 37, 31 });
	deathFromLeftAnim.loop = false;
	deathFromLeftAnim.speed = deathSpeed;

	deathFromRightAnim.PushBack({ 10, 397, 26, 41 });
	deathFromRightAnim.PushBack({ 41, 394, 26, 41 });
	deathFromRightAnim.PushBack({ 73, 392, 28, 41 });
	deathFromRightAnim.PushBack({ 111, 383, 35, 51 });
	deathFromRightAnim.loop = false;
	deathFromRightAnim.speed = deathSpeed;

	// Move Animations
	upAnim.PushBack({ 12, 7, 13, 42 });
	upAnim.PushBack({ 44, 7, 13, 42 });
	upAnim.PushBack({ 76, 7, 13, 42 });
	upAnim.PushBack({ 108, 7, 13, 42 });
	upAnim.loop = true;
	upAnim.speed = animSpeed;

	leftAnim.PushBack({ 6, 103, 31, 41 });
	leftAnim.PushBack({ 39, 103, 31, 41 });
	leftAnim.PushBack({ 72, 103, 31, 41 });
	leftAnim.PushBack({ 103, 103, 31, 41 });
	leftAnim.loop = true;
	leftAnim.speed = animSpeed;

	rightAnim.PushBack({ 8, 285, 31, 38 });
	rightAnim.PushBack({ 43, 285, 27, 41 });
	rightAnim.PushBack({ 71, 285, 30, 36 });
	rightAnim.PushBack({ 108, 285, 26, 36 });
	rightAnim.loop = true;
	rightAnim.speed = animSpeed;
}

Player::~Player()
{
}

bool Player::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	//Add textures -> remember unload
	texture = app->tex->Load("Assets/Sprites/character_sprites.png");
	exitTexture = app->tex->Load("Assets/Sprites/quit_icon.png");
	//lifeBarTexture = app->tex->Load("Assets/Sprites/player_life_bar.png");

	currentAnimation = &downIdleAnim;

	//Add audio -> remember unload
	/*laserFx = App->audio->LoadFx("Assets/Fx/gun_shot.wav");
	bombFx = App->audio->LoadFx("Assets/Fx/explosion_02.wav");
	deathFx = App->audio->LoadFx("Assets/Fx/player_death.wav");
	rockFallFx = App->audio->LoadFx("Assets/Fx/rock_falling.wav");
	*/

	position.x = 550;
	position.y = 1400;

	lastDirection = 5;

	//collBox = App->collisions->AddCollider({ (int)position.x, (int)position.y, playerWidth, playerHeight }, Collider::Type::PLAYER_COLLBOX, this);
	//hitBox = App->collisions->AddCollider({ (int)position.x, (int)position.y + 15, 25, 25}, Collider::Type::PLAYER_HITBOX, this);
	
	/*
	hitBox = app->collisions->AddCollider({ (int)position.x, (int)position.y + 30, playerWidth, playerHeight }, Collider::Type::PLAYER_HITBOX, this);

	colBoxUp = app->collisions->AddCollider({ (int)position.x, (int)position.y - speed, playerWidth, speed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxUpLeft = app->collisions->AddCollider({ (int)position.x - diagonalSpeed, (int)position.y - diagonalSpeed, diagonalSpeed, diagonalSpeed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxLeft = app->collisions->AddCollider({ (int)position.x - speed, (int)position.y, speed, playerHeight }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxDownLeft = app->collisions->AddCollider({ (int)position.x - diagonalSpeed, (int)position.y + playerHeight + diagonalSpeed, diagonalSpeed, diagonalSpeed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxDown = app->collisions->AddCollider({ (int)position.x, (int)position.y + playerHeight, playerWidth, speed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxDownRight = app->collisions->AddCollider({ (int)position.x + playerWidth, (int)position.y + playerHeight, diagonalSpeed, diagonalSpeed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxRight = app->collisions->AddCollider({ (int)position.x + playerWidth, (int)position.y, speed, playerHeight }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxUpRight = app->collisions->AddCollider({ (int)position.x, (int)position.y - diagonalSpeed, diagonalSpeed, diagonalSpeed }, Collider::Type::PLAYER_COLLBOX, this);
	*/

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable1[] = { "0123456789abcdefghijklmnopqrstuvwxyz                       " };
	char lookupTable2[] = { "0123456789:;<=>?*abcdefghijklmnopqrstuvwxyz@çççççççççç          " };
	char lookupTable3[] = { "0123456789çççççççççççççççççççççççççççççççççççççççççççççççççççççççççççççç        " };
	char lookupTable4[] = { "çççççççççççççççç0123456789abcdefghijklmnopqrstuvwxyççççççççççççççççççççç        " };
	char lookupTable5[] = { "çççççççççççççççççççççççççççççççççççççççççççççççççççççççç0123456789çççççç        " };
	char lookupTable6[] = { "çççççççççççççççççççççççççççççççççççççççççççç0123456789          " };
	char lookupTable7[] = { "çççççççççççççççççççççççççççççççççççççççççççççççççççççççç0123456789çççççç        " };
	
	/*
	playerScoreFont = app->fonts->Load("Assets/Fonts/player_score_font.png", lookupTable2, 2);
	endLevelFontGreen = app->fonts->Load("Assets/Fonts/game_over_fonts_big.png", lookupTable4, 5);
	bigGreyFont = app->fonts->Load("Assets/Fonts/game_over_fonts_big.png", lookupTable5, 5);
	endLevelFontPink = app->fonts->Load("Assets/Fonts/game_over_fonts_big.png", lookupTable3, 5);
	bombCounterFont = app->fonts->Load("Assets/Fonts/player_score_font.png", lookupTable6, 2);
	*/

	return ret;
}

Result Player::Update()
{
	Result ret = Result::UPDATE_CONTINUE;

	////////////////////////////////////////////////////////
	// Moving the player with the camera scroll
	//App->player->position.x += 0;
	////////////////////////////////////////////////////////

	//colUp = false;
	//colUpLeft = false;
	//colLeft = false;
	//colDownLeft = false;
	//colDown = false;
	//colDownRight = false;
	//colRight = false;
	//colUpRight = false;

	keyUp = App->input->keys[SDL_SCANCODE_W];
	keyLeft = App->input->keys[SDL_SCANCODE_A];
	keyDown = App->input->keys[SDL_SCANCODE_S];
	keyRight = App->input->keys[SDL_SCANCODE_D];
	shoot = App->input->keys[SDL_SCANCODE_SPACE];

	// lastDirection
	// 
	//	1 = jump
	//  2 = left
	//  3 = right
	//

	// Move the player in all posible direction 
	//AXIS MOVEMENT
	// 
	//left
	if (!destroyed) 
	{
		if ((keyUp == KEY_STATE::KEY_IDLE)
			&& (keyLeft == KEY_STATE::KEY_REPEAT)
			&& (keyDown == KEY_STATE::KEY_IDLE)
			&& (keyRight == KEY_STATE::KEY_IDLE))
		{
			lastDirection = 3;

			if (!colCheck[2])
			{
				position.x -= speed;
				SetAnimation(leftAnim);
				colCheck[2] = false;
			}
			else {
				SetAnimation(leftIdleAnim);
			}
		}

		//right
		if ((keyUp == KEY_STATE::KEY_IDLE)
			&& (keyLeft == KEY_STATE::KEY_IDLE)
			&& (keyDown == KEY_STATE::KEY_IDLE)
			&& (keyRight == KEY_STATE::KEY_REPEAT))
		{
			lastDirection = 7;




			if (!colCheck[6])
			{
				position.x += speed;
				SetAnimation(rightAnim);
				colCheck[5] = false;
			}
			else {
				SetAnimation(rightIdleAnim);
			}
		}

	for (int i = 0; i < 8; i++)
	{
		colCheck[i] = false;
	}


	//camera control

	if (canMoveCamera) {

		switch (level) {

		case 0:

			if (keyRight == KEY_STATE::KEY_REPEAT) {

				if (app->render->camera.y + app->render->camera.h > 500) {


					if (app->render->camera.x / SCREEN_SIZE + app->render->camera.w + speed < 1083)
					{

						if (lastDirection % 2 != 0)
						{
							if (position.x + playerWidth > app->render->camera.x / SCREEN_SIZE + app->render->camera.w - horizontalMargin) {
								app->render->camera.x += speed * SCREEN_SIZE;
							}
						}
						else
						{
							if (position.x + playerWidth > app->render->camera.x / SCREEN_SIZE + app->render->camera.w - horizontalMargin) {
								app->render->camera.x += diagonalSpeed * SCREEN_SIZE;
							}
						}

					}

				}
				else
				{

					if (app->render->camera.x / SCREEN_SIZE + app->render->camera.w + speed < 1242)
					{

						if (lastDirection % 2 != 0)
						{
							if (position.x + playerWidth > app->render->camera.x / SCREEN_SIZE + app->render->camera.w - horizontalMargin) {
								app->render->camera.x += speed * SCREEN_SIZE;
							}
						}
						else
						{
							if (position.x + playerWidth > app->render->camera.x / SCREEN_SIZE + app->render->camera.w - horizontalMargin) {
								app->render->camera.x += diagonalSpeed * SCREEN_SIZE;
							}
						}

					}
				}

			}

			if (keyLeft == KEY_STATE::KEY_REPEAT) {


				if (app->render->camera.x / SCREEN_SIZE - speed > 474)
				{

					if (lastDirection % 2 != 0)
					{
						if (position.x < app->render->camera.x / SCREEN_SIZE + horizontalMargin) {
							app->render->camera.x -= speed * SCREEN_SIZE;
						}
					}
					else
					{
						if (position.x < app->render->camera.x / SCREEN_SIZE + horizontalMargin) {
							app->render->camera.x -= diagonalSpeed * SCREEN_SIZE;
						}
					}

				}

			}

			if (app->render->camera.y / SCREEN_SIZE <= 1156) {

				if (lastDirection % 2 == 0)
				{
					if (position.y <= (app->render->camera.y / SCREEN_SIZE + verticalMargin) && app->render->camera.y / SCREEN_SIZE - diagonalSpeed >= 0) App->render->camera.y -= diagonalSpeed * SCREEN_SIZE;
				}
				else
				{
					if (position.y < (app->render->camera.y / SCREEN_SIZE + verticalMargin) && app->render->camera.y / SCREEN_SIZE - speed >= 0) App->render->camera.y -= speed * SCREEN_SIZE;
				}
			}

			break;

		case 1:

			if (keyRight == KEY_STATE::KEY_REPEAT) {

				if (app->render->camera.x / SCREEN_SIZE + app->render->camera.w + speed < 768)
				{

					if (lastDirection % 2 != 0)
					{
						if (position.x + playerWidth > app->render->camera.x / SCREEN_SIZE + app->render->camera.w - horizontalMargin) {
							app->render->camera.x += speed * SCREEN_SIZE;
						}
					}
					else
					{
						if (position.x + playerWidth > app->render->camera.x / SCREEN_SIZE + app->render->camera.w - horizontalMargin) {
							app->render->camera.x += diagonalSpeed * SCREEN_SIZE;
						}
					}

				}



			}

			if (keyLeft == KEY_STATE::KEY_REPEAT) {


				if (app->render->camera.x / SCREEN_SIZE - speed > 0)
				{

					if (lastDirection % 2 != 0)
					{
						if (position.x < app->render->camera.x / SCREEN_SIZE + horizontalMargin) {
							app->render->camera.x -= speed * SCREEN_SIZE;
						}
					}
					else
					{
						if (position.x < app->render->camera.x / SCREEN_SIZE + horizontalMargin) {
							app->render->camera.x -= diagonalSpeed * SCREEN_SIZE;
						}
					}

				}

			}

			if (app->render->camera.y / SCREEN_SIZE <= 3072) {

				if (lastDirection % 2 == 0)
				{
					if (position.y <= (App->render->camera.y / SCREEN_SIZE + verticalMargin)
						&& App->render->camera.y / SCREEN_SIZE - diagonalSpeed >= 0) App->render->camera.y -= diagonalSpeed * SCREEN_SIZE;
				}
				else
				{
					if (position.y < (App->render->camera.y / SCREEN_SIZE + verticalMargin)
						&& App->render->camera.y / SCREEN_SIZE - speed >= 0) App->render->camera.y -= speed * SCREEN_SIZE;
				}
			}

			break;

		}
	}

	////////////////////////////////////////////////

	if (shoot == KEY_STATE::KEY_DOWN)
	{
		int posOffsetX = 0;
		int posOffsetY = 0;

		switch (lastDirection) {
		case 1:
			posOffsetX = 13;

			break;
		case 2:
			posOffsetX = 4;
			posOffsetY = 1;
			break;
		case 3:
			posOffsetX = 0;
			posOffsetY = 9;
			break;
		case 4:
			posOffsetX = PlayerWidthOffset;
			posOffsetY = 16;
			break;
		case 5:
			posOffsetX = 7;
			posOffsetY = 24;
			break;
		case 6:
			posOffsetX = 17;
			posOffsetY = 18;
			break;
		case 7:
			posOffsetX = 19;
			posOffsetY = 11;
			break;
		case 8:
			posOffsetX = 20;
			posOffsetY = 4;
			break;
		}
		for (size_t i = 0; i < 3; i++)
		{
			App->particles->AddParticle(App->particles->playerBullet1[lastDirection - 1], 0, position.x + posOffsetX, position.y + posOffsetY, lastDirection, Collider::Type::PLAYER_SHOT, i * 4);
		}
		App->audio->PlayFx(laserFx);
	}
	if ((App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN) || (App->fade->credits <= 0 || App->scene->levelTimer <= 0))
	{
		destroyed = true;
		//App->particles->AddParticle(App->particles->playerBullet1[lastDirection - 1], 0, position.x, position.y, lastDirection, Collider::Type::PLAYER_SHOT);
		//App->audio->PlayFx(laserFx);
	}

	/*
	if (App->input->keys[SDL_SCANCODE_LSHIFT] == KEY_STATE::KEY_DOWN)
	{
		if (App->fade->credits < 9)
		{
			App->fade->credits++;
		}

	}
	*/

	/*
	if (playerLife <= 0)
	{
		App->audio->PlayFx(deathFx);
		App->fade->credits--;
		playerLife = playerMaximumLife;
	}
	*/

	////////////////////////////////////////////////

	// Idle Animations 
	if ((keyUp == KEY_STATE::KEY_IDLE)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& (keyRight == KEY_STATE::KEY_IDLE)
		) {

		switch (lastDirection) {

		case 1:


			SetAnimation(upIdleAnim);
			break;

		case 2:

			SetAnimation(upLeftIdleAnim);
			break;

		case 3:

			SetAnimation(leftIdleAnim);
			break;

		case 4:

			SetAnimation(downLeftIdleAnim);
			break;

		case 5:

			SetAnimation(downIdleAnim);
			break;

		case 6:

			SetAnimation(downRightIdleAnim);
			break;

		case 7:

			SetAnimation(rightIdleAnim);
			break;

		case 8:


			SetAnimation(upRightIdleAnim);
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
			if (currentAnimation != &deathFromUpAnim)

				SetAnimation(deathFromUpAnim);
			break;

		case 2:
			if (currentAnimation != &deathFromUpAnim)
				SetAnimation(deathFromUpAnim);
			break;

		case 3:
			if (currentAnimation != &deathFromLeftAnim)
				SetAnimation(deathFromLeftAnim);
			break;

		case 4:
			if (currentAnimation != &deathFromLeftAnim)
				SetAnimation(deathFromLeftAnim);
			break;

		case 5:
			if (currentAnimation != &deathFromDownAnim)
				SetAnimation(deathFromDownAnim);
			break;

		case 6:
			if (currentAnimation != &deathFromDownAnim)
				SetAnimation(deathFromDownAnim);
			break;

		case 7:
			if (currentAnimation != &deathFromRightAnim)
				SetAnimation(deathFromRightAnim);
			break;

		case 8:
			if (currentAnimation != &deathFromRightAnim)
				SetAnimation(deathFromRightAnim);
			break;

		}
	}

	////////////////////////////////////////////

	hitBox->SetPos(position.x, position.y + playerHeightOffset);

	colBoxUp->SetPos(position.x, position.y - speed + playerHeightOffset);
	colBoxUpLeft->SetPos(position.x - diagonalSpeed, position.y - diagonalSpeed + playerHeightOffset);
	colBoxLeft->SetPos(position.x - speed, position.y + playerHeightOffset);
	colBoxDownLeft->SetPos(position.x - diagonalSpeed, position.y + playerHeight + playerHeightOffset);
	colBoxDown->SetPos(position.x, position.y + playerHeight + playerHeightOffset);
	colBoxDownRight->SetPos(position.x + playerWidth, position.y + playerHeight + playerHeightOffset);
	colBoxRight->SetPos(position.x + playerWidth, position.y + playerHeightOffset);
	colBoxUpRight->SetPos(position.x + playerWidth, position.y - diagonalSpeed + playerHeightOffset);
	currentAnimation->Update();

	if (app->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT)
	{
		exit_counter++;
	}
	else {
		exit_counter = 0;
	}

	if (exit_counter >= 200) {

		ret = UpdateResult::UPDATE_STOP;
	}

	/*
	if (backTimer <= 0)
	{
		//exitCountdown--;
		//if (exitCountdown <= 0)
		app->fade->FadeToBlack(this, (Module*)App->fifthScene, 90);
	}
	*/

	/*
	if (app->player->backTimer < -60) {
		app->player->Disable();
	}
	*/

	////////////////////////////////////////////

	if (app->input->keys[SDL_SCANCODE_Z] == KEY_STATE::KEY_DOWN) score += 1000;
	if (app->input->keys[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN) playerLife++;
	if (app->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN) playerLife--;
	if (app->input->keys[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN) App->enemies->AddEnemy(ENEMY_TYPE::SOLDIER, position.x, position.y);

	return ret;
}