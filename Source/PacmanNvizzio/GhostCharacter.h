// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "Runtime/Engine/Classes/AI/Navigation/NavFilters/NavigationQueryFilter.h"
#include "Runtime/Engine/Classes/Engine/TriggerBox.h"
#include "BehaviorTree/BehaviorTree.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "TileGrid.h"
#include "GhostCharacter.generated.h"


/**
 *  Ghost character actor. 
 */
UCLASS()
class PACMANNVIZZIO_API AGhostCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
	
protected:
	AGhostCharacter();

	// Trigger chase or scatter mode
	void TriggerChaseMode();
	void TriggerScatteringMode();
	

	/* --- Properties --- */
	// Timer to trigger chase/scatter mode
	FTimerHandle chaseTimer;

	// Timer to trigger frightened mode
	FTimerHandle frightenedTimer;

	// Total number of chases
	unsigned int iChasesNumber;

	// Duration of chase mode 
	float fChaseDuration;

	// Duration of scatter mode
	float fScatterDuration;

	// Duration of frightened mode
	float fFrightenedDuration;

	// Is in chase mod or not
	bool bChasing;

	// Is frightened or not
	bool bFrightened;

	// AI is active or not
	bool bActive;

	FVector initianSpawnLocation;
	FVector vCurrentScatterLocation;

	const float capsuleRadius = 13.f;

	/* --- COMPONENTS --- */
	
	// AI Behavior Tree
	UPROPERTY(EditAnywhere, Category = AI)
	UBehaviorTree* behavior;
	// First scatter destination
	UPROPERTY(EditAnywhere, Category = AI)
	ATriggerBox* ScatterLocation;
	// Second scatter destination
	UPROPERTY(EditAnywhere, Category = AI)
	ATriggerBox* ScatterLocation2;
	UPROPERTY(EditAnywhere, Category = AI)
	ATileGrid* aGridSystem;
	// Ghost flipbook backed up for frightened mode
	UPROPERTY(VisibleAnywhere, Category = Sprite)
	UPaperFlipbook* pBackupFlipbook;

	// Box obstacle behind our ghost for navigation system
	UPROPERTY(EditAnywhere, Category = AI)
	UBoxComponent* testbox;

	

public:
	// Start behavior tree AI
	void StartBehavior();

	void RespawnGhost();
	void EndFrightenedMode();

	void triggerDynamicObstacle(bool bObstacle);
	bool isDynamicObstacle();

	// bChasing getter
	bool isChasing();

	// bFrightened getter;
	bool isFrightened();

	bool AIisActive();
	void setAIisActive(bool isActive);

	void triggerFrightenedMode(UPaperFlipbook* fFrightenedFlipbook);

	// Behavior Tree getter
	UBehaviorTree* getBehavior();

	// Returns next scatter location
	FVector getCurrentScatterLocation();

	// Virtual function that defines where to go according to pacman's location and direction
	// Must be defined for every ghosts
	virtual FVector getPacmanOffset(FVector pacmanLocation, FVector pacmanDirection);

	// Overlap function called when colliding with scatter locations
	UFUNCTION()
	void OnOverlapBegin1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapBegin2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// box obstacle filter for navigation system
	UPROPERTY(EditAnywhere, Category = AI)
	TSubclassOf<UNavigationQueryFilter> filterQuery;
};
