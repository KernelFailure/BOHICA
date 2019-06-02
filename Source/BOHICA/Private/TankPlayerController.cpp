// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const {
    // auto tank = Cast<ATank>(GetPawn());
    // tank->GetName();
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()  {
    Super::BeginPlay();
    auto tank = GetControlledTank();
    if (!tank) {return;}
    UE_LOG(LogTemp, Warning, TEXT("Player controller found tank: %s"), *(tank->GetName()));
}