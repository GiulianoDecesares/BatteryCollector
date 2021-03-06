// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryMan_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BatteryMan.h"
#include "Blueprint/UserWidget.h"

ABatteryMan_GameMode::ABatteryMan_GameMode()
{
    this->PrimaryActorTick.bCanEverTick = true;
    this->powerDecayRate = 0.05f;
}

void ABatteryMan_GameMode::BeginPlay()
{
    Super::BeginPlay();

    if (this->HUDWidgetClass != nullptr)
    {
        this->currentWidget = CreateWidget<UUserWidget>(this->GetWorld(), this->HUDWidgetClass);

        if (this->currentWidget != nullptr)
        {
            this->currentWidget->AddToViewport();
        }
    }

    this->currentCharacter = Cast<ABatteryMan>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ABatteryMan_GameMode::Tick(float DeltaTme)
{
    Super::Tick(DeltaTme);

    if (this->currentCharacter != nullptr && this->currentCharacter->GetCurrentPower() > 0.0f)
    {
        this->currentCharacter->UpdateCurrentPower(- DeltaTme * this->powerDecayRate * this->currentCharacter->GetInitialPower());
    }
}
  