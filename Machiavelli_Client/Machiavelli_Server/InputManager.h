#pragma once
#include <string>

class InputManager
{
public:
	InputManager();
	std::string HandleInput(std::string input);
	~InputManager();
};

