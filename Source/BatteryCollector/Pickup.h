// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
private:
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = true))
    class UStaticMeshComponent* pickupMesh;

protected:
	bool isActive;

protected:
	virtual void BeginPlay() override;
	
public:	
	APickup();
	
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UStaticMeshComponent* GetMesh() const;

	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive() const;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool state);

	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();
	virtual void WasCollected_Implementation();
};
