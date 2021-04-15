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
	
	UTankMovementComponent();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	FVector LeftForce = FVector(0);
	FVector RightForce = FVector(0);

	// Rear Bias, Front Bias = 1 - Bias value
	UPROPERTY(EditDefaultsOnly, Category = "Tuning", meta = (ClampMin = "0.0", ClampMax = "0.99", UIMin = "0.0", UIMax = "0.99"))
	float Bias = 0.8f;
	UPROPERTY(EditDefaultsOnly, Category = "Tuning", meta = (ClampMin = "0.0", ClampMax = "300", UIMin = "0.0", UIMax = "300"))
	float CGHeight = 100.f;
	UPROPERTY(EditDefaultsOnly, Category = "Tuning", meta = (ClampMin = "0.0", ClampMax = "300", UIMin = "0.0", UIMax = "300"))
	float CGOffset = 200.f;
};

