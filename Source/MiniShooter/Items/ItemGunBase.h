// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemGunBase.generated.h"

class UMeshComponent;

UCLASS()
class MINISHOOTER_API AItemGunBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemGunBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmmo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
