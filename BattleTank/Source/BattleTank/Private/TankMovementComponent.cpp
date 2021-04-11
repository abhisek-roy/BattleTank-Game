// Copyright 2021, Abhisek Roy


#include "TankMovementComponent.h"

void UTankMovementComponent::IntendToMove(float Throw)
{
    Throw = FMath::Clamp(Throw, -1.f, 1.f);
    
	UE_LOG(LogTemp, Warning, TEXT("Throw: %f"), Throw);
}