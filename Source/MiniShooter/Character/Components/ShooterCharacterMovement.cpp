#include "ShooterCharacterMovement.h"

#include "MiniShooter/Character/CharacterBase.h"

UShooterCharacterMovement::UShooterCharacterMovement()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UShooterCharacterMovement::BeginPlay()
{
	Super::BeginPlay();
	
}

float UShooterCharacterMovement::GetMaxSpeed() const
{
	return Cast<ACharacterBase>(GetOwner())->GetSpeed();
}
