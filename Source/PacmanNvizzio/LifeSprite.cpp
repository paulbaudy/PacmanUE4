// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "LifeSprite.h"


// Sets default values
ALifeSprite::ALifeSprite()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Root"));

	spriteComponent = CreateAbstractDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	spriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	spriteComponent->SetupAttachment(Root);
}


void ALifeSprite::setSprite(UPaperSprite* lifeSprite) {
	spriteComponent->SetSprite(lifeSprite);
}