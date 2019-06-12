// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
    auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f Intend move forward throw: %f"), Time, Throw);
    if (!LeftTrack || !RightTrack) {return;}
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
    auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f Intend move forward throw: %f"), Time, Throw);
    if (!LeftTrack || !RightTrack) {return;}
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
    auto Name = GetOwner()->GetName();
    auto MoveVelocityString = MoveVelocity.ToString();
    UE_LOG(LogTemp, Warning, TEXT("%s is moving at: %s"), *Name, *MoveVelocityString);
}