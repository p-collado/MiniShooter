// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MiniShooterHud.generated.h"

class UAttributeSet;
class UShooterMainMenu;
class APlayerCharacter;
class UShooterHUD;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams(){}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* ATS)
		:  PlayerController(PC)
		, PlayerState(PS)
		, AbilitySystemComponent(ASC)
		, AttributeSet(ATS)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature,const float, CharacterHealth);

UCLASS()
class MINISHOOTER_API AMiniShooterHud : public AHUD
{
	GENERATED_BODY()

	static void ShowHUDOf(UUserWidget* MenuToShow);
	static void RemoveMenu(UUserWidget* MenuToRemove);

public:

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnHealthChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnMaxHealthChange;

	void InitPlayerHUDValues() const;

	UFUNCTION(BlueprintCallable)
	void ShowPauseMenu();

	UFUNCTION(BlueprintCallable)
	void ShowDeathMenu();

	UFUNCTION(BlueprintCallable)
	void RemovePauseMenu();

	UFUNCTION(BlueprintCallable)
	void RemoveDeathMenu();

	UFUNCTION(BlueprintCallable)
	void RemoveAllMenus();

	UFUNCTION(BlueprintCallable)
	void CreateMenus();

	UFUNCTION(BlueprintCallable)
	void PauseGame();

	UFUNCTION(BlueprintCallable)
	void QuitGame();

	UFUNCTION(Blueprintable)
	UShooterHUD* GetPlayerHUD() const { return PlayerHUD; }

	UFUNCTION(Blueprintable)
	UShooterMainMenu* GetPauseMenu() const { return PauseMenu; }

	UFUNCTION(Blueprintable)
	UUserWidget* GetDeathMenu() const { return DeathMenu; }
	
	// //Delegates functions
	// UFUNCTION()
	// void OnHealthChanged(const float Value);

	void BroadCastInitialValues();

	void GetPlayerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* ATS);

	void BindCallbackDependencies();

	UPROPERTY()
	FWidgetControllerParams PlayerParams;
	
protected:

	virtual void BeginPlay() override;
	
	//Class pointers
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DeathMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PlayerHUDClass;

	//Widgets Pointers
	UPROPERTY(VisibleDefaultsOnly)
	UShooterHUD* PlayerHUD;

	UPROPERTY(VisibleDefaultsOnly)
	UShooterMainMenu* PauseMenu;

	UPROPERTY(VisibleDefaultsOnly)
	UUserWidget* DeathMenu;
	
	UPROPERTY(VisibleDefaultsOnly)
	APlayerCharacter* CharacterRef;
};