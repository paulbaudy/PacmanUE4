// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "BTTask_Scatter.h"




EBTNodeResult::Type UBTTask_Scatter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AGhostController* _ghostController = Cast<AGhostController>(OwnerComp.GetAIOwner());

	
	if (_ghostController) {
		_ghostController->MoveToLocation(_ghostController->GhostOwner->getCurrentScatterLocation(), -1, true, true, false, true, _ghostController->GhostOwner->testquery);

		/* if (FVector::DistSquared(_ghostController->GhostOwner->GetActorLocation(), _ghostController->GhostOwner->currentScatterDestination) < 10.f) {
			_ghostController->GhostOwner->UpdateScatterDestination();
		}*/


		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}