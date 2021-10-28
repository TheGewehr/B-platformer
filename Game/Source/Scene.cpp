#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Physics.h"

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
	app->physics->Enable();
	// Defining chains

	int mapCoords[72] = {
	-2, 417,
	129, 417,
	129, 437,
	351, 437,
	351, 417,
	383, 417,
	383, 538,
	449, 538,
	449, 481,
	511, 417,
	607, 417,
	607, 521,
	705, 521,
	705, 351,
	831, 224,
	1311, 224,
	1311, 287,
	831, 287,
	831, 417,
	929, 417,
	929, 441,
	1032, 441,
	1032, 417,
	1049, 417,
	1049, 442,
	1160, 442,
	1160, 417,
	1176, 417,
	1176, 442,
	1280, 442,
	1280, 417,
	1311, 417,
	1440, 288,
	1605, 288,
	1609, 505,
	-2, 628
	};

	// 
	app->map->Load("hello.tmx");
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	img = app->tex->Load("Assets/background/Background.png");

	circle = app->tex->Load("Assets/sprites/GraveRobberLeft.png");


	mapColisions = app->physics->CreateChain(0, 0, mapCoords, 72);
	mapColisions->body->SetType(b2_staticBody);


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

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		circles.add(app->physics->CreateCircle(100, 100, 16));
		circles.getLast()->data->listener = this;
	}

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


