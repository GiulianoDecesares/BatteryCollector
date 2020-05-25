// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BatteryMan.generated.h"

class USphereComponent;

UCLASS()
class BATTERYCOLLECTOR_API ABatteryMan : public ACharacter
{
private:
	GENERATED_BODY()

	float movementSpeedMultiplier;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "", meta = (AllowPrivateAccess = true))
	USphereComponent* collectionSphere;

	UPROPERTY(VisibleAnywhere, Category = "Power")
	float currentPower;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float initialPower;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FollowCamera;

	bool isDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float power;

	UPROPERTY(EditAnywhere)
    float powerThreshold;
	
	UPROPERTY(EditAnywhere)
    float runPowerThreshold;

	UPROPERTY(EditAnywhere, Category="HUD")
    TSubclassOf<UUserWidget> powerWidgetClass;

	UUserWidget* powerWidget;

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

	UFUNCTION()
	void OnBeginOverlap(
		class UPrimitiveComponent* hitComponent,
		class AActor* otherActor,
		class UPrimitiveComponent* otherComponent,
		int32 otherBodyIndex, bool fromSweep, const FHitResult& sweepResult);

	void RestartGame();

	FORCEINLINE USphereComponent* GetCollectionSphere() const;

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetInitialPower() const;

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetCurrentPower() const;

	
	/**
	 * \brief Updates the current character power
	 * \param delta Amount to use in the update, could be positive or negative
	 */
	UFUNCTION(BlueprintCallable, Category = "Power")
	void UpdateCurrentPower(float delta);
};
