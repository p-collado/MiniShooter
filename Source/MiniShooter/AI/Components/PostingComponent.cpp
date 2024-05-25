// Fill out your copyright notice in the Description page of Project Settings.


#include "PostingComponent.h"

UPostingComponent::UPostingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UPostingComponent::BeginPlay()
{
	Super::BeginPlay();

	PostingPoint = GetOwner()->GetActorLocation();
}
