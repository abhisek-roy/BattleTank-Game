// Copyright 2021, Abhisek Roy


#include "TankMovementComponent.h"
#include "Components/StaticMeshComponent.h"

void UTankMovementComponent::Initialize(UStaticMeshComponent* LeftTrackToSet, UStaticMeshComponent* RightTrackToSet)
{
    if (!LeftTrackToSet || !RightTrackToSet) return;

    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;    
}

void UTankMovementComponent::IntendToMove(float Throw)
{
    Throw = FMath::Clamp(Throw, -1.f, 1.f);
    
	UE_LOG(LogTemp, Warning, TEXT("Throw: %f"), Throw);
	auto LeftForce = LeftTrack->GetForwardVector() * Throw * MaxTractiveForce;
    auto RightForce = RightTrack->GetForwardVector() * Throw * MaxTractiveForce;

	LeftTrack->AddForceAtLocation(LeftForce, LeftTrack->GetComponentLocation());
    RightTrack->AddForceAtLocation(RightForce, RightTrack->GetComponentLocation());

    UE_LOG(LogTemp, Warning, TEXT("Total force %f."), LeftForce.Size());
}