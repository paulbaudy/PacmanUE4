// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "TileGrid.h"


// Sets default values
ATileGrid::ATileGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // TODO false

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	mGridMeshs = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GridMesh"));
	mGridMeshs->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void ATileGrid::BeginPlay()
{
	Super::BeginPlay();

	/* Clear grid & meshes */
	mGridMeshs->ClearInstances();
	for (TArray<bool> _grid : bGrid) {
		_grid.Empty();
	}

	/* Initialize Grid */
	bGrid.Empty();
	TArray<bool> initArray;
	initArray.Init(false, numberY);
	bGrid.Init(initArray, numberX);

	FString Texte = "TEst";
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Texte);

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.bNoFail = false;

	for (int i = 0; i < numberX; i++) {
		for (int j = 0; j < numberY; j++) {

			FVector _location = GetActorLocation();
			_location.X += i * dotDistance;
			_location.Y += j * dotDistance;

			// ComponentOverlapActors needs to know what channel to use for collision detection
			TArray<TEnumAsByte<EObjectTypeQuery> > arrayObjectTypeQuery;
			arrayObjectTypeQuery.Add(EObjectTypeQuery::ObjectTypeQuery1); // World Dynamic
			arrayObjectTypeQuery.Add(EObjectTypeQuery::ObjectTypeQuery2); // Pawn

			TArray<AActor*> arrayIgnore;
			TArray<AActor*> arrayOutput;

			UKismetSystemLibrary::BoxOverlapActors(GetWorld(), _location, FVector(7.f, 7.f, 7.f), arrayObjectTypeQuery, /*UPaperSpriteComponent::StaticClass()*/ NULL, arrayIgnore, arrayOutput);
			FString Text = FString::SanitizeFloat(arrayOutput.Num());

			if (arrayOutput.Num() == 0) {
				bGrid[i][j] = true;
				if (bShowGrid) {
					FTransform _transform;
					_transform.SetLocation(_location);
					_transform.SetScale3D(FVector(0.1f, 0.1f, 0.1f));
					mGridMeshs->AddInstance(_transform);
				}
			}
			else {
				bGrid[i][j] = false;
			}

		}
	}
	FString Text = FString::SanitizeFloat(bGrid.Num());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Text);

}

void ATileGrid::OnConstruction(const FTransform& Transform)
{
	/* Clear grid & meshes */
	mGridMeshs->ClearInstances();
	for (TArray<bool> _grid : bGrid) {
		_grid.Empty();
	}

	/* Initialize Grid */
	bGrid.Empty();
	TArray<bool> initArray;
	initArray.Init(false, numberY);
	bGrid.Init(initArray, numberX);

	FString Texte = "TEst";
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Texte);

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.bNoFail = false;

	for (int i = 0; i < numberX; i++) {
		for (int j = 0; j < numberY; j++) {
			
			FVector _location = GetActorLocation();
			_location.X += i * dotDistance;
			_location.Y += j * dotDistance;

			// ComponentOverlapActors needs to know what channel to use for collision detection
			TArray<TEnumAsByte<EObjectTypeQuery> > arrayObjectTypeQuery;
			arrayObjectTypeQuery.Add(EObjectTypeQuery::ObjectTypeQuery1); // World Dynamic
			arrayObjectTypeQuery.Add(EObjectTypeQuery::ObjectTypeQuery2); // Pawn

			TArray<AActor*> arrayIgnore;
			TArray<AActor*> arrayOutput;

			UKismetSystemLibrary::BoxOverlapActors(GetWorld(), _location, FVector(7.f, 7.f, 7.f), arrayObjectTypeQuery, /*UPaperSpriteComponent::StaticClass()*/ NULL, arrayIgnore, arrayOutput);
			FString Text = FString::SanitizeFloat(arrayOutput.Num());

			if (arrayOutput.Num() == 0) {
				bGrid[i][j] = true;
				if (bShowGrid) {
					FTransform _transform;
					_transform.SetLocation(_location);
					_transform.SetScale3D(FVector(0.1f, 0.1f, 0.1f));
					mGridMeshs->AddInstance(_transform);
				}
			}
			else {
				bGrid[i][j] = false;
			}
			
		}
	}
	FString Text = FString::SanitizeFloat(bGrid.Num());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Text);
}

// Called every frame
void ATileGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

bool ATileGrid::canWalk(unsigned int x, unsigned int y)
{
	if (x >= (unsigned int) numberX || y >= (unsigned int) numberY) return false;

	return bGrid[x][y];
}

bool ATileGrid::canWalk(FVector location)
{
	FIntVector gridLocation = WorldToGrid(location);
	return canWalk(gridLocation.X, gridLocation.Y);
}

FIntVector ATileGrid::WorldToGrid(FVector location)
{

	FIntVector result;
	result.X = (int)location.X / 16;
	result.Y = (int)location.Y / 16; // TODO constantes
	return result;
}

int ATileGrid::accessibleTiles(FVector location)
{
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), location, 10.f, 12, FLinearColor::White, 20.f);
	
	int cpt = 0;
	FIntVector result = WorldToGrid(location);
	return accessibleTiles(result.X, result.Y);
}

int ATileGrid::accessibleTiles(unsigned int x, unsigned int y)
{
	int cpt = 0;
	canWalk(x + 1, y) ? cpt++ : GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "xp");
	canWalk(x - 1, y) ? cpt++ : GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "xn");;
	canWalk(x, y + 1) ? cpt++ : GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "yp");;
	canWalk(x, y - 1) ? cpt++ : GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "yn");;
	return cpt;
}

FIntVector ATileGrid::SpeedWorldtoSpeedGrid(FVector velocity)
{
	if (velocity.Y > velocity.X) {
		return FIntVector(0, velocity.Y > 0.f?1:-1, 0);
	}
	else {
		return FIntVector(velocity.X > 0.f ? 1 : -1, 0, 0);
	}
}

