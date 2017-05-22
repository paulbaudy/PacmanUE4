// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "GhostCharacter.h"
#include "GhostController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Scatter.generated.h"

/**
*  Custom Behavior Tree task. If ghost is currently in scatter mode,
*  it will move to its current scatter destination
*/
UCLASS()
class PACMANNVIZZIO_API UBTTask_Scatter : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
