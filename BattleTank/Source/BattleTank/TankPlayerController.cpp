// Copyright 2021, Abhisek Roy

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}