// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "GhostCharacter.h"




AGhostCharacter::AGhostCharacter() : APaperCharacter() ,
	iChasesNumber(4), 
	fChaseDuration(20.f),
	fScatterDuration(6.f),
	fFrightenedDuration(10.f),
	bChasing(false),
	bFrightened(false),
	bActive(true)
{

	GetCapsuleComponent()->SetCapsuleRadius(capsuleRadius); 
	GetCapsuleComponent()->SetCapsuleHalfHeight(capsuleRadius);

	testbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Test"));
	testbox->SetBoxExtent(FVector(5.f, 30.f, 5.f));
	testbox->SetupAttachment(RootComponent);
	testbox->bDynamicObstacle = true;

	GetSprite()->bAbsoluteRotation = true;
}

void AGhostCharacter::TriggerChaseMode()
{
	iChasesNumber--;
	bChasing = true;
	if (iChasesNumber > 0)
		GetWorld()->GetTimerManager().SetTimer(chaseTimer, this, &AGhostCharacter::TriggerScatteringMode, fChaseDuration, false);
}

void AGhostCharacter::TriggerScatteringMode()
{
	testbox->bDynamicObstacle = true;
	bChasing = false;
	GetWorld()->GetTimerManager().SetTimer(chaseTimer, this, &AGhostCharacter::TriggerChaseMode, fScatterDuration, false);
}

void AGhostCharacter::StartBehavior() {
	// Initialize scatter locations
	if (ScatterLocation) {
		vCurrentScatterLocation = ScatterLocation->GetActorLocation();
		ScatterLocation->GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &AGhostCharacter::OnOverlapBegin1);
	}
	if (ScatterLocation2) {
		ScatterLocation2->GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &AGhostCharacter::OnOverlapBegin2);
	}

	testbox->bDynamicObstacle = true;
	initianSpawnLocation = GetActorLocation();

	GetWorld()->GetTimerManager().SetTimer(chaseTimer, this, &AGhostCharacter::TriggerChaseMode, fScatterDuration, false);
}

void AGhostCharacter::RespawnGhost() {
	SetActorLocation(initianSpawnLocation);
}

void AGhostCharacter::triggerDynamicObstacle(bool bObstacle)
{
	// testbox->bDynamicObstacle = bObstacle;
}

bool AGhostCharacter::isDynamicObstacle()
{
	return testbox->bDynamicObstacle;
}

bool AGhostCharacter::isChasing() {
	return bChasing && !bFrightened;
}

bool AGhostCharacter::isFrightened() {
	return bFrightened;
}

bool AGhostCharacter::AIisActive()
{
	return bActive;
}

void AGhostCharacter::setAIisActive(bool isActive)
{
	bActive = isActive;
}

void AGhostCharacter::triggerFrightenedMode(UPaperFlipbook* fFrightenedFlipbook)
{
	if (!bFrightened) {
		// Pause scatter/chase timer
		GetWorld()->GetTimerManager().PauseTimer(chaseTimer);

		bFrightened = true;
		// Backup current flipbook
		pBackupFlipbook = GetSprite()->GetFlipbook();

		// Set new flipbook for frightened mode
		GetSprite()->SetFlipbook(fFrightenedFlipbook);
	}

	GetWorld()->GetTimerManager().SetTimer(frightenedTimer, this, &AGhostCharacter::EndFrightenedMode, fFrightenedDuration, false);
}

void AGhostCharacter::EndFrightenedMode() {
	// Returns to current mode
	GetWorld()->GetTimerManager().UnPauseTimer(chaseTimer);
	if (bFrightened) {
		bFrightened = false;

		GetSprite()->SetFlipbook(pBackupFlipbook);
	}
}

UBehaviorTree* AGhostCharacter::getBehavior() {
	return behavior;
}

FVector AGhostCharacter::getCurrentScatterLocation() {
	return vCurrentScatterLocation;
}

FVector AGhostCharacter::getPacmanOffset(FVector pacmanLocation, FVector pacmanDirection)
{
	return pacmanLocation; // Returns the same location by default (Red behavior)
}

void AGhostCharacter::OnOverlapBegin1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor == this) && (OtherComp != nullptr)) {
		if(ScatterLocation2)
			vCurrentScatterLocation = ScatterLocation2->GetActorLocation();
	}
}

void AGhostCharacter::OnOverlapBegin2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor == this) && (OtherComp != nullptr)) {
		if(ScatterLocation)
			vCurrentScatterLocation = ScatterLocation->GetActorLocation();
	}
}
