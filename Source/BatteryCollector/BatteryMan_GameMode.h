// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BatteryMan_GameMode.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryMan_GameMode : public AGameMode
{
private:
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = true))
	float powerDecayRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power", meta = (BlueprintProtected = true))
	float powerToWin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = true))
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY()
	UUserWidget* currentWidget;

public:
	ABatteryMan_GameMode();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTme) override;

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;
};
