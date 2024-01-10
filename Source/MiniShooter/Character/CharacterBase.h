// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "InputActionValue.h"
#include "CharacterBase.generated.h"

//Forward Declarations
struct FOnAttributeChangeData;
class UShooterHUD;
class UAbilitySystemComponent;
class UGameplayAbility;
class UMiniShooterAttributeSet;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FGameAbilityMapping
{
	GENERATED_USTRUCT_BODY()

	// Type of ability to grant
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> AbilityType;

	// Input action to bind the ability to, if any (can be left unset)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UInputAction> InputAction;
};

USTRUCT(BlueprintType)
struct FAbilityInputBinding
{
	GENERATED_USTRUCT_BODY()

	int32  InputID = 0;
	uint32 OnPressedHandle = 0;
	uint32 OnReleasedHandle = 0;
	uint32 OnHeldHandle = 0;
	FGameplayAbilitySpecHandle Ability;

	int32 SetIDInput()
	{
		return IDCounter++;
	}

private:

	static int32 IDCounter;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChange,const float, CharacterHealth);

UCLASS()
class MINISHOOTER_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

private:
	void InputPressed(UInputAction* InputAction);
	void InputHeld(UInputAction* InputAction);
	void InputReleased(UInputAction* InputAction);
	void InitializeInputs();

	UPROPERTY()
	TMap<UInputAction*, FAbilityInputBinding> MapAbilityBindings;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	// UGASEnhancedInputCmp* GasEnhanceInputComp;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category="HUD")
	UShooterHUD* HUDWidget;

public:
	
	/** Input mapping to add to the input system */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputMappingContext* InputMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Controls")
	TArray<FGameAbilityMapping> InputsHabilidades;
	
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** LookAt Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseMenuAction;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FHealthChange OnHealthChange;

	// Sets default values for this character's properties
	ACharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns InputManager subobject **/
	//FORCEINLINE UGASEnhancedInputCmp* GetInputManager() const { return GasEnhanceInputComp; }

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere, Category="GAS")
	UDataTable* InitTable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="GAS")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS")
	UMiniShooterAttributeSet* AttributeSet;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	const UMiniShooterAttributeSet* GetAttributeSet() { return AttributeSet; }
	
	void OnHealthChanged(const FOnAttributeChangeData& Data) const;

	void Move(const FInputActionValue& Value);

	void LookAt(const FInputActionValue& Value);
};
