// Copyright 2021, Abhisek Roy

#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    ATank* PawnTank = GetControlledTank();
    if(!PawnTank) return;
    UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possessing: %s."), *(PawnTank->GetName()));
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetControlledTank()) return;

    FVector HitLocation;
    if(GetSightRayHitLocation(HitLocation))
    {
        // UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s."), *HitLocation.ToCompactString());
        GetControlledTank()->AimAt(HitLocation);
    }

    // TODO Tank starts orienting the barrel
}

bool ATankPlayerController::GetSightRayHitLocation( FVector& OutHitLocation) const
{
    OutHitLocation = FVector(0,0,0);
    
    // Raycast through the barrel, if hits returns true and update HitLocation
    // Find the crosshair position in Pixel Coordinate
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    FVector2D ScreenLocation(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);
    // UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s."), *ScreenLocation.ToString());

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
        ECC_Visibility
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