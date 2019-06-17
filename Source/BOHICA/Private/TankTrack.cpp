// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Speed) {
    

    auto ForceApplied = GetForwardVector() * Speed * TrackMaxDrivingForce;
    auto ForceLoation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLoation);
}

UTankTrack::UTankTrack() {
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    
    UE_LOG(LogTemp, Warning, TEXT("Ticking in Track."));
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    auto root = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (root->GetMass() * CorrectionAcceleration) / 2;
    root->AddForce(CorrectionForce);
}