// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "TileGrid.generated.h"

UCLASS()
class PACMANNVIZZIO_API ATileGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	*  
	*  
	*/
	virtual void OnConstruction(const FTransform& Transform) override;


	/* --- COMPONENTS --- */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Root)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Visibility)
	UStaticMesh* mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Root)
	UInstancedStaticMeshComponent* mGridMeshs;

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
	bool bShowGrid;

	TArray<TArray<bool>> bGrid;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Check if entity can walk into a specific tile
	bool canWalk(unsigned int x, unsigned int y);
	bool canWalk(FVector location);
	FIntVector WorldToGrid(FVector location);
	int accessibleTiles(unsigned int x, unsigned int y);
	int accessibleTiles(FVector location);
	FIntVector SpeedWorldtoSpeedGrid(FVector velocity);

};
