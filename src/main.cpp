#include <stdlib.h>
#include "app.h"
#include "globals.h"
#include "memleaks.h"

#include "SDL/SDL.h"

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

int main(int argc, char** argv)
{
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
			case MAIN_CREATION:
				App = new Application();
				state = MAIN_START;
				break;
			case MAIN_START:
				state = (App->Init() == false) ? MAIN_EXIT : MAIN_UPDATE;
				break;
			case MAIN_UPDATE:
			{
				int update_return = App->Update();

				if (update_return == UPDATE_ERROR)
					state = MAIN_EXIT;
				else if (update_return == UPDATE_STOP)
					state = MAIN_FINISH;
			}
				break;
			case MAIN_FINISH:
			default:
				main_return = !(App->CleanUp() == false) ? EXIT_SUCCESS : main_return;
				state = MAIN_EXIT;
				break;
		}
	}

	delete App;
	return main_return;
}
