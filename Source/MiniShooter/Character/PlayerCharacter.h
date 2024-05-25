#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"

//Forward Declarations
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UAIPerceptionStimuliSourceComponent;
class UInputMappingContext;
struct FOnAttributeChangeData;
class UGameplayAbility;
struct FInputActionValue;

UCLASS()
class MINISHOOTER_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

	//AI
	void SetupStimulusSource();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:

	//Begin Combat Interface
	virtual FVector GetSocketLocation_Implementation() override;
	virtual FVector GetTargetDirection_Implementation() override;
	//End Combat Interface
	
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//AI Stimulus Source
	UPROPERTY(VisibleAnywhere)
	UAIPerceptionStimuliSourceComponent* StimuliSource;

	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetCamera() const { return FollowCamera; }

	virtual void PossessedBy(AController* NewController) override;
	
};
