// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "BTDecorator_IsDeciding.h"




bool UBTDecorator_IsDeciding::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AGhostController* _ghostController = Cast<AGhostController>(OwnerComp.GetAIOwner());

	if (_ghostController) {
		return _ghostController->GhostOwner->isDynamicObstacle();
	}
	return false;
}
