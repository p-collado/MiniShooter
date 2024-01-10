// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniShooterHud.h"

#include "EnhancedInputComponent.h"
#include "ShooterHUD.h"
#include "ShooterMainMenu.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MiniShooter/Character/CharacterBase.h"
#include "MiniShooter/Character/ShooterPlayerController.h"
#include "MiniShooter/GAS/MiniShooterAttributeSet.h"

void AMiniShooterHud::ShowHUDOf(UUserWidget* MenuToShow)
{
	MenuToShow->AddToViewport();
}

void AMiniShooterHud::RemoveMenu(UUserWidget* MenuToRemove)
{
	MenuToRemove->RemoveFromParent();
}

void AMiniShooterHud::InitPlayerHUDValues() const
{
	if(PlayerHUD)
	{
		PlayerHUD->LifeBar->SetPercent(100);

		const UMiniShooterAttributeSet* Set = CharacterRef->GetAttributeSet();

		if (Set)
		{
			PlayerHUD->CurrentValueHealthText->SetText(FText::AsNumber(Set->GetHealth()));
			PlayerHUD->MaxValueHealthText->SetText(FText::AsNumber(Set->GetMaxHealth()));
		}
	}
}

void AMiniShooterHud::ShowPauseMenu()
{
	PauseMenu->AddToViewport();
}

void AMiniShooterHud::ShowDeathMenu()
{
	DeathMenu->AddToViewport();
}

void AMiniShooterHud::RemovePauseMenu()
{
	PauseMenu->RemoveFromParent();
}

void AMiniShooterHud::RemoveDeathMenu()
{
	DeathMenu->RemoveFromParent();
}

void AMiniShooterHud::RemoveAllMenus()
{
	PauseMenu->RemoveFromParent();
	DeathMenu->RemoveFromParent();
}

void AMiniShooterHud::CreateMenus()
{
	if (PlayerHUDClass)
	{
		if (PlayerHUD == nullptr)
		{
			PlayerHUD = Cast<UShooterHUD>(CreateWidget(PlayerOwner, PlayerHUDClass, FName("PlayerHUDWidget")));
			PlayerHUD->SetHudOwner(this);
		}
	}

	if (PauseMenuClass)
	{
		if (PauseMenu == nullptr)
		{
			PauseMenu = Cast<UShooterMainMenu>(CreateWidget(PlayerOwner, PauseMenuClass, FName("PauseMenuWidget")));
			PauseMenu->SetHudOwner(this);
		}
	}
}

void AMiniShooterHud::PauseGame()
{
	if(GetOwningPlayerController()->IsPaused())
	{
		PauseMenu->AddToViewport();
		GetOwningPlayerController()->SetShowMouseCursor(true);
		FInputModeGameAndUI InputModeUIOnly;
		InputModeUIOnly.SetWidgetToFocus(PauseMenu->TakeWidget());
		GetOwningPlayerController()->SetInputMode(InputModeUIOnly);
	}
	else
	{
		PauseMenu->RemoveFromParent();
		GetOwningPlayerController()->SetShowMouseCursor(false);
		GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());
	}
}

void AMiniShooterHud::QuitGame()
{

#if WITH_EDITOR
	if (GIsPlayInEditorWorld)
	{
		Cast<AShooterPlayerController>(GetOwningPlayerController())->Pause();
		return;
	}
#endif
	
	FGenericPlatformMisc::RequestExit(false);
}

void AMiniShooterHud::OnHealthChanged(const float Value)
{
	PlayerHUD->LifeBar->SetPercent(Value / CharacterRef->GetAttributeSet()->GetMaxHealth());
	PlayerHUD->CurrentValueHealthText->SetText(FText::AsNumber(Value));
}

void AMiniShooterHud::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = Cast<ACharacterBase>(GetOwningPawn());
	
	CreateMenus();

	APlayerController* PC = Cast<APlayerController>(GetOwningPlayerController());
	
	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PC->InputComponent.Get());
	
	if (PC)
	{
		FHealthChange& Delegate = CharacterRef->OnHealthChange;
		Delegate.AddDynamic(this, &AMiniShooterHud::OnHealthChanged);
		ShowHUDOf(PlayerHUD);
	}
}