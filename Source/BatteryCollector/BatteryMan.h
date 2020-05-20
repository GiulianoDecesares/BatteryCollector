// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BatteryMan.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ABatteryMan : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABatteryMan();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FollowCamera;

	void MoveForward(float value);
	void MoveRight(float value);

	bool isDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float power;

	UPROPERTY(EditAnywhere)
	float powerThreshold;

	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<UUserWidget> powerWidgetClass;

	UUserWidget* powerWidget;

	UFUNCTION()
	void OnBeginOverlap(
		class UPrimitiveComponent* hitComponent,
		class AActor* otherActor,
		class UPrimitiveComponent* otherComponent,
		int32 otherBodyIndex, bool fromSweep, const FHitResult& sweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
