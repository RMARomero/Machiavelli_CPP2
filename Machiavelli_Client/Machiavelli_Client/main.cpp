// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include <crtdbg.h>
#include "GameLoop.h"
#include <memory>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	shared_ptr<GameLoop> loop{ new GameLoop() };
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}

