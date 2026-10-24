// Christopher Davis - All rghts reserved

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class THEHOLLOWTOMB_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Movement input handlers */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

protected:
	/*** Mapping context and action */
	UPROPERTY(EditDefaultsOnly, Category = "Input");
	TObjectPtr<UInputMappingContext> DefaultMappingContect;

	UPROPERTY(EditDefaultsOnly, Category = "Input");
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input");
	TObjectPtr<UInputAction> LookAction;
};
