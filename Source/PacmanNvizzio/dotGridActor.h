// Paul BAUDY for Nvizzio Creations Inc

#pragma once


#include "dotActor.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "dotGridActor.generated.h"

UCLASS()
class PACMANNVIZZIO_API AdotGridActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AdotGridActor();

	void addBonusPoint(FIntVector bonus);

protected:
	/* Custom construction script. 
	*  Will be called when the grid is place in the editor, in order to spawn dots 
	*  according to our properties
	*/ 
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* --- COMPONENTS --- */
	// Custom root component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Root)
	USceneComponent* Root;

	// Sprite used by dots
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sprite)
	UPaperSprite* dotSprite;

	

	/* --- Grid properties --- */
	// Distance between two dots - Tile size
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid)
	int dotDistance;

	// Number of dots in X direction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid)
	int numberX;

	// Number of dots in Y direction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid)
	int numberY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid)
	TArray<FIntVector> bonusPoints;
	
};
