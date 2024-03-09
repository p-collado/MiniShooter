// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterMainMenu.generated.h"

class AMiniShooterHud;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class MINISHOOTER_API UShooterMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void SetHudOwner(AMiniShooterHud* owner) {ShooterHud = owner;}
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ResumeText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* QuitText;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	AMiniShooterHud* ShooterHud;
};