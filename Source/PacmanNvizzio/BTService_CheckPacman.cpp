// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "BTService_CheckPacman.h"


UBTService_CheckPacman::UBTService_CheckPacman() {
	bCreateNodeInstance = true;
}

void UBTService_CheckPacman::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AGhostController* _ghostController = Cast<AGhostController>(OwnerComp.GetAIOwner());
	AGhostCharacter* _ownedGhost = Cast<AGhostCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (_ghostController && _ownedGhost) {
		APacmanPawn *_pacman = Cast<APacmanPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());


		if (_pacman) {
		
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(_ghostController->PacmanID, _pacman);
		}
	}
}

