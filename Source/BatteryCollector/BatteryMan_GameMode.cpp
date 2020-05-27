// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "BatteryMan.h"
#include "Blueprint/UserWidget.h"
#include "BatteryMan_GameMode.h"

ABatteryMan_GameMode::ABatteryMan_GameMode()
{
    this->PrimaryActorTick.bCanEverTick = true;
    this->powerDecayRate = 0.05f;
}

void ABatteryMan_GameMode::BeginPlay()
{
    Super::BeginPlay();

    ABatteryMan* character = Cast<ABatteryMan>(UGameplayStatics::GetPlayerPawn(this, 0));

    if (character != nullptr)
    {
        this->powerToWin = character->GetInitialPower() * 1.25f;
    }

    if (this->HUDWidgetClass != nullptr)
    {
        this->currentWidget = CreateWidget<UUserWidget>(this->GetWorld(), this->HUDWidgetClass);

        if (this->currentWidget != nullptr)
        {
            this->currentWidget->AddToViewport();
        }
    }
}

void ABatteryMan_GameMode::Tick(float DeltaTme)
{
    Super::Tick(DeltaTme);

    ABatteryMan* character = Cast<ABatteryMan>(UGameplayStatics::GetPlayerPawn(this, 0));

    if (character != nullptr && character->GetCurrentPower() > 0.0f)
    {
        character->UpdateCurrentPower(- DeltaTme * this->powerDecayRate * character->GetInitialPower());
    }
}

float ABatteryMan_GameMode::GetPowerToWin() const
{
    return this->powerToWin;
}
