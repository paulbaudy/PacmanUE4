// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "BTDecorator_Chasing.h"

/* Decorator's condition */
bool UBTDecorator_Chasing::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AGhostController* _ghostController = Cast<AGhostController>(OwnerComp.GetAIOwner());

	// If AI Controller is valid, returns ghost's current chasing state
	if (_ghostController) {
		return _ghostController->GhostOwner->isChasing();
	}
	return false;
}
