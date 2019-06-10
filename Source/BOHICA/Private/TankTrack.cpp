// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Speed) {
    auto Name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s Moving at speed: %f"), *Name, Speed);
}