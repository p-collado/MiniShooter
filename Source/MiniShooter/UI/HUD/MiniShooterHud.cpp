// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniShooterHud.h"

#include "Blueprint/UserWidget.h"
#include "MiniShooter/Player/ShooterPlayerController.h"
#include "MiniShooter/UI/Controllers/OverlayWidgetController.h"
#include "MiniShooter/UI/Widgets/ShooterUserWidget.h"

void AMiniShooterHud::PauseGame()
{
	if(GetOwningPlayerController()->IsPaused())
	{
		PauseMenu = Cast<UShooterUserWidget>(CreateWidget(GetOwningPlayerController(), PauseMenuClass));
		PauseMenu->AddToViewport();
		GetOwningPlayerController()->SetShowMouseCursor(true);
		FInputModeGameAndUI InputModeUIOnly;
		InputModeUIOnly.SetWidgetToFocus(PauseMenu->TakeWidget());
		GetOwningPlayerController()->SetInputMode(InputModeUIOnly);
	}
	else
	{
		PauseMenu->RemoveFromParent();
		PauseMenu = nullptr;
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

UOverlayWidgetController* AMiniShooterHud::GetOverlayWidgetController(const FWidgetControllerParams WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();

		return OverlayWidgetController;
	}

	return OverlayWidgetController;
}

void AMiniShooterHud::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC,
                                  UAttributeSet* ATS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class unitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Controller Widget Class unitialized, please fill out BP_AuraHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	PlayerHUD = Cast<UShooterUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, ATS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	PlayerHUD->SetWidgetController(WidgetController);
	WidgetController->BroadCastInitialValues();

	Widget->AddToViewport();
}
