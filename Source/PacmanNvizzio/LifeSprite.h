// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "LifeSprite.generated.h"

UCLASS()
class PACMANNVIZZIO_API ALifeSprite : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALifeSprite();

	void setSprite(UPaperSprite* lifeSprite);

protected:

	/* --- COMPONENTS --- */

	USceneComponent* Root;


	UPaperSpriteComponent* spriteComponent;
};
