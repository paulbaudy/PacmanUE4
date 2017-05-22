// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "GhostController.h"


AGhostController::AGhostController() {
	ghostBlackboard = CreateAbstractDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	ghostBehaviorTree = CreateAbstractDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
}

void AGhostController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AGhostCharacter* newGhost = Cast<AGhostCharacter>(InPawn);

	if (newGhost && newGhost->getBehavior()) {
		// Initialize blackboard and behavior tree
		ghostBlackboard->InitializeBlackboard(*newGhost->getBehavior()->BlackboardAsset);

		PacmanID = ghostBlackboard->GetKeyID("Pacman");
		DestinationID = ghostBlackboard->GetKeyID("Destination");
		GhostOwner = newGhost;

		ghostBehaviorTree->StartTree(*newGhost->getBehavior());
		newGhost->StartBehavior();
	}
	

}