// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "LifeSprite.h"
#include "PaperSpriteActor.h"
#include "GhostController.h"
#include "PaperFlipbook.h"
#include "GhostCharacter.h"
#include "GameFramework/Actor.h"
#include "GameManagerActor.generated.h"

/**
*  Game manager. Handles AI start, frighten mode and lives UI
*/
UCLASS()
class PACMANNVIZZIO_API AGameManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManagerActor();

	void triggerFrightenedMode();

	// Respawn all ghosts in starting box
	void RespawnCharacters();

	// Increase number of eaten dots
	void increaseDotNumber();

	// Initialize number of lives sprites on UI
	void initializeLivesUI(unsigned int lives);

	// Update UI
	void decreaseLives();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	/* --- COMPONENTS --- */

	// Array of ghosts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Manager)
	TArray<AGhostCharacter*> aGhostCharacters;

	// Custom point for AI start
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	AGhostCharacter* aBlueGhost;

	// Custom point for AI start
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	AGhostCharacter* aOrangeGhost;

	// Ghost frightened flipbook
	UPROPERTY(EditAnywhere, Category = Sprite)
	UPaperFlipbook* pFrightenedFlipbook;

	// Life sprite location
	UPROPERTY(EditAnywhere, Category = Sprite)
	ATargetPoint* livesSpritesTarget;

	// Life custom sprite
	UPROPERTY(EditAnywhere, Category = Sprite)
	UPaperSprite* lifeSprite;

	TArray<ALifeSprite*> lifeSpriteArray;

	unsigned int iDotNumber;
	unsigned int livesLeft;
	
	const unsigned int dotToEatOrange = 130;
	const unsigned int dotToEatBlue = 30;
	const unsigned int UILivesOffset = 50;
};
