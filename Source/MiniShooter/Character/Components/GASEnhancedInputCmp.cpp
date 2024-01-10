// Fill out your copyright notice in the Description page of Project Settings.


#include "GASEnhancedInputCmp.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include <AbilitySystemGlobals.h>
#include <MiniShooter/Character/CharacterBase.h>
#include "InputMappingContext.h"

#include "MiniShooter/Character/ShooterPlayerController.h"

// Sets default values for this component's properties
UGASEnhancedInputCmp::UGASEnhancedInputCmp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGASEnhancedInputCmp::InitializeInputs(UInputComponent* PlayerInputComponent)
{
	//APawn* PlayerPawn = Cast<APawn>(GetOwner());
	//InputComponent = CastChecked<UEnhancedInputComponent>(PlayerPawn->InputComponent);
	InputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (ensureMsgf(InputComponent, TEXT("Project must use EnhancedInputComponent to support InputManagerComponent")))
	{
		//Moving
		// InputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UGASEnhancedInputCmp::Move);
		// InputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UGASEnhancedInputCmp::LookAt);
		// InputComponent->BindAction(PauseMenuAction, ETriggerEvent::Started, Cast<AShooterPlayerController>(Cast<APawn>(GetOwner())->GetController()), &AShooterPlayerController::Pause);

		//SetupInputComponent();
		SetupPlayerControls();
	}
}


// Called when the game starts
void UGASEnhancedInputCmp::BeginPlay()
{
	Super::BeginPlay();

	// ...

	OwnerPawn = GetOwner<APawn>();
	
}

void UGASEnhancedInputCmp::SetupPlayerControls()
{
	// for (FGameAbilityMapping& AbilityMapping : InputsHabilidades)
	// {
	// 	FAbilityInputBinding NewBinding = FAbilityInputBinding();
	//
	// 	NewBinding.Ability = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(AbilityMapping.AbilityType.Get()));
	//
	// 	NewBinding.InputID = 0;
	// 	
	// 	if (!AbilityMapping.InputAction.IsNull())
	// 	{
	// 		UInputAction* Action = AbilityMapping.InputAction.LoadSynchronous();
	// 		NewBinding.OnPressedHandle = InputComponent->BindAction(Action, ETriggerEvent::Started, this, &UGASEnhancedInputCmp::InputPressed, Action).GetHandle();
	// 		NewBinding.OnHeldHandle = InputComponent->BindAction(Action, ETriggerEvent::Ongoing, this, &UGASEnhancedInputCmp::InputHeld, Action).GetHandle();
	// 		NewBinding.OnReleasedHandle = InputComponent->BindAction(Action, ETriggerEvent::Completed, this, &UGASEnhancedInputCmp::InputReleased, Action).GetHandle();
	// 		MapAbilityBindings.Add(Action, NewBinding);
	// 	}
	// }
}

UAbilitySystemComponent* UGASEnhancedInputCmp::GetAbilitySystemComponent()
{
	return UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
}

void UGASEnhancedInputCmp::SetupInputComponent()
{
	// APlayerController* PlayerController = Cast<APawn>(GetOwner())->GetController<APlayerController>();
	//
	// const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	// if (!LocalPlayer)
	// {
	// 	return;
	// }
	//
	// if (InputMappingContext)
	// {
	// 	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	// 	Subsystem->ClearAllMappings();
	// 	Subsystem->AddMappingContext(InputMappingContext, InputPriority);
	// }
}


void UGASEnhancedInputCmp::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (OwnerPawn->Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = OwnerPawn->Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		OwnerPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		OwnerPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void UGASEnhancedInputCmp::LookAt(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (OwnerPawn->Controller != nullptr)
	{
		// add yaw and pitch input to controller
		OwnerPawn->AddControllerYawInput(LookAxisVector.X);
		OwnerPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

// Called every frame
void UGASEnhancedInputCmp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGASEnhancedInputCmp::ChangeAbilityInput(UInputAction* InputAction, TSubclassOf<UGameplayAbility> AbilityToChange)
{
	// if (MapAbilityBindings.Contains(InputAction))
	// {
	// 	if (MapAbilityBindings[InputAction].Ability.IsValid())
	// 	{
	// 		FAbilityInputBinding& AbilityInMap = MapAbilityBindings[InputAction];
	// 		GetAbilitySystemComponent()->ClearAbility(AbilityInMap.Ability);
	// 		AbilityInMap.Ability = GetAbilitySystemComponent()->GiveAbility(AbilityToChange);
	// 	}
	// }
}

void UGASEnhancedInputCmp::InputPressed(UInputAction* InputAction)
{
	//Busca en la estructura el id;
	//int id = 0;
	//AbilityComponent->AbilityLocalInputPressed(id);


	// UAbilitySystemComponent* AbilityComponent = GetAbilitySystemComponent();
	// FGameplayAbilitySpecHandle& aux = MapAbilityBindings.Find(InputAction)->Ability;
	//
	// if (!AbilityComponent->FindAbilitySpecFromHandle(aux)->IsActive())
	// {
	// 	AbilityComponent->TryActivateAbility(MapAbilityBindings.Find(InputAction)->Ability);
	// }
	// GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("Accion presionada"));
}

void UGASEnhancedInputCmp::InputReleased(UInputAction* InputAction)
{
	// GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("Accion soltada"));
	//
	// UAbilitySystemComponent* AbilityComponent = GetAbilitySystemComponent();
	// FGameplayAbilitySpecHandle& aux = MapAbilityBindings.Find(InputAction)->Ability;
	// FGameplayAbilitySpec* Spec = AbilityComponent->FindAbilitySpecFromHandle(aux);
	// //AbilityComponent->CancelAbility(Spec->Ability);
}

void UGASEnhancedInputCmp::InputHeld(UInputAction* InputAction)
{

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("Accion Mantenida"));
	UAbilitySystemComponent* AbilityComponent = GetAbilitySystemComponent();
	
}