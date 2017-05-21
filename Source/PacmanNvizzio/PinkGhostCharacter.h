// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "GhostCharacter.h"
#include "PinkGhostCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PACMANNVIZZIO_API APinkGhostCharacter : public AGhostCharacter
{
	GENERATED_BODY()

	APinkGhostCharacter();

	virtual FVector getPacmanOffset(FVector pacmanLocation, FVector pacmanDirection);
	
};
