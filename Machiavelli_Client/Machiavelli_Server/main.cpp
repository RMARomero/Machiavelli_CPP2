// main.cpp : Defines the entry point for the console application.
//

#include <time.h>
#include <stdlib.h>
#include "SocketManager.h"

#ifdef CRTDBG_MAP_ALLOC
HANDLE stream;
stream = CreateFile(dmpFilename, GENERIC_WRITE, FILE_SHARE_WRITE,
	NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
_CrtSetReportFile(_CRT_ERROR, stream);
_CrtSetReportFile(_CRT_WARN, stream);
_CrtDumpMemoryLeaks();
CloseHandle(stream);
#endif

int main(int argc, const char * argv[])
{
	srand(time(0));
	SocketManager::getInstance().start();
	return 0;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}


