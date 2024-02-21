// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
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

UCLASS()
class MINISHOOTER_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
	void InitializeInitAttributes();

	//AI
	void SetupStimulusSource();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category="HUD")
	UShooterHUD* HUDWidget;

public:

	//Begin Combat Interface
	virtual FVector GetSocketLocation_Implementation() override;
	virtual FVector GetForwardVector_Implementation() override;
	//End Combat Interface
	
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//AI Stimulus Source
	UPROPERTY()
	UAIPerceptionStimuliSourceComponent* StimuliSource;

	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetCamera() const { return FollowCamera; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void PossessedBy(AController* NewController) override;
	
};
