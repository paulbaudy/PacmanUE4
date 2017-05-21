// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "BlueGhostCharacter.h"


ABlueGhostCharacter::ABlueGhostCharacter() : AGhostCharacter()
{
	bActive = false;
}

FVector ABlueGhostCharacter::getPacmanOffset(FVector pacmanLocation, FVector pacmanDirection)
{
	if (RedGhost) {
		//DrawDebugLine(GetWorld(), RedGhost->GetActorLocation(), (pacmanLocation - RedGhost->GetActorLocation()) * 2 + RedGhost->GetActorLocation(), FColor::Blue, false, -1, 0, 10);
		return (pacmanLocation - RedGhost->GetActorLocation()) * 2 + RedGhost->GetActorLocation();
	}

	return pacmanLocation;
}
