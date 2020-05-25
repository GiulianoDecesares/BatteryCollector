// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan_GameMode.h"

ABatteryMan_GameMode::ABatteryMan_GameMode()
{
    this->PrimaryActorTick.bCanEverTick = true;
}

void ABatteryMan_GameMode::BeginPlay()
{
    Super::BeginPlay();
    
}

void ABatteryMan_GameMode::Tick(float DeltaTme)
{
    Super::Tick(DeltaTme);
}
