#include "ModuleCollisions.h"

#include "App.h"
#include <iostream>

#include "Render.h"
#include "Player.h"
#include "Input.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions() : Module()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_HITBOX] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = true;

	matrix[Collider::Type::PLAYER_HITBOX][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_HITBOX][Collider::Type::PLAYER_HITBOX] = false;
	matrix[Collider::Type::PLAYER_HITBOX][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_HITBOX][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_HITBOX][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER_HITBOX][Collider::Type::POWER_UP] = true;
	matrix[Collider::Type::PLAYER_HITBOX][Collider::Type::OBSTACLE] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_HITBOX] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_HITBOX] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::OBSTACLE] = true;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_HITBOX] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::OBSTACLE][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::OBSTACLE][Collider::Type::PLAYER_HITBOX] = true;
	matrix[Collider::Type::POWER_UP][Collider::Type::PLAYER_HITBOX] = true;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

bool ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect) && (c2 != nullptr) && c1 != nullptr)
			{
				std::cout << " Hay una interseccion "<< std::endl;
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

bool ModuleCollisions::Update(float dt)
{
	// Here all movements are applyed
	app->player->yposition += GRAVITY;
	app->player->colBox->rect.y += GRAVITY;
	app->player->hitBox->rect.y += GRAVITY;

	// Player movement
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		app->player->yposition -= 2;
		app->player->colBox->rect.y -= 2;
		app->player->hitBox->rect.y -= 2;
	}
	
	
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		app->player->yposition += 1;
		app->player->colBox->rect.y += 1;
		app->player->hitBox->rect.y += 1;
	}
	
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		app->player->xposition -= 1;
		app->player->colBox->rect.x -= 1;
		app->player->hitBox->rect.x -= 1;
	}
	
	
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		app->player->xposition += 1;
		app->player->colBox->rect.x += 1;
		app->player->hitBox->rect.x += 1;
	}
	
	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
	{
		debug = !debug;
	
	}
	

	
		
	return true;
}

bool ModuleCollisions::PostUpdate()
{
	if (debug==true)
		DebugDraw();

	return true;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;


	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		//std::cout << " Aqui se printean los colliders " << colliders[i] << std::endl;

		switch (colliders[i]->type)
		{
		case Collider::Type::NONE: // white
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::WALL: // blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::BULLET_WALL: // blue
			app->render->DrawRectangle(colliders[i]->rect, 100, 0, 100, alpha);
			break;
		case Collider::Type::PLAYER_HITBOX: // green
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::PLAYER_COLLBOX: // green
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case Collider::Type::ENEMY: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::PLAYER_SHOT: // yellow
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case Collider::Type::ENEMY_SHOT: // magenta
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::POWER_UP: // magenta
			app->render->DrawRectangle(colliders[i]->rect, 34, 255, 54, alpha);
			break;
		case Collider::Type::OBSTACLE: // magenta
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 100, alpha);
			break;
		case Collider::Type::TRIGGER: // magenta
			app->render->DrawRectangle(colliders[i]->rect, 128, 128, 128, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	////LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;
	
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{

			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

int ModuleCollisions::GetMaxColliders() const {
	return MAX_COLLIDERS;
}

void ModuleCollisions::OnCollision(Collider* c1, Collider* c2)
{
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}

void ModuleCollisions::RemoveColliderType(Collider::Type type)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i]->type == type)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}
