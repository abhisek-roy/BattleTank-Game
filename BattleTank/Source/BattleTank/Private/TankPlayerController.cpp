// Copyright 2021, Abhisek Roy

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h" // So we can omplement OnDeath

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (ensure(AimingComponent)) FoundAimingComponent(AimingComponent);
}


void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if(InPawn) 
    {
        auto PossesedTank = Cast<ATank>(InPawn);
        if(!ensure(PossesedTank)) return;

        // Subscribe our local method to the tank's death event
        PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossesedTankDeath);
    }
}

void ATankPlayerController::OnPossesedTankDeath()
{
    StartSpectatingOnly();
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetPawn()) return;
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) return;    

    FVector HitLocation;
    if(GetSightRayHitLocation(HitLocation))
    {
       AimingComponent->AimAt(HitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation( FVector& OutHitLocation) const
{
    OutHitLocation = FVector(0,0,0);
    
    // Raycast through the barrel, if hits returns true and update HitLocation
    // Find the crosshair position in Pixel Coordinate
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    FVector2D ScreenLocation(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);

    // "De-project" the screen position of the crosshair to a world direction
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
    // Line-trace along that look direction, and see what we hit (up to a max range)
        return GetLookVectorHitLocation(LookDirection, OutHitLocation);        
    }
    return false;
}

bool ATankPlayerController::GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraLocation;
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraLocation,
        LookDirection
    );
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector LookDirection, FVector& OutHitLocation) const
{
    // LineTraceSingleByChannel();
    FHitResult HitResult;
    FVector RayStart = PlayerCameraManager->GetCameraLocation(); 
    FVector RayEnd = RayStart + Range * LookDirection;

    if (GetWorld()->LineTraceSingleByChannel(
        HitResult,
        RayStart,
        RayEnd,
        ECollisionChannel::ECC_Camera
        )
    )
    {
        OutHitLocation = HitResult.Location;
        return true;
    }else   
    {
        OutHitLocation = FVector(0);
        return false;
    }
}