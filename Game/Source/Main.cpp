#include "App.h"

#include "Defs.h"


// NOTE: SDL redefines main function
#include "SDL/include/SDL.h"

// NOTE: Library linkage is configured in Linker Options
//#pragma comment(lib, "../Game/Source/External/SDL/libx86/SDL2.lib")
//#pragma comment(lib, "../Game/Source/External/SDL/libx86/SDL2main.lib")

#include <stdlib.h>

enum MainState
{
	CREATE = 1,
	AWAKE,
	START,
	LOOP,
	CLEAN,
	FAIL,
	EXIT
};

int main(int argc, char* args[])
{
	//LOG("Engine starting ...");

	MainState state = CREATE;
	int result = EXIT_FAILURE;
	App* app_ = NULL;


	while(state != EXIT)
	{
		switch(state)
		{

			// Allocate the engine --------------------------------------------
			case CREATE:
			//LOG("CREATION PHASE ===============================");

				app_ = new App(argc, args);

			if(app_ != NULL)
				state = AWAKE;
			else
				state = FAIL;

			break;

			// Awake all modules -----------------------------------------------
			case AWAKE:
			//LOG("AWAKE PHASE ===============================");
			if(app_->Awake() == true)
				state = START;
			else
			{
				//LOG("ERROR: Awake failed");
				state = FAIL;
			}

			break;

			// Call all modules before first frame  ----------------------------
			case START:
			//LOG("START PHASE ===============================");
			if(app_->Start() == true)
			{
				state = LOOP;
				//LOG("UPDATE PHASE ===============================");
			}
			else
			{
				state = FAIL;
				//LOG("ERROR: Start failed");
			}
			break;

			// Loop all modules until we are asked to leave ---------------------
			case LOOP:
			if(app_->Update() == false)
				state = CLEAN;
			break;

			// Cleanup allocated memory -----------------------------------------
			case CLEAN:
			//LOG("CLEANUP PHASE ===============================");
			if(app_->CleanUp() == true)
			{
				RELEASE(app_);
				result = EXIT_SUCCESS;
				state = EXIT;
			}
			else
				state = FAIL;

			break;

			// Exit with errors and shame ---------------------------------------
			case FAIL:
			//LOG("Exiting with errors :(");
			result = EXIT_FAILURE;
			state = EXIT;
			break;
		}
	}

	//LOG("... Bye! :)\n");

	// Dump memory leaks
	return result;
}