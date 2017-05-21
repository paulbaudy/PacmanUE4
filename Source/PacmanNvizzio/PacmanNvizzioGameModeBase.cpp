// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "PacmanNvizzioGameModeBase.h"

APacmanNvizzioGameModeBase::APacmanNvizzioGameModeBase() {
	// Set default pawn class to our Pacman pawn
	DefaultPawnClass = APacmanPawn::StaticClass();
}
