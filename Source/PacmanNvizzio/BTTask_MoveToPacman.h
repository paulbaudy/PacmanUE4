// Paul BAUDY for Nvizzio Creations Inc

#pragma once
#include "AI/Navigation/NavigationPath.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GhostController.h"
#include "GhostCharacter.h"
#include "PacmanPawn.h"
#include "BTTask_MoveToPacman.generated.h"

/**
*  Custom Behavior Tree task. If ghost is currently chasing Pacman, it will
*  call the navigation system to find a path to it. 
*  Ghost will move to Pacman according to its own offset. 
*/
UCLASS()
class PACMANNVIZZIO_API UBTTask_MoveToPacman : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
