// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorRotator.h"

// Sets default values for this component's properties
UActorRotator::UActorRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	this->pitch = 0.0f;
	this->yaw = 0.0f;
	this->roll = 0.0f;

	this->actorMesh = nullptr;
}


// Called when the game starts
void UActorRotator::BeginPlay()
{
	Super::BeginPlay();

	// Initialize actor mesh	
	UActorComponent* staticMesh = this->GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass());
	
	if (staticMesh != nullptr)
	{
		this->actorMesh = Cast<UStaticMeshComponent, UActorComponent>(staticMesh);
	}
}


// Called every frame
void UActorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UActorComponent* staticMesh = this->GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass());

	if (this->actorMesh != nullptr)
	{
		this->actorMesh->AddWorldRotation(FQuat(FRotator(this->pitch, this->yaw, this->roll)));
	}
}

