﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ShooterAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class MINISHOOTER_API UShooterAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static UShooterAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
