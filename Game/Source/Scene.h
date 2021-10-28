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

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

private:
	List<PhysBody*> circles;
	List<PhysBody*> boxes;
	List<PhysBody*> ricks;

	PhysBody* mapColisions;
	PhysBody* limits;

	PhysBody* sensor_loss;
	PhysBody* sensor_win;
	PhysBody* ricochet01;
	PhysBody* ricochet02;
	PhysBody* fliperLeft;
	PhysBody* fliperRight;
	
	bool sensed;


	float angularSpeedLeft;
	float maxAngleLeft;
	float minAngleLeft;
	float angleMarginLeft;

	float angularSpeedRight;
	float maxAngleRight;
	float minAngleRight;
	float angleMarginRight;


	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* map;
	SDL_Texture* fliper_left;
	SDL_Texture* fliper_right;
	SDL_Texture* img;

	uint bonus_fx;
	uint ball_lost_fx;
	uint win_fx;
	uint loose_fx;

	iPoint ray;
	bool ray_on;

	int lives;
	bool win_con;
	bool game_end;

	SDL_Rect end_rect;
	bool spawn_ball;
};

#endif // __SCENE_H__