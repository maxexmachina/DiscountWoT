// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


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


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

