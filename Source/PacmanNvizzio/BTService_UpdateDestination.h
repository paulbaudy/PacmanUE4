// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "PacmanPawn.h"
#include "GhostController.h"
#include "GhostCharacter.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateDestination.generated.h"

/**
 * 
 */
UCLASS()
class PACMANNVIZZIO_API UBTService_UpdateDestination : public UBTService
{
	GENERATED_BODY()

	UBTService_UpdateDestination();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
