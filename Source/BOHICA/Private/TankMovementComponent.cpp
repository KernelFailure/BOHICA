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
    UE_LOG(LogTemp, Warning, TEXT("Start request direct move..."));
    auto Name = GetOwner()->GetName();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    auto RightTurnVector = FVector::CrossProduct(TankForward, AIForwardIntention);
    auto RightTurnThrow = RightTurnVector.Z;
    UE_LOG(LogTemp, Warning, TEXT("MoveComp forward vector: %f - right turn vector: %f"), ForwardThrow, RightTurnThrow)
    IntendMoveForward(ForwardThrow);
    IntendTurnRight(RightTurnThrow);
}