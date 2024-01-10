// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "MiniShooter/HUD/MiniShooterHud.h"

AShooterPlayerController::AShooterPlayerController()
{
	
}

void AShooterPlayerController::Pause()
{
	Super::Pause();
	Cast<AMiniShooterHud>(GetHUD())->PauseGame();
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
}


