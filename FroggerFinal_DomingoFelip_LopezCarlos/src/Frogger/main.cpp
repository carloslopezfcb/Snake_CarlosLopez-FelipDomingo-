

#include "GameEngine.hh"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 1000

int main(int argc, char* args[]) {
	GameEngine::Run<SCREEN_WIDTH, SCREEN_HEIGHT>("Frogger");
	return 0;
}