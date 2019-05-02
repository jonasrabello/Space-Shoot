#include <iostream>
#include <Engine.h>
#include "MainScene.h"
#include "SDL.h"

using namespace core;

int main(int argc, char* args[]) {

	Engine e(new MainScene());

	if (e.Init()) {
		std::cout << "Engine cannot initialize" << std::endl;
	}

	return 0;
}