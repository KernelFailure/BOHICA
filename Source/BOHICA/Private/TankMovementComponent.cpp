// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
    if (!ensure(LeftTrack && RightTrack)) {return;}
    auto Name = GetOwner()->GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s is moving FORWARD at throw speed: %f"), *Name, Throw);
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
    if (!ensure(LeftTrack && RightTrack)) {return;}
    auto Name = GetOwner()->GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s is TURNING RIGHT at throw speed: %f"), *Name, Throw);
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
    
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();

    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    IntendMoveForward(ForwardThrow);

    auto RightTurnVector = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
    IntendTurnRight(RightTurnVector);

    auto Name = GetOwner()->GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s: MoveComp forward vector: %f - right turn vector: %f"), *Name, ForwardThrow, RightTurnVector);
    
    
}