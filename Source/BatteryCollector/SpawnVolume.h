// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;
class APickup;

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
private:
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = true))

	float currentSpawnDelay;
    UBoxComponent* whereToSpawn;

protected:
	UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<APickup> whatToSpawn;

	FTimerHandle spawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    float minimumSpawnDelay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    float maximumSpawnDelay;
	
public:	
	ASpawnVolume();
	
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UBoxComponent* GetWhereToSpawn() const;

	UFUNCTION(BlueprintPure, Category = "Spawning")
    FVector GetRandomPointInVolume() const;

private:
	void SpawnPickup();

protected:
	virtual void BeginPlay() override;
};
