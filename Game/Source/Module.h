#ifndef __MODULE_H__
#define __MODULE_H__

#include "SString.h"
#include "Globals.h"

#include "PugiXml/src/pugixml.hpp"

class App;
class PhysBody;

class Module
{
private:
	bool enabled;

public:
	App* Application;

	Module(App* parent, bool start_enabled = true) : Application(parent), enabled(start_enabled)
	{}

	bool IsEnabled() const
	{
		return enabled;
	}

	void Enable()
	{
		if (enabled == false)
		{
			enabled = true;
			Start();
		}
	}

	void Disable()
	{
		if (enabled == true)
		{
			enabled = false;
			CleanUp();
		}
	}

	void Init()
	{
		active = true;
	}

	// Called before render is available
	// L01: DONE 5: Sending config file to all modules
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	virtual void OnCollision(PhysBody* bodyA, PhysBody* bodyB)
	{
	}

    // L02: DONE 2: Create new virtual methods to Load / Save state
	virtual bool LoadState(pugi::xml_node&)
	{
		return true;
	}

	virtual bool SaveState(pugi::xml_node&) const
	{
		return true;
	}

public:

	SString name;
	bool active;

};

#endif // __MODULE_H__