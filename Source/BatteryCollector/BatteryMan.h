// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BatteryMan.generated.h"

class USphereComponent;
class UPrimitiveComponent;
class AActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInteractionHint, FString, HintName, bool, ShowHint);

UCLASS()
class BATTERYCOLLECTOR_API ABatteryMan : public ACharacter
{
private:
	GENERATED_BODY()

	float movementSpeedMultiplier;

	float drainRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "", meta = (AllowPrivateAccess = true))
	USphereComponent* collectionSphere;

	UPROPERTY(VisibleAnywhere, Category = "Power")
	float currentPower;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = true))
	float initialPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = true))
    float maxPower;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = true))
	float baseSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = true))
    float runSpeedMultiplier;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FInteractionHint InteractionHintEvent;

	bool isDead;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Pickups")
	void Collect();

public:
	ABatteryMan();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);

	void Run();
	void StopRunning();
	void RestartGame();

	FORCEINLINE USphereComponent* GetCollectionSphere() const;

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetInitialPower() const;

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetCurrentPower() const;

	UFUNCTION(BlueprintPure, Category = "Power")
    float GetMaxPower() const;
	
	/**
	 * \brief Updates the current character power
	 * \param delta Amount to use in the update, could be positive or negative
	 */
	UFUNCTION(BlueprintCallable, Category = "Power")
	void UpdateCurrentPower(float delta);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* other, UPrimitiveComponent* otherComponent, int32 otherBobyIndex, bool fromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* overlappedComponent, AActor* other, UPrimitiveComponent* otherComponent, int32 otherBodyIndex);
};
