#pragma once
#include <string>

class InputManager
{
public:
	InputManager();
	~InputManager();

	std::string HandleInput(std::string input){	return input; }
};

