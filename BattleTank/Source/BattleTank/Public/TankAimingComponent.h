// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector AimLocation, float ProjectileSpeed);
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);
	void SetTurretReference(UStaticMeshComponent* TurretToSet);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	EFiringState FiringState = EFiringState::Reloading;
public:

private:
	UStaticMeshComponent* Barrel = nullptr;
	UStaticMeshComponent* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
	void ElevateBarrel(float RelSpeed);
	void OrientTurret(float RelSpeed);

};
