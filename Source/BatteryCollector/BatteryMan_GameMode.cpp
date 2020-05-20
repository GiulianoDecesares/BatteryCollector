// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan_GameMode.h"

ABatteryMan_GameMode::ABatteryMan_GameMode()
{
    this->PrimaryActorTick.bCanEverTick = true;
}

void ABatteryMan_GameMode::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle handle;
    GetWorldTimerManager().SetTimer(handle, this, &ABatteryMan_GameMode::SpawnPlayerRecharge, FMath::RandRange(2.0f, 5.0f), true);
    
}

void ABatteryMan_GameMode::Tick(float DeltaTme)
{
    Super::Tick(DeltaTme);
}

void ABatteryMan_GameMode::SpawnPlayerRecharge()
{
    float randX = FMath::RandRange(this->SpawnXMaximum, this->SpawnXMinimum);
    float randY = FMath::RandRange(this->SpawnYMaximum, this->SpawnYMinimum);

    FVector spawnPosition = FVector(randX, randY, this->spawnZ);
    GetWorld()->SpawnActor(this->PlayerRecharge, &spawnPosition, &FRotator::ZeroRotator);
}
