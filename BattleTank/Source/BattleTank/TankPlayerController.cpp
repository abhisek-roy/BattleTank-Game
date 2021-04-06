// Copyright 2021, Abhisek Roy

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    ATank* PawnTank = GetControlledTank();
    if(!PawnTank) return;
    UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possessing: %s."), *(PawnTank->GetName()));
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}