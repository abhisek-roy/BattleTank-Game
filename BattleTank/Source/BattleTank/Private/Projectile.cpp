// Copyright 2021, Abhisek Roy

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	// No need to protect component as constructed in the constructor
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	BlastForce = CreateDefaultSubobject<URadialForceComponent>(FName("Blast Force"));
	BlastForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BlastForce->bAutoActivate = false;
	
	// SoundAttenuation = CreateDefaultSubobject<USoundAttenuation>(FName("Settings"));
	// BlastForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();	
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::Launch(float Speed)
{
	if(!ensure(ProjectileMovement)) return;
	ProjectileMovement->SetVelocityInLocalSpace( FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
	if(!ensure(LaunchSound)) return;
	UGameplayStatics::PlaySoundAtLocation( this, LaunchSound, GetActorLocation(), 1.f, 1.f, 0.f, SoundAttenuation);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ImpactBlast->Activate();
	CollisionMesh->SetVisibility(false);
	LaunchBlast->Deactivate();
	BlastForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		BlastForce->Radius, // for consistancy
		UDamageType::StaticClass() ,
		TArray<AActor*>() // damage all actors
	);

	if(!ensure(BlastSound)) return;
	UGameplayStatics::PlaySoundAtLocation( this, BlastSound, GetActorLocation(), 1.f, 1.f, 0.f, SoundAttenuation);

	FTimerHandle ProjectileDestroyTimer;
	GetWorld()->GetTimerManager().SetTimer(ProjectileDestroyTimer ,this, &AProjectile::DestroyProjectile, ProjectileLife, false);
}

void AProjectile::DestroyProjectile()
{
	Destroy();
}
