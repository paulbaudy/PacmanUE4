// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "GhostCharacter.h"
#include "GhostController.h"
#include "BTDecorator_Chasing.generated.h"

/**
 * 
 */
UCLASS()
class PACMANNVIZZIO_API UBTDecorator_Chasing : public UBTDecorator
{
	GENERATED_BODY()
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
