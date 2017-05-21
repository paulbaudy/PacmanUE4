// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "BTService_UpdateDestination.h"

UBTService_UpdateDestination::UBTService_UpdateDestination() {
	bCreateNodeInstance = true;
}


void UBTService_UpdateDestination::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	AGhostController* _ghostController = Cast<AGhostController>(OwnerComp.GetAIOwner());

	if (_ghostController) {
		APacmanPawn *_pacman = Cast<APacmanPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (_pacman) {

			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(_ghostController->DestinationID, _pacman->GetActorLocation());
		}
	}
}
