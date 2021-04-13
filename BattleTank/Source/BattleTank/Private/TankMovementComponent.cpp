// Copyright 2021, Abhisek Roy


#include "TankMovementComponent.h"
#include "Components/StaticMeshComponent.h"

void UTankMovementComponent::Initialize(UStaticMeshComponent* LeftTrackToSet, UStaticMeshComponent* RightTrackToSet)
{
    if(!ensure(LeftTrackToSet && RightTrackToSet)) return;
	LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;    
}

void UTankMovementComponent::IntendToMove(float Throw)
{
	ApplyThrottleIndividually(Throw, Throw);
}

void UTankMovementComponent::RotateRight(float Throw)
{
    ApplyThrottleIndividually(Throw, -1 * Throw);
}

// Individually apply throttle to the tracks
void UTankMovementComponent::ApplyThrottleIndividually(float ThrottleLeft, float ThrottleRight)
{
	ThrottleLeft = FMath::Clamp(ThrottleLeft, -1.f, 1.f);
	ThrottleRight = FMath::Clamp(ThrottleRight, -1.f, 1.f);
    auto LeftForceMag = ThrottleLeft * MaxTractiveForce * 0.8;
    auto RightForceMag = ThrottleRight * MaxTractiveForce * 0.8;

	if (!ensure(LeftTrack && RightTrack)) return;

	auto LeftForce = LeftTrack->GetForwardVector() * LeftForceMag;
	auto RightForce = RightTrack->GetForwardVector() * RightForceMag;

	LeftTrack->AddForceAtLocation(LeftForce, LeftTrack->GetComponentLocation());
    RightTrack->AddForceAtLocation(RightForce, RightTrack->GetComponentLocation());
}

void UTankMovementComponent::RequestDirectMove( const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we're replacing the functionality from the Engine code
	auto TankName = GetOwner()->GetName();
	auto AIMoveIntention = MoveVelocity.GetSafeNormal();
	auto FaceDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(FaceDirection, AIMoveIntention);
	auto Rotate = FVector::CrossProduct(FaceDirection, AIMoveIntention).Z;

	IntendToMove(ForwardThrow);
	RotateRight(Rotate);
}
