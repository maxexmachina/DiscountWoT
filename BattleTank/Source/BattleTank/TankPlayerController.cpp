// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank player controller is possessing %s"), *GetPawn()->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Tank player controller is not possessing anything"))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	
	// Get world location if linetrace hrough the crosshair
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

// Get world location of linetrace through the crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position
	int32 VieportSizeX, ViewportSizeY;
	FVector LookDirection;
	GetViewportSize(VieportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(VieportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Linetrace along that direction, and see what we hit (up to max range)
		GetLookVectorHitLocaion(HitLocation, LookDirection);
	}

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocaion(FVector& HitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	FVector LineTraceStart = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = LineTraceStart + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		LineTraceStart,
		LineTraceEnd,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Linetrace didn't succeed
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

// "De-project" the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}




