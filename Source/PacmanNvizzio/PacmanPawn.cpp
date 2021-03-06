// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "PacmanPawn.h"


// Sets default values
APacmanPawn::APacmanPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create our box collider root component
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	BoxComponent->SetMobility(EComponentMobility::Movable);
	BoxComponent->SetBoxExtent(FVector(TILESIZE-1, TILESIZE-1, TILESIZE-1)); // If box is the size of TILESIZE, it will collide constantly
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APacmanPawn::OnOverlapBegin);
	RootComponent = BoxComponent;

	currentSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	currentSprite->SetupAttachment(BoxComponent);
	currentSprite->OnComponentBeginOverlap.AddDynamic(this, &APacmanPawn::OnOverlapBeginSprite);

	PawnMovement = CreateDefaultSubobject<UPacmanPawnMovement>(TEXT("MovementComponent"));
	// Lock character motion onto the XY plane, so the character can't move in or out of the screen
	PawnMovement->bConstrainToPlane = true;
	PawnMovement->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));
	PawnMovement->UpdatedComponent = RootComponent;

	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

UPawnMovementComponent* APacmanPawn::GetMovementComponent() const
{
	return PawnMovement;
}

// Called when the game starts or when spawned
void APacmanPawn::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTarget(DefaultCamera);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AdotActor::StaticClass(), FoundActors);

	dotToEat = FoundActors.Num();
	initianSpawnLocation = GetActorLocation();
	livesLeft = 4;
	bVulnerable = true;

	if (aGameManager) {
		aGameManager->initializeLivesUI(livesLeft);
	}
}

void APacmanPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		AGhostCharacter* _ghost = Cast<AGhostCharacter>(OtherActor);
		if (_ghost) {
			
			if (_ghost->isFrightened()) {
				_ghost->RespawnGhost();
				_ghost->EndFrightenedMode();
				bVulnerable = false;
				GetWorld()->GetTimerManager().SetTimer(vulnerableTimer, this, &APacmanPawn::ResetVulnerable, 0.5f, false); // TODO retirer, collision avec 2 composents du fantome en est la cause
			}
			else if(bVulnerable) {
				RespawnPlayer();
				aGameManager->RespawnCharacters();
			}
		}
	}
}

void APacmanPawn::OnOverlapBeginSprite(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		AdotActor* _dot = Cast<AdotActor>(OtherActor);
		if (_dot) {
			EatDot(_dot->getIsBonus());
			_dot->Destroy();
		}
	}
}

void APacmanPawn::RespawnPlayer() {
	SetActorLocation(initianSpawnLocation);
	livesLeft--;
	if (livesLeft == 0) {
		UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
	}
	if (aGameManager) {
		aGameManager->decreaseLives();
	}
}

void APacmanPawn::ResetVulnerable() {
	bVulnerable = true;
}

// Called every frame
void APacmanPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAnimation();
}

void APacmanPawn::EatDot(bool isBonus) {
	dotToEat--;

	if (dotToEat == 0) {
		UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
	}

	if (aGameManager) {
		if (isBonus) {
			aGameManager->triggerFrightenedMode();
		}

		aGameManager->increaseDotNumber();
	}
}

FVector APacmanPawn::getCurrentDirection()
{
	return PawnMovement->getCurrentDirection();
}

// Called to bind functionality to input
void APacmanPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveRight", this, &APacmanPawn::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &APacmanPawn::MoveUp);

	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APacmanPawn::UpdateAnimation()
{
	FVector newDirection = getCurrentDirection();

	if (newDirection != lastDirection) {
		if (newDirection.X > 0) {
			currentSprite->SetFlipbook(LeftSprite);
		}
		else if (newDirection.X < 0) {
			currentSprite->SetFlipbook(RightSprite);
		}
		else if (newDirection.Y > 0) {
			currentSprite->SetFlipbook(UpSprite);
		}
		else if(newDirection.Y < 0) {
			currentSprite->SetFlipbook(DownSprite);
		}

		lastDirection = newDirection;
	}
}

/* Input functions */

void APacmanPawn::MoveRight(float rate)
{
	PawnMovement->AddInputVector(-GetActorForwardVector()*rate);
}

void APacmanPawn::MoveUp(float rate)
{
	PawnMovement->AddInputVector(GetActorRightVector()*rate);
}

