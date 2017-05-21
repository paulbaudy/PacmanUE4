// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "GameManagerActor.h"


// Sets default values
AGameManagerActor::AGameManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGameManagerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGameManagerActor::triggerFrightenedMode() {
	if (!pFrightenedFlipbook) return;

	for (AGhostCharacter* _ghost : aGhostCharacters) {
		_ghost->triggerFrightenedMode(pFrightenedFlipbook);
	}
}

void AGameManagerActor::RespawnCharacters() {
	for (AGhostCharacter* _ghost : aGhostCharacters) {
		_ghost->RespawnGhost(); // TODO reset frighten
	}
}

void AGameManagerActor::increaseDotNumber()
{
	iDotNumber++;
	if (iDotNumber >= 130) { // TODO variables
		if (aOrangeGhost && !aOrangeGhost->AIisActive()) {
			aOrangeGhost->setAIisActive(true);
		}
	}
	if (iDotNumber >= 30) {
		if (aBlueGhost && !aBlueGhost->AIisActive()) {
			aBlueGhost->setAIisActive(true);
		}
	}
}

