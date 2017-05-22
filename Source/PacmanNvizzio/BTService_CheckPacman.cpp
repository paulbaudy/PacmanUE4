// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "BTService_CheckPacman.h"


UBTService_CheckPacman::UBTService_CheckPacman() {
	bCreateNodeInstance = true;
}

/* Service's tick */
void UBTService_CheckPacman::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AGhostController* _ghostController = Cast<AGhostController>(OwnerComp.GetAIOwner());

	// If AI Controller is valid...
	if (_ghostController) {
		APacmanPawn *_pacman = Cast<APacmanPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

		// if a Pacman pawn is controlled by the player, update object in behavior tree. 
		if (_pacman) {
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(_ghostController->PacmanID, _pacman);
		}
	}
}

