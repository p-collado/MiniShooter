// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */

class AMiniShooterHud;


UCLASS()
class MINISHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AShooterPlayerController();

	UPROPERTY(VisibleDefaultsOnly) //Sin uso de momento
	AMiniShooterHud* MainHud;
	
	virtual void Pause() override;
	
protected:
	virtual void BeginPlay() override;
};
