// Copyright 2021, Abhisek Roy

#include "TankMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

void UTankMovementComponent::Initialize(UStaticMeshComponent* LeftTrackToSet, UStaticMeshComponent* RightTrackToSet)
{
    if(!ensure(LeftTrackToSet && RightTrackToSet)) return;
	LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendToMove(float Throw)
{
	ForwardForceLeft = Throw / 2;
	ForwardForceRight = Throw / 2;
}

void UTankMovementComponent::RotateRight(float Throw)
{
	RotateForceLeft = Throw / 2;
	RotateForceRight = Throw / 2;
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
	ActuateLeft();
	ActuateRight();
}

void UTankMovementComponent::ActuateLeft()
{
	if (!ensure(LeftTrack)) return;
	auto ThrottleLeft = FMath::Clamp(ForwardForceLeft + RotateForceLeft, -1.f, 1.f);
	auto LeftForce = ThrottleLeft * MaxTractiveForce * LeftTrack->GetForwardVector();
	LeftTrack->AddForceAtLocation(LeftForce, LeftTrack->GetComponentLocation());
	ApplySidewaysForce();
	ForwardForceLeft = 0;
	RotateForceLeft = 0;
}

void UTankMovementComponent::ActuateRight()
{
	if (!ensure(RightTrack)) return;
	auto ThrottleRight = FMath::Clamp(ForwardForceRight - RotateForceRight, -1.f, 1.f);
	auto RightForce = ThrottleRight * MaxTractiveForce * RightTrack->GetForwardVector();
	RightTrack->AddForceAtLocation(RightForce, RightTrack->GetComponentLocation());
	ApplySidewaysForce();
	ForwardForceRight = 0;
	RotateForceRight = 0;
}

void UTankMovementComponent::ApplySidewaysForce()
{
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if (TankRoot->GetComponentVelocity().Size() < 10.0)  // Magic number to ignore sideways friction a lower speed
	{
		return;
	}

	// Apply extra force to counter sideways slip
	auto Velocity = TankRoot->GetComponentVelocity();
	auto SlippageSpeed = FVector::DotProduct(Velocity.GetSafeNormal(), TankRoot->GetRightVector());
	auto SlippageForce = -MaxTractiveForce * SlippageSpeed * TankRoot->GetRightVector() / 2; // Two application points

	FVector ApplicationPointF = TankRoot->GetComponentLocation() + TankRoot->GetUpVector() * CGHeight + TankRoot->GetForwardVector() * CGOffset;
	FVector ApplicationPointR = TankRoot->GetComponentLocation() + TankRoot->GetUpVector() * CGHeight - TankRoot->GetForwardVector() * CGOffset;

	TankRoot->AddForceAtLocation(SlippageForce * (1 - Bias), ApplicationPointF);
	TankRoot->AddForceAtLocation(SlippageForce * (Bias), ApplicationPointR);
	DrawDebugLine(
		GetWorld(),
		ApplicationPointF,
		ApplicationPointF + SlippageForce.GetSafeNormal() * 500,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f
	);
	DrawDebugLine(
		GetWorld(),
		ApplicationPointR,
		ApplicationPointR + SlippageForce.GetSafeNormal() * 500,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f
	);
}
