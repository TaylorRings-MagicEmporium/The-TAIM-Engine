#include "The_TAIM_Engine.h"

int main(int argc, char* args[])
{
	The_TAIM_Engine TTE = The_TAIM_Engine();

	TTE.SetupEngine();
	TTE.StartEngine();

	return 0;
}