// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UStaticMeshComponent;

/**
 * Fly-by-wire and manual movement components
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:	
	// Sets left track and right track reference
	UFUNCTION( BlueprintCallable, Category = Setup)
	void Initialize(UStaticMeshComponent* LeftTrackToSet, UStaticMeshComponent* RightTrackToSet);
	
	UFUNCTION( BlueprintCallable, Category = Movement)
	void IntendToMove(float Throw);

	UFUNCTION( BlueprintCallable, Category = Movement)
	void RotateRight(float Throw);

	UFUNCTION( BlueprintCallable, Category = Movement)
	void ApplyThrottleIndividually(float ThrottleLeft, float ThrottleRight);

	void RequestDirectMove( const FVector & MoveVelocity, bool bForceMaxSpeed) override;
	
protected:
	UStaticMeshComponent* LeftTrack = nullptr; 
	UStaticMeshComponent* RightTrack = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MaxTractiveForce = 30000000.0f;
};

