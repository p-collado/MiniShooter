// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PostingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINISHOOTER_API UPostingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPostingComponent();

	FVector GetPostingPoint() const { return PostingPoint; }
	FVector GetDirection() const { return Direction; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Watch Point Config");
	FVector PostingPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Watch Point Config", meta=(ClampMin = 0.f, ClampMax = 1.f));
	FVector Direction { 1.f, 0.f, 0.f };
	
};
