// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Pickup.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->whereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	this->RootComponent = this->GetWhereToSpawn();

	this->minimumSpawnDelay = 1.0f;
	this->maximumSpawnDelay = 4.5f;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	this->currentSpawnDelay = FMath::FRandRange(this->minimumSpawnDelay, this->maximumSpawnDelay);
	GetWorldTimerManager().SetTimer(this->spawnTimer, this, &ASpawnVolume::SpawnPickup, this->currentSpawnDelay, false);
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBoxComponent* ASpawnVolume::GetWhereToSpawn() const
{
	return this->whereToSpawn;
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	const FVector spawnOrigin = this->GetWhereToSpawn()->Bounds.Origin;
	const FVector spawnExtend = this->GetWhereToSpawn()->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnExtend);
}

void ASpawnVolume::SpawnPickup()
{
	if (this->whatToSpawn != nullptr)
	{
		UWorld* const world = this->GetWorld();
		if (world != nullptr)
		{
			FActorSpawnParameters spawnParameters;
			spawnParameters.Owner = this;
			spawnParameters.Instigator = this->GetInstigator();

			const FVector spawnLocation = this->GetRandomPointInVolume();
			const FRotator spawnRotation = FRotator(FMath::FRand() * 360.0f, FMath::FRand() * 360.0f, FMath::FRand() * 360.0f);

			[[maybe_unused]] APickup* const spawnedPickup = world->SpawnActor<APickup>(this->whatToSpawn, spawnLocation, spawnRotation, spawnParameters);

			this->currentSpawnDelay = FMath::FRandRange(this->minimumSpawnDelay, this->maximumSpawnDelay);
			GetWorldTimerManager().SetTimer(this->spawnTimer, this, &ASpawnVolume::SpawnPickup, this->currentSpawnDelay, false);
		}
	}
}

