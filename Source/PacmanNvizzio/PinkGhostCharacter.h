// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "GhostCharacter.h"
#include "PinkGhostCharacter.generated.h"

/**
*  Custom pink ghost character. Will try to go to pacman's direction
*/
UCLASS()
class PACMANNVIZZIO_API APinkGhostCharacter : public AGhostCharacter
{
	GENERATED_BODY()

	APinkGhostCharacter();

	virtual FVector getPacmanOffset(FVector pacmanLocation, FVector pacmanDirection);
	
	const float pinkOffset = 8.f;
};
