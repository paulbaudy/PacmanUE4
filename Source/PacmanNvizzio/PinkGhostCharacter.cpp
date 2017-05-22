// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "PinkGhostCharacter.h"

APinkGhostCharacter::APinkGhostCharacter() : AGhostCharacter()
{

}


FVector APinkGhostCharacter::getPacmanOffset(FVector pacmanLocation, FVector pacmanDirection) {
	return pacmanLocation + pacmanDirection*pinkOffset*TILESIZE;
}