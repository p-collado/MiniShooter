#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "MiniShooter/Input/MiniShooterInputConfig.h"
#include "MiniShooterInputComponent.generated.h"

class UMiniShooterInputConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINISHOOTER_API UMiniShooterInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityInputActions(const UMiniShooterInputConfig* InputConfig, UserClass* Object, PressedFuncType PressFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UMiniShooterInputComponent::BindAbilityInputActions(const UMiniShooterInputConfig* InputConfig, UserClass* Object, PressedFuncType PressFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig)
	for (const FMiniShooterInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressFunc, Action.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}

