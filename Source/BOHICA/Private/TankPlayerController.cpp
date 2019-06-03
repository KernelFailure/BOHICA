// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()  {
    Super::BeginPlay();
    auto tank = GetControlledTank();
    if (!tank) {return;}
    //UE_LOG(LogTemp, Warning, TEXT("Player controller found tank: %s"), *(tank->GetName()));
}

void ATankPlayerController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
    // auto tank = Cast<ATank>(GetPawn());
    // tank->GetName();
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair(){
    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation)) {
            UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
    int32 sizeX, sizeY;
    GetViewportSize(sizeX, sizeY);
    FVector2D ScreenLocation = FVector2D(sizeX * CrossHairXLocation, sizeY * CrossHairYLocation);
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection)) {
        //UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
        GetLookVectorHitLocation(LookDirection, HitLocation);
    }

    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    if (GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility)
        )
    {
        HitLocation = HitResult.Location;
        return true;
    }
    return false;
}
