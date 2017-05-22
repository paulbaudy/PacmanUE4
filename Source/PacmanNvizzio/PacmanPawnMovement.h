// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "TileGrid.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PacmanPawnMovement.generated.h"

/**
 * 
 */
UCLASS()
class PACMANNVIZZIO_API UPacmanPawnMovement : public UFloatingPawnMovement
{
	GENERATED_BODY()

	
	UPacmanPawnMovement();


private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	void GoToCurrentDirection(float DeltaTime);

	// Pacman's current velocity
	FVector currentDirection;

	// Pacman's maximum velocity
	float maxVelocity;

	
public:
	FVector getCurrentDirection();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
	ATileGrid* tileGrid;
};
