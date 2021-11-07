#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "Globals.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	
	//Collider* playerWall[100] = { nullptr };

private:
	
	SDL_Texture* map;
	
	SDL_Texture* img;

	uint bonus_fx;
	
	SDL_Rect end_rect;
	

	List<PhysBody*> static_chains;
	//p2List<PhysBody*> mapStaticBodies;

	PhysBody* sensor_loss;
	PhysBody* sensor_win;
	PhysBody* sensor_out;
	PhysBody* ricochet01;
	PhysBody* ricochet02;
	PhysBody* fliperLeft;
	PhysBody* fliperRight;
};

#endif // __SCENE_H__