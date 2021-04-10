// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;

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

private:
	UFUNCTION( BlueprintCallable, Category = Setup)
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	UFUNCTION( BlueprintCallable, Category = Setup)
	void SetTurretReference(UStaticMeshComponent* TurretToSet);

	UFUNCTION( BlueprintCallable, Category = Setup)
	void Fire();

	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileSpeed = 4000.0f;
};
