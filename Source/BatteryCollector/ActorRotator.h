// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/ObjectMacros.h"

#include "ActorRotator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTERYCOLLECTOR_API UActorRotator : public UActorComponent
{
	GENERATED_BODY()

	UStaticMeshComponent* actorMesh;

public:	
	// Sets default values for this component's properties
	UActorRotator();

	UPROPERTY(EditAnywhere)
    float roll;

	UPROPERTY(EditAnywhere)
    float yaw;

	UPROPERTY(EditAnywhere)
    float pitch;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
