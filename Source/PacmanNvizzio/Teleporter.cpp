// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "Teleporter.h"


// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Root->SetBoxExtent(FVector(2.f, 2.f, 2.f));
	Root->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);
	RootComponent = Root;

	Destination = CreateDefaultSubobject<USceneComponent>(TEXT("Destination"));
	Destination->SetupAttachment(RootComponent);
}

void ATeleporter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		APacmanPawn * _pacman = Cast<APacmanPawn>(OtherActor);
		if (_pacman) {
			_pacman->SetActorLocation(Destination->GetComponentLocation());
		}
	}
}

