// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemGunBase.h"


// Sets default values
AItemGunBase::AItemGunBase()
	:Damage(0.f)
	,MaxAmmo(0)
	,CurrentAmmo(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComp");
	RootComponent = SkeletalMeshComponent;
}

// Called when the game starts or when spawned
void AItemGunBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

