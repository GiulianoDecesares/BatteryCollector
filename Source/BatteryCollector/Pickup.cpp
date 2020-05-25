// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create static mesh
	this->pickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	this->RootComponent = this->pickupMesh;

	// Default activated
	this->isActive = true;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* APickup::GetMesh() const
{
	return this->pickupMesh;
}

bool APickup::IsActive() const
{
	return this->isActive;
}

void APickup::SetActive(const bool state)
{
	this->isActive = state;
}

void APickup::WasCollected_Implementation()
{
	UE_LOG(LogClass, Log, TEXT("%s collected"), *this->GetName());
}

