// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


// Forward declarations
class UTankBarrel;
class UTankTurret;

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
	void GetBarrelReference(UStaticMeshComponent* BarrelReference);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UStaticMeshComponent* Barrel = nullptr;
	UStaticMeshComponent* Turret = nullptr;
	UStaticMeshComponent* BarrelSM;

	void MoveBarrelTowards(FVector AimDirection);
	void ElevateBarrel(float RelSpeed);
	void OrientTurret(float RelSpeed);
};
