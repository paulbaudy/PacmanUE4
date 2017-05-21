// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "dotActor.h"

// Sets default values
AdotActor::AdotActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bBonus = false;

	BoxComponent = CreateAbstractDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AdotActor::OnOverlapBegin);
	RootComponent = BoxComponent;

	spriteComponent = CreateAbstractDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	spriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	spriteComponent->SetupAttachment(BoxComponent);

}

void AdotActor::setSprite(UPaperSprite* dotSprite)
{
	spriteComponent->SetSprite(dotSprite);
	spriteComponent->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	BoxComponent->SetBoxExtent(FVector(dotSprite->GetSourceSize().X, dotSprite->GetSourceSize().Y, 1.f));

}

// Checks collisions during placement in the editor
bool AdotActor::isOverlapingMap()
{
	// ComponentOverlapActors needs to know what channel to use for collision detection
	TArray<TEnumAsByte<EObjectTypeQuery> > arrayObjectTypeQuery;
	arrayObjectTypeQuery.Add(EObjectTypeQuery::ObjectTypeQuery1); // World Dynamic
	arrayObjectTypeQuery.Add(EObjectTypeQuery::ObjectTypeQuery2); // Pawn

	// Better ignore this actor
	TArray<AActor*> arrayIgnoreList;
	arrayIgnoreList.Add(this);

	// arrayOutput contains colliding actors
	TArray<AActor*> arrayOutput;
	UKismetSystemLibrary::ComponentOverlapActors(BoxComponent, GetActorTransform(), arrayObjectTypeQuery, APaperSpriteActor::StaticClass(), arrayIgnoreList, arrayOutput);
	
	
	return arrayOutput.Num() > 0;
}

void AdotActor::OnConstruction(const FTransform& Transform) {
	if (bBonus) {
		spriteComponent->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	}
	else {
		spriteComponent->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	}
}

// Called when the game starts or when spawned
void AdotActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AdotActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		APacmanPawn * _pacman = Cast<APacmanPawn>(OtherActor);
		if (_pacman) {
			_pacman->EatDot(bBonus);
			Destroy();
		}
	}
}
