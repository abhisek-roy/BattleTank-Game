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
	void ActuateLeft();

	UFUNCTION(BlueprintCallable, Category = Movement)
	void ActuateRight();

	void RequestDirectMove( const FVector & MoveVelocity, bool bForceMaxSpeed) override;
	
protected:
	UStaticMeshComponent* LeftTrack = nullptr; 
	UStaticMeshComponent* RightTrack = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MaxTractiveForce = 50000000.0f;
	
private:
	float ForwardForceLeft = 0, ForwardForceRight = 0;
	float RotateForceLeft = 0, RotateForceRight = 0;

	// Rear Bias, Front Bias = 1 - Bias value
	UPROPERTY(EditDefaultsOnly, Category = "Tuning", meta = (ClampMin = "0.0", ClampMax = "0.99", UIMin = "0.0", UIMax = "0.99"))
	float Bias = 0.8f;
	UPROPERTY(EditDefaultsOnly, Category = "Tuning", meta = (ClampMin = "0.0", ClampMax = "300", UIMin = "0.0", UIMax = "300"))
	float CGHeight = 100.f;
	UPROPERTY(EditDefaultsOnly, Category = "Tuning", meta = (ClampMin = "0.0", ClampMax = "300", UIMin = "0.0", UIMax = "300"))
	float CGOffset = 200.f;
	UPROPERTY(EditDefaultsOnly, Category = "Tuning", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float AdjustForceDueFrameRate = 20.f;

	void ApplySidewaysForce();
};

