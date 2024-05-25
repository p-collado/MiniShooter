#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ShooterCharacterMovement.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINISHOOTER_API UShooterCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UShooterCharacterMovement();
	virtual float GetMaxSpeed() const override;

protected:
	virtual void BeginPlay() override;
};
