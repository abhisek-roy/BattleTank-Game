// Copyright 2021, Abhisek Roy


#include "TankMovementComponent.h"
#include "Components/StaticMeshComponent.h"

void UTankMovementComponent::Initialize(UStaticMeshComponent* LeftTrackToSet, UStaticMeshComponent* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;    
}

void UTankMovementComponent::IntendToMove(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Intend to move"));
	ApplyThrottleIndividually(Throw, Throw);
}

void UTankMovementComponent::RotateRight(float Throw)
{
    ApplyThrottleIndividually(Throw, -1 * Throw);
	UE_LOG(LogTemp, Warning, TEXT("RotateRight."));
}

// Individually apply throttle to the tracks
void UTankMovementComponent::ApplyThrottleIndividually(float ThrottleLeft, float ThrottleRight)
{
	ThrottleLeft = FMath::Clamp(ThrottleLeft, -1.f, 1.f);
	ThrottleRight = FMath::Clamp(ThrottleRight, -1.f, 1.f);
    auto LeftForceMag = ThrottleLeft * MaxTractiveForce * 0.8;
    auto RightForceMag = ThrottleRight * MaxTractiveForce * 0.8;
	UE_LOG(LogTemp, Warning, TEXT("Apply individually"));
	
	UE_LOG(LogTemp, Warning, TEXT("%f, %f."), LeftForceMag, RightForceMag);
	if (!LeftTrack || !RightTrack) return;

	auto LeftForce = LeftTrack->GetForwardVector() * LeftForceMag;
	auto RightForce = RightTrack->GetForwardVector() * RightForceMag;

	LeftTrack->AddForceAtLocation(LeftForce, LeftTrack->GetComponentLocation());
    RightTrack->AddForceAtLocation(RightForce, RightTrack->GetComponentLocation());
}
