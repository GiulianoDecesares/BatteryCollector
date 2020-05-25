// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryPickup.h"

ABatteryPickup::ABatteryPickup()
{
    this->GetMesh()->SetSimulatePhysics(true);

    this->power = 150.0f;
}

void ABatteryPickup::WasCollected_Implementation()
{
    Super::WasCollected_Implementation();
    this->Destroy();
}

float ABatteryPickup::GetPower() const
{
    return this->power;
}
