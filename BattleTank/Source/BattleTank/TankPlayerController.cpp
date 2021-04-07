// Copyright 2021, Abhisek Roy

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
        UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s."), *HitLocation.ToCompactString());
    }

    // TODO Tank starts orienting the barrel
}

bool ATankPlayerController::GetSightRayHitLocation( FVector& OutHitLocation) const
{
    OutHitLocation = FVector(0,0,0);
    // Raycast through the barrel, if hits returns true and update HitLocation
    
    // Find the crosshair position in Pixel Coordinate
    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5f;

    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.25f;

    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    FVector2D ScreenLocation(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);
    // UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s."), *ScreenLocation.ToString());

    // "De-project" the screen position of the crosshair to a world direction
    FVector CameraLocation, CameraRotation;
    DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraLocation,
        CameraRotation
    );
    UE_LOG(LogTemp, Warning, TEXT("Lookina at: %s."), *CameraRotation.ToString());
    
    // Line-trace along that look direction, and see what we hit (up to a max range)
    
    return false;
}