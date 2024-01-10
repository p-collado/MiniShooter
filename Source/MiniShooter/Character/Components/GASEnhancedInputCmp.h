// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "GameplayAbilitySpec.h"
#include "GASEnhancedInputCmp.generated.h"

class UEnhancedInputComponent;
class UInputMappingContext;
class UInputAction;
class UGameplayAbility;

// USTRUCT(BlueprintType)
// struct FGameAbilityMapping
// {
// 	GENERATED_USTRUCT_BODY()
//
// 	// Type of ability to grant
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly)
// 	TSubclassOf<UGameplayAbility> AbilityType;
//
// 	// Input action to bind the ability to, if any (can be left unset)
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly)
// 	TSoftObjectPtr<UInputAction> InputAction;
// };

// USTRUCT(BlueprintType)
// struct FAbilityInputBinding
// {
// 	GENERATED_USTRUCT_BODY()
//
// 	int32  InputID = 0;
// 	uint32 OnPressedHandle = 0;
// 	uint32 OnReleasedHandle = 0;
// 	uint32 OnHeldHandle = 0;
// 	FGameplayAbilitySpecHandle Ability;
//
// };

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINISHOOTER_API UGASEnhancedInputCmp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGASEnhancedInputCmp();

	void InitializeInputs(UInputComponent* PlayerInputComponent);

	/** Input mapping to add to the input system */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputMappingContext* InputMappingContext = nullptr;

	/** Priority to bind mapping context with */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Controls")
	int InputPriority = 0;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Controls")
	// TArray<FGameAbilityMapping> InputsHabilidades;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** LookAt Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseMenuAction;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Native/BP Event to set up player controls */
	UFUNCTION(Category = "Player Controls")
	void SetupPlayerControls();

	UFUNCTION()
	UAbilitySystemComponent* GetAbilitySystemComponent();

	void SetupInputComponent();

	/** The bound input component. */
	UPROPERTY(transient)
	UEnhancedInputComponent* InputComponent;
	
	/*FUNCTIONS FOR THE INPUT ACTIONS*/
	void Move(const FInputActionValue& Value);
	void LookAt(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void ChangeAbilityInput(UInputAction* InputAction, TSubclassOf<UGameplayAbility>AbilityToChange);
	
private:
	void InputPressed(UInputAction* InputAction);
	void InputReleased(UInputAction* InputAction);
	void InputHeld(UInputAction* InputAction);

	//TMap<UInputAction*, FAbilityInputBinding> MapAbilityBindings;

	UPROPERTY()
	APawn* OwnerPawn;
};
