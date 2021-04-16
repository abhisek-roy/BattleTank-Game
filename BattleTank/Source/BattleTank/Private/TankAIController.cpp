// Copyright 2021, Abhisek Roy

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (ensure(AimingComponent)) return;
}

void ATankAIController::Tick( float DeltaTime)
{
    Super::Tick( DeltaTime);

    // Move towards Player
    MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), AcceptanceRadius);

    // Aim towards Player
    AimingComponent->AimAt(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
    
    // Fire if ready i.e. locked
    if( AimingComponent->GetFiringState() == EFiringState::Locked )
        AimingComponent->Fire();
}

