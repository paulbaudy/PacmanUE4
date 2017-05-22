// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "dotGridActor.h"
#include "PaperSpriteActor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "PacmanPawn.h"
#include "GameFramework/Actor.h"
#include "dotActor.generated.h"

UCLASS()
class PACMANNVIZZIO_API AdotActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AdotActor();

	// Updates dot's sprite & collision box
	void setSprite(UPaperSprite* dotSprite);

	// Checks collisions during placement in the editor
	bool isOverlapingMap();

	void setIsBonus(bool bonus);

protected:
	/* Custom construction script.
	*/
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* --- COMPONENTS --- */

	// Custom root component which is a box collider
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Root)
	UBoxComponent* BoxComponent;

	// Dot's sprite
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperSpriteComponent* spriteComponent;

	// If this dot is a power-up for pacman. Can be set in editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	bool bBonus;

public:	
	// Overlap function called when colliding with other actors
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
