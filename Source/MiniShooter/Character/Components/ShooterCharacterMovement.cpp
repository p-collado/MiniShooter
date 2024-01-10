// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterMovement.h"
#include "MiniShooter/Character/CharacterBase.h"
#include "MiniShooter/GAS/MiniShooterAttributeSet.h"

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
	ACharacterBase* CharRef = Cast<ACharacterBase>(GetOwner());

	if (!CharRef)
	{
		return Super::GetMaxSpeed();
	}

	const UMiniShooterAttributeSet* Set = CharRef->GetAttributeSet();
	
	if (Set && IsCrouching())
	{
		return Set->GetCrouchSpeed();
	}
	
	if (Set)
	{
		return Set->GetMovSpeed();
	}

	return 0.0f;
}


// Called every frame
void UShooterCharacterMovement::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

