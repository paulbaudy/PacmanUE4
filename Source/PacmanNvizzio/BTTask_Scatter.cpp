// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "BTTask_Scatter.h"



/* Task definition */
EBTNodeResult::Type UBTTask_Scatter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AGhostController* _ghostController = Cast<AGhostController>(OwnerComp.GetAIOwner());

	// If AI Controller is valid, move to our current scatter destination
	if (_ghostController) {
		_ghostController->MoveToLocation(_ghostController->GhostOwner->getCurrentScatterLocation(), -1, true, true, false, true, _ghostController->GhostOwner->filterQuery);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}