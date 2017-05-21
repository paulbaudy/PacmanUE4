// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "BTDecorator_Chasing.h"




bool UBTDecorator_Chasing::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AGhostController* _ghostController = Cast<AGhostController>(OwnerComp.GetAIOwner());

	if (_ghostController) {
		AGhostCharacter* _ghost = Cast<AGhostCharacter>(_ghostController->GetPawn());

		if (_ghost) {
			return _ghost->isChasing();
		}
	}
	return false;
}
