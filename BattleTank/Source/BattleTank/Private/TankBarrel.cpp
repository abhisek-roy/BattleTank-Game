// Copyright 2021, Abhisek Roy


#include "TankBarrel.h"

void UTankBarrel::Elevate( float DegsPerSec )
{
    // Move the barrel the right about this frame
	// Given a max elevation speed, and the frame time
    UE_LOG(LogTemp, Warning, TEXT("%s should elevate barrel by: %s."),*GetOwner()->GetName(), DegsPerSec);

}