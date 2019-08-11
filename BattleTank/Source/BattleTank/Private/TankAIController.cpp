// Fill out your copyright notice in the Description page of Project Settings.



#include "TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetPlayerTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("AI found player: %s"), *GetPlayerTank()->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI not found player tank"))
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }

	return Cast<ATank>(PlayerPawn);
}
