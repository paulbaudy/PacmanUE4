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
		_ghost->RespawnGhost();
		_ghost->EndFrightenedMode();
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

void AGameManagerActor::initializeLivesUI(unsigned int lives)
{
	if (!livesSpritesTarget) return;

	FActorSpawnParameters SpawnInfo;

	for (unsigned int i = 0; i < lives; i++) {
		FVector _location = livesSpritesTarget->GetActorLocation();
		_location.X += 50 * i; // TODO constantes
		ALifeSprite* _life = GetWorld()->SpawnActor<ALifeSprite>(_location, livesSpritesTarget->GetActorRotation(), SpawnInfo);
		if (_life && lifeSprite) {
			_life->setSprite(lifeSprite);
		}
		lifeSpriteArray.Add(_life);
	}
	livesLeft = lives;
}

void AGameManagerActor::decreaseLives()
{
	lifeSpriteArray[livesLeft - 1]->Destroy();
	livesLeft--;
}

