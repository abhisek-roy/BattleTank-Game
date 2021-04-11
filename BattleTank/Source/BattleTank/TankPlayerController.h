// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Always the last one

/**
 * 
 */

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	float Range = 1000000.0f;
	
	UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5f;

    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.29f;

	void AimTowardsCrosshair();
	ATank* GetControlledTank() const;
	bool GetSightRayHitLocation( FVector& HitLocation) const;
	bool GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(const FVector LookDirection, FVector& OutHitLocation) const;
};