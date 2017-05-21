// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "TileDecision.h"


// Sets default values
ATileDecision::ATileDecision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	BoxCollider->SetBoxExtent(FVector(5.f, 5.f, 5.f)); // TODO constantes
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ATileDecision::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ATileDecision::OnOverlapEnd);
	BoxCollider->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATileDecision::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATileDecision::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		AGhostCharacter* _ghost = Cast<AGhostCharacter>(OtherActor);
		if (_ghost) {
			_ghost->triggerDynamicObstacle(true);
		}
	}
}

void ATileDecision::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		AGhostCharacter* _ghost = Cast<AGhostCharacter>(OtherActor);
		if (_ghost) {
			_ghost->triggerDynamicObstacle(true);
		}
	}
}

