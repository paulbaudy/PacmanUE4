// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GhostCharacter.h"
#include "GhostController.generated.h"

/**
 * 
 */
UCLASS()
class PACMANNVIZZIO_API AGhostController : public AAIController
{
	GENERATED_BODY()
	
	/* --- AI COMPONENTS --- */

	// Custom Blackboard
	UPROPERTY(transient)
	UBlackboardComponent* ghostBlackboard;

	// Custom AI Behavior Tree
	UPROPERTY(transient)
	UBehaviorTreeComponent* ghostBehaviorTree;

public:
	AGhostController();

	virtual void Possess(APawn* InPawn) override;

	// Pacman Key
	uint8 PacmanID;

	// Destination ID
	uint8 DestinationID;

	// Ghost owned by this AI Controller
	AGhostCharacter* GhostOwner;

	bool firstCheck;
};
