// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "GhostCharacter.h"
#include "GhostController.h"
#include "BTDecorator_IsDeciding.generated.h"

/**
 * 
 */
UCLASS()
class PACMANNVIZZIO_API UBTDecorator_IsDeciding : public UBTDecorator
{
	GENERATED_BODY()
	
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	
};
