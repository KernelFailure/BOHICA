// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
    
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
    
}

UTankTrack::UTankTrack() {
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay() {
    Super::BeginPlay();
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
    UE_LOG(LogTemp, Warning, TEXT("I'm hit...Ben is immature"));
    DriveTrack();
    ApplySidewaysForce();
    CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce() {
    //UE_LOG(LogTemp, Warning, TEXT("Ticking in Track."));
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    auto root = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (root->GetMass() * CorrectionAcceleration) / 2;
    root->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack() {
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLoation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLoation);
}