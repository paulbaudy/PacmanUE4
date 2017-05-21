// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "GhostCharacter.h"
#include "GameFramework/Actor.h"
#include "TileDecision.generated.h"

UCLASS()
class PACMANNVIZZIO_API ATileDecision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileDecision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* --- COMPONENTS --- */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Root)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Root)
	UBoxComponent* BoxCollider;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
