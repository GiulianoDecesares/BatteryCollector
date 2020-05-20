// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan.h"

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

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
	this->power = 80.0f;
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

void ABatteryMan::OnBeginOverlap(UPrimitiveComponent* hitComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool fromSweep, const FHitResult& sweepResult)
{
	if (otherActor->ActorHasTag("Recharge"))
	{
		this->power += 10.0f;

		if (this->power > 100.0f)
		{
			this->power = 100.0f;
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Current power is: %f"), this->power);

		otherActor->Destroy();
	}
}

void ABatteryMan::BeginPlay()
{
	Super::BeginPlay();
	
	this->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABatteryMan::OnBeginOverlap);

	if (this->powerWidgetClass != nullptr)
	{
		this->powerWidget = CreateWidget(GetWorld(), this->powerWidgetClass);

		if (this->powerWidget != nullptr)
		{
			this->powerWidget->AddToViewport();
		}
	}
}

void ABatteryMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABatteryMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABatteryMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABatteryMan::MoveRight);
}

