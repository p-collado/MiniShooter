// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAssetManager.h"

#include "FShooterGameplayTags.h"

UShooterAssetManager& UShooterAssetManager::Get()
{
	check(GEngine);
	UShooterAssetManager* AssetManager = Cast<UShooterAssetManager>(GEngine->AssetManager);
	return *AssetManager;
}

void UShooterAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FShooterGameplayTags::InitializeNativeGameplayTags();
}
