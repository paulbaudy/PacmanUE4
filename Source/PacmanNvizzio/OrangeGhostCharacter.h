// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "GhostCharacter.h"
#include "OrangeGhostCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PACMANNVIZZIO_API AOrangeGhostCharacter : public AGhostCharacter
{
	GENERATED_BODY()

	AOrangeGhostCharacter();
	
	virtual FVector getPacmanOffset(FVector pacmanLocation, FVector pacmanDirection);
	
};
