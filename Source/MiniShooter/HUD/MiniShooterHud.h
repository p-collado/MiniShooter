// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MiniShooterHud.generated.h"

/**
 * 
 */

class UShooterHUD;
class ACharacterBase;

UCLASS()
class MINISHOOTER_API AMiniShooterHud : public AHUD
{
	GENERATED_BODY()

	static void ShowHUDOf(UUserWidget* MenuToShow);
	static void RemoveMenu(UUserWidget* MenuToRemove);

public:

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


	//Delegates functions
	UFUNCTION()
	void OnHealthChanged(const float Value);

protected:

	virtual void BeginPlay() override;
	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DeathMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PlayerHUDClass;

	UPROPERTY(VisibleDefaultsOnly)
	UShooterHUD* PlayerHUD;

	UPROPERTY(VisibleDefaultsOnly)
	UShooterMainMenu* PauseMenu;

	UPROPERTY(VisibleDefaultsOnly)
	UUserWidget* DeathMenu;

	UPROPERTY(VisibleDefaultsOnly)
	ACharacterBase* CharacterRef;
};