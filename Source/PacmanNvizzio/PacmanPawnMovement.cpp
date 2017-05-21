// Paul BAUDY for Nvizzio Creations Inc

#include "PacmanNvizzio.h"
#include "PacmanPawnMovement.h"


UPacmanPawnMovement::UPacmanPawnMovement() : UFloatingPawnMovement() ,
	maxVelocity(100.f) // TODO constante
{}

void UPacmanPawnMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	// If this Movement Component is not owned by a pawn, UpdatedComponent is not correct,
	// or if pawn is not rendered, or can't even move, this component is not updated
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Get new direction by inputs
	FVector Direction = ConsumeInputVector().GetClampedToMaxSize(1.0f);
	if (Direction.Y != 0) Direction.X = 0;

	//if (Direction.Y > 0)
	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, Direction.ToString());


	// Try going to the new direction if it is different than the current destination.
	// If this new direction will trigger a collision, simply continue moving according 
	// to the current Pacman velocity
	if (!Direction.IsNearlyZero() && !Direction.Equals(currentDirection, 0.1f)) {

		FHitResult fResult;
		FCollisionQueryParams fParams;
		fParams.AddIgnoredActor(UpdatedComponent->GetOwner());

		if (Direction.Y != 0.f) {
			int dirY = Direction.Y;
			int dirX = -currentDirection.X;
			//GEngine->AddOnScreenDebugMessage(-1, 0.08f, FColor::Red, FString::SanitizeFloat(dirY));

			bool bResult = GetWorld()->LineTraceSingleByChannel(fResult, UpdatedComponent->GetComponentLocation() + FVector(0.f, 20.f, 0.f)*dirY + FVector(15.f, 0.f, 0.f)*dirX, UpdatedComponent->GetComponentLocation() + FVector(0.f, 20.f, 0.f)*dirY - FVector(15.f, 0.f, 0.f)*dirX, ECollisionChannel::ECC_WorldDynamic, fParams);
			DrawDebugLine(GetWorld(), UpdatedComponent->GetComponentLocation() + FVector(0.f, 20.f, 0.f)*dirY + FVector(15.f, 0.f, 0.f)*dirX, UpdatedComponent->GetComponentLocation() + FVector(0.f, 20.f, 0.f)*dirY - FVector(15.f, 0.f, 0.f)*dirX, FColor::Red, false, -1.f, 0, 1.f);

			if (bResult) {
				GoToCurrentDirection(DeltaTime);
				return;
			}
		}
		else if (Direction.X != 0.f) {
			int dirY = -currentDirection.Y;
			int dirX = Direction.X;

			bool bResult = GetWorld()->LineTraceSingleByChannel(fResult, UpdatedComponent->GetComponentLocation() + FVector(20.f, 0.f, 0.f)*dirX + FVector(0.f, 15.f, 0.f)*dirY, UpdatedComponent->GetComponentLocation() + FVector(20.f, 0.f, 0.f)*dirX - FVector(0.f, 15.f, 0.f)*dirY, ECollisionChannel::ECC_WorldDynamic, fParams);
			DrawDebugLine(GetWorld(), UpdatedComponent->GetComponentLocation() + FVector(20.f, 0.f, 0.f)*dirX + FVector(0.f, 15.f, 0.f)*dirY, UpdatedComponent->GetComponentLocation() + FVector(20.f, 0.f, 0.f)*dirX - FVector(0.f, 15.f, 0.f)*dirY, FColor::Red, false, -1.f, 0, 1.f);

			if (bResult) {
				GoToCurrentDirection(DeltaTime);
				return;
			}
		}
		FHitResult Hit;
		bool res = SafeMoveUpdatedComponent(Direction* DeltaTime * maxVelocity, UpdatedComponent->GetComponentRotation(), true, Hit);


		// If our new direction is not hitting anything, it will be our new constant velocity...
		if (!Hit.IsValidBlockingHit()) {
			currentDirection = Direction;
		}
		// ... Or if we can't go to this new direction, Pacman will move according to its 
		// current velocity
		else {
			GoToCurrentDirection(DeltaTime);
		}

	}
	// If no input is triggered, Pacman will move according to its current velocity
	else if (currentDirection != FVector::ZeroVector) {
		GoToCurrentDirection(DeltaTime);
	}
}

void UPacmanPawnMovement::GoToCurrentDirection(float DeltaTime)
{
	FHitResult Hit;
	MoveUpdatedComponent(currentDirection* DeltaTime * maxVelocity, UpdatedComponent->GetComponentRotation().Quaternion(), true, &Hit);


	// When no correct input is received, and when Pacman is hitting something with its 
	// current velocity, then it stops moving. 
	if (Hit.IsValidBlockingHit()) {
		//currentDirection = FVector::ZeroVector;
	}

}

FVector UPacmanPawnMovement::getCurrentDirection()
{
	return currentDirection.ClampMaxSize(1.f);
}
