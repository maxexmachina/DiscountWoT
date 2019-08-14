// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
private:

	ATank* GetControlledTank() const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirecion) const;

	// Start moving the barrel so that
	// a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();

	// Return OUT parameter, true if hits landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	// Get the point of intersection of linetrace with the landscape
	bool GetLookVectorHitLocaion(FVector& HitLocation, FVector LookDirection) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
