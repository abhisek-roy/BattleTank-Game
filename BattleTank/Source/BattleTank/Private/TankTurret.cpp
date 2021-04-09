// Copyright 2021, Abhisek Roy


#include "TankTurret.h"

// void UTankTurret::Orient( float RelSpeed )
// {
    // // Move the barrel the right about this frame
	// // Given a max elevation speed, and the frame time
    // // RelSpeed -1 to +1
    // RelSpeed = FMath::Clamp<float>(RelSpeed, -1, 1);
    
    // float Yaw = RelativeRotation.Yaw + RelSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
    // // RelativeRotation.Add(0.f, RelSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds, 0.f);
    // SetRelativeRotation(FRotator(0, Yaw, 0));
    // UE_LOG(LogTemp, Warning, TEXT("%s: Pitch = %f, Yaw = %f."), *GetOwner()->GetName(),RelativeRotation.Pitch, Yaw);
// }