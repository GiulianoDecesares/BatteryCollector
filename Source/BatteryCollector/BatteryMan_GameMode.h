// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BatteryMan_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryMan_GameMode : public AGameMode
{
	GENERATED_BODY()

	ABatteryMan_GameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTme) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> PlayerRecharge;

	float spawnZ = 130.0f;
	
	UPROPERTY(EditAnywhere)
	float SpawnXMinimum;

	UPROPERTY(EditAnywhere)
    float SpawnXMaximum;

	UPROPERTY(EditAnywhere)
    float SpawnYMinimum;

	UPROPERTY(EditAnywhere)
    float SpawnYMaximum;

	void SpawnPlayerRecharge();
};
