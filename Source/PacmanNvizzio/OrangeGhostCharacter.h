// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "GhostCharacter.h"
#include "OrangeGhostCharacter.generated.h"

/**
*  Custom Orange ghost character. Will go to scatter point if too close to pacman's location
*/
UCLASS()
class PACMANNVIZZIO_API AOrangeGhostCharacter : public AGhostCharacter
{
	GENERATED_BODY()

	AOrangeGhostCharacter();
	
	virtual FVector getPacmanOffset(FVector pacmanLocation, FVector pacmanDirection);

	const int OrangeOffset = 10;
	
};
