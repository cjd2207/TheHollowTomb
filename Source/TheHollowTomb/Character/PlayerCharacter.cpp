// Christopher Davis - All rghts reserved


#include "Character/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create and set up Spring Arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	
	CameraBoom->TargetArmLength = 300.0f; // Distance behind character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on controller

	// Create and attach Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	// Character movement settings
	bUseControllerRotationYaw = true;
	//GetCharacterMovement()->bOrientRotationToMovement = true;

	WalkSpeed = 600.f;
	SprintSpeed = 900.f;
}
 
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSprinting && CurrentStamina > 0.f)
	{
		CurrentStamina -= StaminaDrainRate * DeltaTime;
		if (CurrentStamina <= 0.f)
		{
			CurrentStamina = 0.f;
			StopSprint(); // Automatically stop sprinting
		}
	}
	else if(bCanRecoverStamina)
	{
		CurrentStamina = FMath::Clamp(CurrentStamina + StaminaRecoveryRate * DeltaTime, 0.f, MaxStamina);
	}

	if (GEngine)
	{
		FString StaminaString = FString::Printf(TEXT("Stamina: %.1f"), CurrentStamina);
		GEngine->AddOnScreenDebugMessage(
			1,				// Key (1 = overwrite previous)
			0.f,			// Time on screen (0 = this frame only)
			FColor::Green,  // Color
			StaminaString
		);
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (DefaultMappingContect)
			{
				Subsystem->AddMappingContext(DefaultMappingContect, 0);
			}
		}
	}

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction,  ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInput->BindAction(LookAction,  ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInput->BindAction(JumpAction,  ETriggerEvent::Started,   this, &APlayerCharacter::StartJump);
		EnhancedInput->BindAction(JumpAction,  ETriggerEvent::Completed, this, &APlayerCharacter::StopJump);
		EnhancedInput->BindAction(SprintAction,ETriggerEvent::Started,   this, &APlayerCharacter::StartSprint);
		EnhancedInput->BindAction(SprintAction,ETriggerEvent::Completed, this, &APlayerCharacter::StopSprint);
		EnhancedInput->BindAction(CrouchAction,ETriggerEvent::Started,   this, &APlayerCharacter::ToggleCrouch);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();
    if (Controller && MovementVector.SizeSquared() > 0.f)
    {
        const FRotator YawRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

        const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(Forward, MovementVector.Y);
        AddMovementInput(Right, MovementVector.X);
    }
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();
    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(-LookAxisVector.Y);
}

void APlayerCharacter::StartJump()
{
	Jump();
}

void APlayerCharacter::StopJump()
{
	StopJumping();
}

void APlayerCharacter::StartSprint()
{
	if (CurrentStamina > 0.f)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void APlayerCharacter::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// Block recovery and start delay timer
	bCanRecoverStamina = false;

	GetWorldTimerManager().ClearTimer(StaminaRecoveryTimerHandle);
	
	GetWorldTimerManager().SetTimer(
		StaminaRecoveryTimerHandle,
		this,
		&APlayerCharacter::EnableStaminaRecovery,
		StaminaRecoveryDelay,
		false
	);
}

void APlayerCharacter::EnableStaminaRecovery()
{
	bCanRecoverStamina = true;
}

void APlayerCharacter::ToggleCrouch()
{
	if (bIsCrouched)
		UnCrouch();
	else
		Crouch();
}