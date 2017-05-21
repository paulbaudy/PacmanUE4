// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "GhostCharacter.h"
#include "BlueGhostCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PACMANNVIZZIO_API ABlueGhostCharacter : public AGhostCharacter
{
	GENERATED_BODY()

	ABlueGhostCharacter();

	/* --- COMPONENTS --- */
	// Red ghost reference to use its position
	UPROPERTY(EditAnywhere, Category = AI)
	AGhostCharacter* RedGhost;
	
	virtual FVector getPacmanOffset(FVector pacmanLocation, FVector pacmanDirection);
};
