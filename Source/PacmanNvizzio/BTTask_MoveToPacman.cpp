// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "BTTask_MoveToPacman.h"




EBTNodeResult::Type UBTTask_MoveToPacman::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AGhostController* _ghostController = Cast<AGhostController>(OwnerComp.GetAIOwner());

	APacmanPawn* _pacman = Cast<APacmanPawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(_ghostController->PacmanID));
	FVector _destination = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(_ghostController->DestinationID);

	//GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Red, _destination.ToString());

	if (_pacman) {
		//GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Red, _pacman->getCurrentDirection().ToString());

		//FVector QueryingExtent = FVector(500.0f, 500.0f, 250.0f);
		//FNavLocation NavLoc;

		//UNavigationSystem::GetNavigationSystem(GetWorld())->ProjectPointToNavigation(_ghostController->GhostOwner->getPacmanOffset(_pacman->GetActorLocation()), NavLoc, QueryingExtent);
		/*UNavigationQueryFilter fQuery;
		FNavigationFilterArea testf;
		
		fQuery.Areas.Add
		UNavigationPath * path = UNavigationSystem::GetNavigationSystem(GetWorld())->FindPathToLocationSynchronously(GetWorld(), _ghostController->GhostOwner->GetActorLocation(), _pacman->GetActorLocation());
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::SanitizeFloat(path->GetPathCost()));
		

		if (path != NULL) {
			for (int pointiter = 0; pointiter < path->PathPoints.Num(); pointiter++)
			{
				DrawDebugSphere(GetWorld(), path->PathPoints[pointiter], 10.0f, 12, FColor(255, 0, 0));
			}
		}*/
		
		FVector dest = _ghostController->GhostOwner->getPacmanOffset(_pacman->GetActorLocation(), _pacman->getCurrentDirection());
		

		if (!_ghostController->MoveToLocation(dest, -1.f, true, true, false, true, _ghostController->GhostOwner->testquery)) {
			//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, "Fail");
			FVector QueryingExtent = FVector(FMath::Abs(_pacman->GetActorLocation().X - dest.X), FMath::Abs(_pacman->GetActorLocation().Y - dest.Y), 250.0f);
			FNavLocation NavLoc;
			//GEngine->AddOnScreenDebugMessage(-1, 0.03f, FColor::Red, _pacman->GetName());
			UNavigationSystem::GetNavigationSystem(GetWorld())->ProjectPointToNavigation(_ghostController->GhostOwner->getPacmanOffset(_pacman->GetActorLocation(), _pacman->getCurrentDirection()), NavLoc, QueryingExtent);
			_ghostController->MoveToLocation(NavLoc.Location, -1.f, true, true, false, true, _ghostController->GhostOwner->testquery);

		}


		//_ghostController->MoveToLocation(NavLoc.Location);

		//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, NavLoc.Location.ToString());
		return EBTNodeResult::Succeeded;
	}
	else {
		return EBTNodeResult::Failed;
	}
}