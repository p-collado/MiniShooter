// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "MiniShooter/Character/Components/MiniShooterInputComponent.h"
#include "MiniShooter/GAS/MiniShooterAbilitySystemComponent.h"
#include "MiniShooter/HUD/MiniShooterHud.h"

AShooterPlayerController::AShooterPlayerController()
{
	
}

void AShooterPlayerController::Pause()
{
	Super::Pause();
	Cast<AMiniShooterHud>(GetHUD())->PauseGame();
}

void AShooterPlayerController::OpenInventory(const FInputActionValue& InputActionValue)
{
	
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(MappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem)
	Subsystem->AddMappingContext(MappingContext, 0);
	
}

void AShooterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UMiniShooterInputComponent* EnhancedInputComponent = CastChecked<UMiniShooterInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::Move);
	EnhancedInputComponent->BindAction(PauseMenuAction, ETriggerEvent::Started, this, &AShooterPlayerController::Pause);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::LookAt);
	EnhancedInputComponent->BindAction(TabAction, ETriggerEvent::Started, this, &AShooterPlayerController::OpenInventory);
	
}

UMiniShooterAbilitySystemComponent* AShooterPlayerController::GetASC()
{
	if (MiniShooterAbilitySystemComponent == nullptr)
	{
		MiniShooterAbilitySystemComponent = Cast<UMiniShooterAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}

	return MiniShooterAbilitySystemComponent;
}

void AShooterPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// input is a Vector2D
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	
	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	APawn* ControlledPawn = GetPawn<APawn>();
	if (ControlledPawn)
	{
		// add movement 
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AShooterPlayerController::LookAt(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	APawn* ControlledPawn = GetPawn<APawn>();
	if (ControlledPawn)
	{
		// add yaw and pitch input to controller
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AShooterPlayerController::InputPressed(FGameplayTag InputTag)
{
	
}

void AShooterPlayerController::InputHeld(FGameplayTag InputTag)
{
	if(GetASC())
	{
		GetASC()->AbilityInputTagReleased(InputTag);
	}
}

void AShooterPlayerController::InputReleased(FGameplayTag InputTag)
{
	if(GetASC())
	{
		GetASC()->AbilityInputTagHeld(InputTag);
	}
}
