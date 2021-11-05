#include "ModuleCollisions.h"

#include "App.h"
#include <iostream>

#include "Render.h"
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

			if (c1->Intersects(c2->rect))
			{
				if (matrix[c1->type][c2->type] && c1->listener)
					c1->listener->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->listener)
					c2->listener->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

bool ModuleCollisions::Update()
{
	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
		debug = !debug;

	return true;
}

bool ModuleCollisions::PostUpdate()
{
	if (debug)
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

		std::cout << " Aqui se printean los colliders " << colliders[i] << std::endl;

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
