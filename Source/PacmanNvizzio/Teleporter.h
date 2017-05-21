// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "PacmanPawn.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

UCLASS()
class PACMANNVIZZIO_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();

protected:

	/* --- COMPONENTS --- */
	UPROPERTY(VisibleAnywhere, Category = Root)
	UBoxComponent* Root;


	UPROPERTY(VisibleAnywhere, Category = Root)
	USceneComponent* Destination;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
