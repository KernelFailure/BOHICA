// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay() {
    Super::BeginPlay();
    auto AITank = GetPlayerTank();
    if (!AITank) {return;}
    UE_LOG(LogTemp, Warning, TEXT("AI found player tank: %s"), *(AITank->GetName()));
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const{
    auto FirstPlayerController = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!FirstPlayerController) {return nullptr;}
    return Cast<ATank>(FirstPlayerController);
}