// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "OrangeGhostCharacter.h"


AOrangeGhostCharacter::AOrangeGhostCharacter() : AGhostCharacter()
{
	bActive = false;
}

FVector AOrangeGhostCharacter::getPacmanOffset(FVector pacmanLocation, FVector pacmanDirection) {
	FVector vecToPac = pacmanLocation - GetActorLocation();

	if (FVector::DistSquared(pacmanLocation, GetActorLocation()) < (OrangeOffset * TILESIZE)*(OrangeOffset * TILESIZE)) {
		return vCurrentScatterLocation;
	}

	return pacmanLocation;
}