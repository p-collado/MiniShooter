// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterMainMenu.h"
#include "MiniShooterHud.h"
#include "Components/Button.h"
#include "MiniShooter/Player/ShooterPlayerController.h"

void UShooterMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	QuitButton->OnClicked.AddUniqueDynamic(ShooterHud, &AMiniShooterHud::QuitGame);
	ResumeButton->OnClicked.AddUniqueDynamic(Cast<AShooterPlayerController>(GetOwningPlayer()), &AShooterPlayerController::Pause);
}
