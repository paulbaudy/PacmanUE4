// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "GhostCharacter.h"
#include "GhostController.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsActive.generated.h"

/**
 * 
 */
UCLASS()
class PACMANNVIZZIO_API UBTDecorator_IsActive : public UBTDecorator
{
	GENERATED_BODY()
	
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	
};
