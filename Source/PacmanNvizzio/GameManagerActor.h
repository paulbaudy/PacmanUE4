// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "LifeSprite.h"
#include "PaperSpriteActor.h"
#include "GhostController.h"
#include "PaperFlipbook.h"
#include "GhostCharacter.h"
#include "GameFramework/Actor.h"
#include "GameManagerActor.generated.h"

UCLASS()
class PACMANNVIZZIO_API AGameManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManagerActor();

	void triggerFrightenedMode();

	void RespawnCharacters();

	void increaseDotNumber();

	void initializeLivesUI(unsigned int lives);
	void decreaseLives();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	/* --- COMPONENTS --- */

	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Manager)
	TArray<AGhostCharacter*> aGhostCharacters;

	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	AGhostCharacter* aBlueGhost;

	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	AGhostCharacter* aOrangeGhost;

	// Ghost frightened flipbook
	UPROPERTY(EditAnywhere, Category = Sprite)
	UPaperFlipbook* pFrightenedFlipbook;

	UPROPERTY(EditAnywhere, Category = Sprite)
	ATargetPoint* livesSpritesTarget;

	UPROPERTY(EditAnywhere, Category = Sprite)
	UPaperSprite* lifeSprite;

	TArray<ALifeSprite*> lifeSpriteArray;

	unsigned int iDotNumber;
	unsigned int livesLeft;
	
};
