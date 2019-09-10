#include "Game.h"
#include "MainMenu.h"

int main(int argc, const char **argv)
{
	MainMenu menu;
	menu.run();
	
	//Si on joue
	if (!menu.getQuit())
	{
		Game g;
		g.run();
	}

    return 0;
}
