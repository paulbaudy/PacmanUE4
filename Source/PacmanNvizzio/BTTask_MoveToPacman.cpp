// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "BTTask_MoveToPacman.h"

/* Task definition */
EBTNodeResult::Type UBTTask_MoveToPacman::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AGhostController* _ghostController = Cast<AGhostController>(OwnerComp.GetAIOwner());

	APacmanPawn* _pacman = Cast<APacmanPawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(_ghostController->PacmanID));
	FVector _destination = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(_ghostController->DestinationID);

	// If pacman is correctly detected...
	if (_pacman) {
		
		// Apply custom ghost offset, which is unique to each ghost. 
		FVector dest = _ghostController->GhostOwner->getPacmanOffset(_pacman->GetActorLocation(), _pacman->getCurrentDirection());
		
		// Try moving to our destination, with a filter that prevents him to turn around
		if (!_ghostController->MoveToLocation(dest, -1.f, true, true, false, true, _ghostController->GhostOwner->filterQuery)) {
			// If our destination is not in the current navmesh, try to find the nearest point on it

			FVector QueryingExtent = FVector(FMath::Abs(_pacman->GetActorLocation().X - dest.X), FMath::Abs(_pacman->GetActorLocation().Y - dest.Y), 250.0f);
			FNavLocation NavLoc;

			UNavigationSystem::GetNavigationSystem(GetWorld())->ProjectPointToNavigation(_ghostController->GhostOwner->getPacmanOffset(_pacman->GetActorLocation(), _pacman->getCurrentDirection()), NavLoc, QueryingExtent);
			_ghostController->MoveToLocation(NavLoc.Location, -1.f, true, true, false, true, _ghostController->GhostOwner->filterQuery);

		}

		return EBTNodeResult::Succeeded;
	}
	else {
		return EBTNodeResult::Failed;
	}
}