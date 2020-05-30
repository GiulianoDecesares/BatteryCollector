// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan.h"


#include "BatteryPickup.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Pickup.h"

ABatteryMan::ABatteryMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    
    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    
    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;
    
    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
    CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
    
    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	this->isDead = false;

	this->collectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionComponent"));
	this->collectionSphere->AttachTo(this->RootComponent);
	this->collectionSphere->SetSphereRadius(200.0f);

	// Bind overlap events
	this->collectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABatteryMan::OnOverlapBegin);
	this->collectionSphere->OnComponentEndOverlap.AddDynamic(this, &ABatteryMan::OnOverlapEnd);

	this->initialPower = 2000.0f;
	this->currentPower = this->initialPower;

	this->speedMultiplier = 0.75f;
	this->baseSpeed = 10.0f;
}

void ABatteryMan::MoveForward(float value)
{
	if (!this->isDead)
	{
		const FRotator rotation = this->Controller->GetControlRotation();
		const FRotator yaw(0, rotation.Yaw, 0);

		// Calculate forward vector
		const FVector direction = FRotationMatrix(yaw).GetUnitAxis(EAxis::X);

		// Move
		this->AddMovementInput(direction, value);
	}
}

void ABatteryMan::MoveRight(float value)
{
	if (!this->isDead)
	{
		const FRotator rotation = this->Controller->GetControlRotation();
		const FRotator yaw(0, rotation.Yaw, 0);

		// Calculate forward vector
		const FVector direction = FRotationMatrix(yaw).GetUnitAxis(EAxis::Y);

		// Move
		this->AddMovementInput(direction, value);
	}
}

/*
void ABatteryMan::Run()
{
	// this->movementSpeedMultiplier = 5.0f;
}

void ABatteryMan::StopRunning()
{
	// this->movementSpeedMultiplier = 1.0f;
}
*/

void ABatteryMan::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

USphereComponent* ABatteryMan::GetCollectionSphere() const
{
	return this->collectionSphere;
}

float ABatteryMan::GetInitialPower() const
{
	return this->initialPower;
}

float ABatteryMan::GetCurrentPower() const
{
	return this->currentPower;
}

void ABatteryMan::UpdateCurrentPower(float delta)
{
	this->currentPower += delta;
	this->GetCharacterMovement()->MaxWalkSpeed = this->baseSpeed + this->speedMultiplier * this->GetCurrentPower();
}

void ABatteryMan::OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* other,
	UPrimitiveComponent* otherComponent, int32 otherBobyIndex, bool fromSweep, const FHitResult& sweepResult)
{
	APickup* const pickup = Cast<APickup>(other);

	if (pickup != nullptr && pickup->NeedsHint())
	{
		this->InteractionHintEvent.Broadcast("Pickup", true);
	}
}

void ABatteryMan::OnOverlapEnd(UPrimitiveComponent* overlappedComponent, AActor* other,
	UPrimitiveComponent* otherComponent, int32 otherBodyIndex)
{
	APickup* const pickup = Cast<APickup>(other);

	if (pickup != nullptr && pickup->NeedsHint())
	{
		this->InteractionHintEvent.Broadcast("Pickup", false);
	}
}

void ABatteryMan::BeginPlay()
{
	Super::BeginPlay();
}

void ABatteryMan::Collect()
{
	TArray<AActor*> collected;
	this->collectionSphere->GetOverlappingActors(collected);

	float collectedPower = 0.0f;

	for (int index = 0; index < collected.Num(); index++)
	{
		APickup* const pickup = Cast<APickup>(collected[index]);

		if (pickup != nullptr && !pickup->IsPendingKill() && pickup->IsActive())
		{
			ABatteryPickup* const batteryPickup = Cast<ABatteryPickup>(collected[index]);

			if (batteryPickup != nullptr)
			{
				collectedPower += batteryPickup->GetPower();
			}			
			
			pickup->WasCollected();
			pickup->SetActive(false);
		}
	}

	if (collectedPower != 0.0f)
	{
		this->UpdateCurrentPower(collectedPower);
	}
}

void ABatteryMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!this->isDead && this->GetCurrentPower() <= 0.0f)
	{
		this->isDead = true;
		this->GetMesh()->SetSimulatePhysics(true);

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABatteryMan::RestartGame, 2.0f, false);
	}
}

void ABatteryMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABatteryMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABatteryMan::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	// PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ABatteryMan::Run);
	// PlayerInputComponent->BindAction("Run", IE_Released, this, &ABatteryMan::StopRunning);
	PlayerInputComponent->BindAction("Collect", IE_Pressed, this, &ABatteryMan::Collect);
}

