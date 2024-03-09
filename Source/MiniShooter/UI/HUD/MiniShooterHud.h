// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MiniShooterHud.generated.h"

class UOverlayWidgetController;
class UShooterUserWidget;
class UAttributeSet;
class UShooterMainMenu;
class APlayerCharacter;
class UShooterHUD;
class UAbilitySystemComponent;
struct FWidgetControllerParams;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature,const float, CharacterHealth);

UCLASS()
class MINISHOOTER_API AMiniShooterHud : public AHUD
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void PauseGame();

	UFUNCTION(BlueprintCallable)
	void QuitGame();

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams WCParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* ATS);

private:
	
	//Class pointers
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UShooterUserWidget> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UShooterUserWidget> OverlayWidgetClass;

	//Class Widget Controller
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	//Widgets Pointers
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UShooterUserWidget> PlayerHUD;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UShooterUserWidget> PauseMenu;

	//Widget Controller Pointers
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
};