// Copyright 2021, Abhisek Roy


#include "TankBarrel.h"

void UTankBarrel::Elevate( float RelSpeed )
{
    // Move the barrel the right about this frame
	// Given a max elevation speed, and the frame time
    // RelSpeed -1 to +1
    RelSpeed = FMath::Clamp<float>(RelSpeed, -1, 1);
    
    float Attitude = RelativeRotation.Pitch + RelSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
    Attitude = FMath::Clamp<float>(Attitude, MinElevationDeg, MaxElevationDeg);
    SetRelativeRotation(FRotator(Attitude, 0,0));
    // UE_LOG(LogTemp, Warning, TEXT("RelSpd = %f, Attitude = %f."), RelSpeed, Attitude);
}