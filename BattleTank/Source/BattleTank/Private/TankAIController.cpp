// Copyright 2021, Abhisek Roy

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h" // So we can omplement OnDeath

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if(InPawn) 
    {
        PossesedTank = Cast<ATank>(InPawn);
        if(!ensure(PossesedTank)) return;

        // Subscribe our local method to the tank's death event
        PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
    }
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick( float DeltaTime)
{
    Super::Tick( DeltaTime);
    // If not depossesed
    AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) return;

    // Move towards Player
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

    if (!PlayerTank) return;
    MoveToActor(PlayerTank, AcceptanceRadius);
    // Aim towards Player
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    // Fire if ready i.e. locked
    if( AimingComponent->GetFiringState() == EFiringState::Locked )
        AimingComponent->Fire();
}

void ATankAIController::OnPossesedTankDeath()
{
    PossesedTank = Cast<ATank>(GetPawn());
    if(!ensure(PossesedTank)) return;
    PossesedTank->DetachFromControllerPendingDestroy();
    // PossesedTank->Destroy();
}