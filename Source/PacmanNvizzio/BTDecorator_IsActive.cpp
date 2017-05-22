// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "BTDecorator_IsActive.h"


/* Decorator's condition */
bool UBTDecorator_IsActive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AGhostController* _ghostController = Cast<AGhostController>(OwnerComp.GetAIOwner());

	// If AI Controller is valid, returns ghost's current active state
	if (_ghostController) {
		return _ghostController->GhostOwner->AIisActive();
	}
	return false;
}

