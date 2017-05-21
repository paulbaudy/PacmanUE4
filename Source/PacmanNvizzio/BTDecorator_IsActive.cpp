// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "BTDecorator_IsActive.h"



bool UBTDecorator_IsActive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AGhostController* _ghostController = Cast<AGhostController>(OwnerComp.GetAIOwner());

	if (_ghostController) {
		return _ghostController->GhostOwner->AIisActive();
	}
	return false;
}

