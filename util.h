#ifndef __UTILITY_H_INCLUDED__
#define __UTILITY_H_INCLUDED__
#include <string>

struct Config
{	
	int GAME_BUILD[2]; //0 - Major, 1 - Minor, 2 - Build
	int RES_X, RES_Y;

	char GAME_VERSION[32];
	char GAME_TITLE[256];

	char KEY_UP = 'W';
};

#endif
