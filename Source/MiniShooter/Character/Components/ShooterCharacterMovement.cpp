// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterMovement.h"

#include "MiniShooter/Character/CharacterBase.h"

// Sets default values for this component's properties
UShooterCharacterMovement::UShooterCharacterMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
	// ...
}


// Called when the game starts
void UShooterCharacterMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

float UShooterCharacterMovement::GetMaxSpeed() const
{
	return Cast<ACharacterBase>(GetOwner())->GetSpeed();
}
