// Christopher Davis - All rghts reserved

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class THEHOLLOWTOMB_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Movement input handlers */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump();
	void StopJump();
	void StartSprint();
	void StopSprint();
	void ToggleCrouch();
	void EnableStaminaRecovery();

	/*** Mapping context and action */
	UPROPERTY(EditDefaultsOnly, Category = "Input");
	TObjectPtr<UInputMappingContext> DefaultMappingContect;

	UPROPERTY(EditDefaultsOnly, Category = "Input");
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input");
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SprintAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> CrouchAction;

	/** Spring arm that positions the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

private:
	float WalkSpeed;
	float SprintSpeed;
	bool bIsSprinting;
	bool bCanRecoverStamina = true;

	FTimerHandle StaminaRecoveryTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float CurrentStamina = 100.f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float StaminaDrainRate = 25.f; // per second

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float StaminaRecoveryRate = 15.f; // per second
	
	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float StaminaRecoveryDelay = 10.0f;

};
