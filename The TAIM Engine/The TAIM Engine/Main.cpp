#include "The_TAIM_Engine.h"


// Main's only job is to enable the engine by initialisating, setting up and then starting it
int main(int argc, char* args[])
{
	The_TAIM_Engine TTE = The_TAIM_Engine();

	TTE.SetupEngine();
	TTE.StartEngine();

	return 0;
}