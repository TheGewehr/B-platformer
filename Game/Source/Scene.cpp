#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include "ModuleCollisions.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	//app->physics->Enable();
	// Defining chains

	
	// 
	app->map->Load("hello.tmx");
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	img = app->tex->Load("Assets/background/Background.png");

	


	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	app->render->DrawTexture(img, 0, 0, NULL);

    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 1;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 1;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 1;


	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	// Draw map
	app->map->Draw();

	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void Scene::OnCollision(Collider* c1, Collider* c2)
{


	//AXIAL
	if (c1 == app->player->colBoxUp && c2->type == Collider::WALL) {
		app->player->colCheck[0] = true;
	}
	if (c1 == app->player->colBoxLeft && c2->type == Collider::WALL) {
		app->player->colCheck[2] = true;
	}
	if (c1 == app->player->colBoxDown && c2->type == Collider::WALL) {
		app->player->colCheck[4] = true;
	}
	if (c1 == app->player->colBoxRight && c2->type == Collider::WALL) {
		app->player->colCheck[6] = true;
	}

	//DIAGONAL
	if (c1 == app->player->colBoxUpLeft && c2->type == Collider::WALL) {
		app->player->colCheck[1] = true;
	}
	if (c1 == app->player->colBoxDownLeft && c2->type == Collider::WALL) {
		app->player->colCheck[3] = true;
	}
	if (c1 == app->player->colBoxDownRight && c2->type == Collider::WALL) {
		app->player->colCheck[5] = true;
	}
	if (c1 == app->player->colBoxUpRight && c2->type == Collider::WALL) {
		app->player->colCheck[7] = true;
	}

	////rock
	//
	//if (c2 == app->scene->rockTrigger) {
	//	app->scene->rockAnimActivate = true;
	//	app->audio->PlayFx(rockFallFx);
	//	app->scene->rockTrigger->pendingToDelete = true;
	//}
	//
	//if (c2 == app->scene->bossTrigger) {
	//	if (App->scene->bossTrigger->pendingToDelete == false) App->enemies->AddEnemy(ENEMY_TYPE::BOSS_1, 1060, -190);
	//	App->scene->bossTrigger->pendingToDelete = true;
	//	canMoveCamera = false;
	//
	//
	//}

	if (app->collisions->debug) {
		if (c2->type == Collider::ENEMY_SHOT ) // && !in_iFrame
		{
			app->player->playerLife -= 1;
			//iFrameTimer = iFrameTimerReference;
			//in_iFrame = true;

		}
	}



}


