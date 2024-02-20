// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */

class UMiniShooterAbilitySystemComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class AMiniShooterHud;


UCLASS()
class MINISHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AShooterPlayerController();
	
	virtual void Pause() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> MappingContext;
	
	UPROPERTY(EditAnywhere, Category= "Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category= "Input")
	TObjectPtr<UInputAction> TabAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> PauseMenuAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY()
	TObjectPtr<UMiniShooterAbilitySystemComponent> MiniShooterAbilitySystemComponent;

	UMiniShooterAbilitySystemComponent* GetASC();

	//Input
	void OpenInventory(const FInputActionValue& InputActionValue);
	void Move(const FInputActionValue& InputActionValue);
	void LookAt(const FInputActionValue& Value);
	void InputPressed(FGameplayTag InputTag);
	void InputHeld(FGameplayTag InputTag);
	void InputReleased(FGameplayTag InputTag);
	
};
