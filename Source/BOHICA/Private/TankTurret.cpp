// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto Rotation = RelativeRotation.Yaw + RotationChange;
    auto time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: Barrel Rotation: %f"), time, Rotation);
    SetRelativeRotation(FRotator(0, Rotation, 0));
}