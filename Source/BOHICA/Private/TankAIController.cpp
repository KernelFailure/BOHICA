// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay() {
    Super::BeginPlay();    
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    auto ControlledTank = Cast<ATank>(GetPawn());
    if (PlayerTank) {
        MoveToActor(PlayerTank, AcceptanceRadius);
        //ENGINE_NavMovementComponent_generated_h
        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        ControlledTank->Fire(); //Turn off enemy fire to testing.  Just un-comment to make them fire again
    }
}


