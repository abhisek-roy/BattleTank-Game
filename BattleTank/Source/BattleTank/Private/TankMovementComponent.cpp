// Copyright 2021, Abhisek Roy


#include "TankMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

UTankMovementComponent::UTankMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if (TankRoot->GetComponentVelocity().Size() < 100.0)  // Magic number to ignore sideways friction a lower speed
	{
		return;
	}
	
	// Apply extra force to counter sideways slip
	auto Velocity = TankRoot->GetComponentVelocity();
	auto SlippageSpeed = FVector::DotProduct(Velocity.GetSafeNormal(), TankRoot->GetRightVector());
	auto SlippageForce = -MaxTractiveForce * SlippageSpeed * TankRoot->GetRightVector(); // Two application points

	FVector ApplicationPointF = TankRoot->GetComponentLocation() + TankRoot->GetUpVector()*CGHeight + TankRoot->GetForwardVector()*CGOffset;
	FVector ApplicationPointR = TankRoot->GetComponentLocation() + TankRoot->GetUpVector()*CGHeight - TankRoot->GetForwardVector()*CGOffset;

	TankRoot->AddForceAtLocation(SlippageForce*(1 - Bias), ApplicationPointF);
	TankRoot->AddForceAtLocation(SlippageForce*(Bias), ApplicationPointR);
	DrawDebugLine(
		GetWorld(),
		ApplicationPointF,
		ApplicationPointF + SlippageForce.GetSafeNormal()*500,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f
	);
	DrawDebugLine(
		GetWorld(),
		ApplicationPointR,
		ApplicationPointR + SlippageForce.GetSafeNormal()*500,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f
	);
}

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

	LeftForce = LeftTrack->GetForwardVector() * LeftForceMag;
	RightForce = RightTrack->GetForwardVector() * RightForceMag;
	
	LeftTrack->AddForceAtLocation(LeftForce, LeftTrack->GetComponentLocation());
    RightTrack->AddForceAtLocation(RightForce, RightTrack->GetComponentLocation());
}

void UTankMovementComponent::RequestDirectMove( const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we're replacing the functionality from the Engine code
	auto AIMoveIntention = MoveVelocity.GetSafeNormal();
	auto FaceDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(FaceDirection, AIMoveIntention);
	auto Rotate = FVector::CrossProduct(FaceDirection, AIMoveIntention).Z;

	IntendToMove(ForwardThrow);
	RotateRight(Rotate);
}
