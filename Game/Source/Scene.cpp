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

#include <iostream>

#include "Defs.h"


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
	//LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// Uploading the assets
	app->map->Load("hello.tmx");
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	img = app->tex->Load("Assets/background/Background.png");

	// MAP colliders
	//app->collisions->colliders[0] = new Collider({ 20, 20, 100, 100 }, Collider::Type::WALL, this);
	// Ground colliders
	app->collisions->AddCollider({ 0, 416, 128, 64 }, Collider::Type::WALL,this);
	app->collisions->AddCollider({ 352, 416, 32, 64 }, Collider::Type::WALL,this);
	app->collisions->AddCollider({ 511, 416, 97, 64 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 704, 351, 128, 129 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 831, 224, 481, 64 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 832, 416, 96, 64 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1159, 416, 18, 64 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1031, 416, 18, 64 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1280, 416, 32, 64 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1439, 288, 161, 192 }, Collider::Type::WALL, this);
		// Platform colliders
	app->collisions->AddCollider({ 128, 288, 224, 32 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 448, 192, 32, 32 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 544, 256, 64, 32 }, Collider::Type::WALL, this);

		// Ramp 1 colliders
	app->collisions->AddCollider({ 456, 472, 55, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 465, 462, 46, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 474, 453, 37, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 483, 444, 28, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 492, 435, 19, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 501, 426, 10, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 511, 417, 9, 9 }, Collider::Type::WALL, this);

		// Ramp 2 colliders
	app->collisions->AddCollider({ 830, 225, 9, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 821, 234, 10, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 812, 243, 19, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 803, 252, 28, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 794, 261, 37, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 785, 270, 46, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 776, 279, 55, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 767, 288, 64, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 758, 297, 73, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 749, 306, 82, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 740, 315, 91, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 731, 324, 1100, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 722, 333, 109, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 713, 342, 118, 9 }, Collider::Type::WALL, this);

		// Ramp 3 colliders
	app->collisions->AddCollider({ 1438, 289, 9, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1429, 298, 10, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1420, 307, 19, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1411, 316, 28, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1402, 325, 37, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1393, 334, 46, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1384, 343, 55, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1375, 352, 64, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1366, 361, 73, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1357, 370, 82, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1348, 379, 91, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1339, 388, 100, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1330, 397, 109, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1321, 406, 118, 9 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1312, 415, 127, 44 }, Collider::Type::WALL, this);

	// Water colliders
	app->collisions->AddCollider({ 128, 417, 224, 63 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 928, 417, 103, 63 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1049, 417, 110, 63 }, Collider::Type::WALL, this);
	app->collisions->AddCollider({ 1177, 417, 103, 63 }, Collider::Type::WALL, this);

	if (app->player->IsEnabled() == 0)
	{
		app->player->Enable();
	}

	if (app->collisions->IsEnabled() == 0)
	{
		app->collisions->Enable();
	}

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


	//std::cout << "    " << app->player->xposition << "      " << app->player->yposition <<std::endl;

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	// Draw map
	app->map->Draw();

	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());


	//app->collisions->AddCollider();

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
	//LOG("Freeing scene");

	return true;
}

void Scene::OnCollision(Collider* c1, Collider* c2)
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


