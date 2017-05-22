// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "dotGridActor.h"


// Sets default values
AdotGridActor::AdotGridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create root component
	Root = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Root->SetMobility(EComponentMobility::Movable);
	RootComponent = Root;

}

// Construction script
void AdotGridActor::OnConstruction(const FTransform& Transform)
{
	// Delete all children
	TArray<AActor*> temp;
	GetAttachedActors(temp);

	for (AActor* CActor : temp)
	{
		CActor->Destroy();
	}

	if (!dotSprite) // If dot sprite is not set, safely return
		return;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.bNoFail = false;

	// Spawn dot grid
	for (int i = 0; i < numberX; i++) {
		for (int j = 0; j < numberY; j++) {
			
			FVector _location = GetActorLocation();
			_location.X += i * dotDistance;
			_location.Y += j * dotDistance;
			AdotActor* newDot = GetWorld()->SpawnActor<AdotActor>(_location, GetActorRotation(), SpawnInfo);
			newDot->setSprite(dotSprite);

			// If new dot is not colliding with the map...
			if (!newDot->isOverlapingMap()) {
				newDot->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				if (bonusPoints.Contains(FIntVector(i, j, 0))) {
					newDot->setIsBonus(true);
				}
			}
			else
				newDot->Destroy();

		}
	}
}

void AdotGridActor::addBonusPoint(FIntVector bonus) {
	bonusPoints.Add(bonus);
}

// Called when the game starts or when spawned
void AdotGridActor::BeginPlay()
{
	Super::BeginPlay();
	
}
