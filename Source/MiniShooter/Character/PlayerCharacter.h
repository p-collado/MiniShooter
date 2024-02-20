// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameplayAbilitySpecHandle.h"
#include "PlayerCharacter.generated.h"

//Forward Declarations
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UShooterHUD;
class UAIPerceptionStimuliSourceComponent;
class UInputMappingContext;
struct FOnAttributeChangeData;
class UGameplayAbility;
struct FInputActionValue;


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

UCLASS()
class MINISHOOTER_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
	void InitializeInitAttributes();

	//AI
	void SetupStimulusSource();

	UPROPERTY()
	TMap<UInputAction*, FAbilityInputBinding> MapAbilityBindings;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category="HUD")
	UShooterHUD* HUDWidget;

public:
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//AI Stimulus Source
	UPROPERTY()
	UAIPerceptionStimuliSourceComponent* StimuliSource;
	
	/** Input mapping to add to the input system */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputMappingContext* InputMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Controls")
	TArray<FGameAbilityMapping> InputsHabilidades;

	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetCamera() const { return FollowCamera; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void PossessedBy(AController* NewController) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
