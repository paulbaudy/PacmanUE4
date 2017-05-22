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
#include "BTService_CheckPacman.generated.h"

/**
*  Custom Behavior Tree Service. Called in order to detect Pacman's position
*  and update it in behavior tree. 
*/
UCLASS()
class PACMANNVIZZIO_API UBTService_CheckPacman : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_CheckPacman();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
