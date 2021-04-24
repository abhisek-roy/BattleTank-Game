// Copyright 2021, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;
class USoundBase;
class USoundAttenuation;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Launch(float Speed);

private:
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	USoundAttenuation* SoundAttenuation = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	URadialForceComponent* BlastForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	USoundBase* BlastSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	USoundBase* LaunchSound = nullptr;

	// Destroy Projectile after
	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ProjectileLife = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ProjectileDamage = 20.f;

	UFUNCTION()    
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void DestroyProjectile();
};
