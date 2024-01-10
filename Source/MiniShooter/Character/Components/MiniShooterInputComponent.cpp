// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniShooterInputComponent.h"


void UMiniShooterInputComponent::InitInputBinds()
{
	
}

// Sets default values for this component's properties
UMiniShooterInputComponent::UMiniShooterInputComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMiniShooterInputComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMiniShooterInputComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMiniShooterInputComponent::OnRegister()
{
	Super::OnRegister();
	
}

