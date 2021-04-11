// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt( FVector AimLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION( BlueprintCallable, Category = Setup)
	void Fire();

	UFUNCTION( BlueprintCallable, Category = Setup)
	void ApplyForce(float Throttle, UStaticMeshComponent* Track);

private:
	UFUNCTION( BlueprintCallable, Category = Setup)
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	UFUNCTION( BlueprintCallable, Category = Setup)
	void SetTurretReference(UStaticMeshComponent* TurretToSet);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxTractiveForce = 40000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ProjectileSpeed = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.f;

	float LastFiredAt = 0.f;

	UStaticMeshComponent* Barrel;
};
