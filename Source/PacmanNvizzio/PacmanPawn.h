// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "GhostCharacter.h"
#include "GameManagerActor.h"
#include "PacmanWidget.h"
#include "Blueprint/UserWidget.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PacmanPawnMovement.h"
#include "dotActor.h"

#include "GameFramework/Pawn.h"
#include "PacmanPawn.generated.h"

UCLASS()
class PACMANNVIZZIO_API APacmanPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APacmanPawn();

	// Override GetMovementComponent to return our custom Movement Component
	virtual UPawnMovementComponent* GetMovementComponent() const override;

protected:
	/* --- COMPONENTS --- */

	// Custom root component which is a box collider
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn)
	UBoxComponent* BoxComponent;

	// Custom orthographic camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	ACameraActor* DefaultCamera;

	// Custom Pawn movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn)
	UPacmanPawnMovement* PawnMovement;

	// Pacman's sprite animation
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbookComponent* currentSprite;

	/* --- animation sprites --- */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* UpSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* LeftSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* DownSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UPaperFlipbook* RightSprite;

	// Game manager instance to update game state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Manager)
	AGameManagerActor* aGameManager;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Box and sprite overlap callbacks */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapBeginSprite(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Respawn player when dead
	void RespawnPlayer();

	// Reset short vulnerable time when eating a ghost
	void ResetVulnerable();

	// Vulnerable time when eating a ghost
	FTimerHandle vulnerableTimer;

	// Last direction for animation update
	FVector lastDirection;

	// Initial location for respawning
	FVector initianSpawnLocation;


	// Remaining dots to eat in order to win
	unsigned int dotToEat;

	// Remaining lives
	unsigned int livesLeft;

	bool bVulnerable;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when eating a dot
	void EatDot(bool isBonus);

	FVector getCurrentDirection();

private:
	void UpdateAnimation();

	// Player input functions
	void MoveRight(float rate);
	void MoveUp(float rate);
};
