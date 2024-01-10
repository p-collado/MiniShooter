// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ShooterPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MiniShooterInputComponent.h"
#include "Components/ShooterCharacterMovement.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "MiniShooter/Character/Components/GASEnhancedInputCmp.h"
#include "MiniShooter/GAS/MiniShooterAbilitySystemComponent.h"
#include "MiniShooter/GAS/MiniShooterAttributeSet.h"
#include "MiniShooter/HUD/MiniShooterHud.h"


int FAbilityInputBinding::IDCounter = 0;

void ACharacterBase::InputPressed(UInputAction* InputAction)
{
	//UAbilitySystemComponent* AbilityComponent = GetAbilitySystemComponent();
	//const FGameplayAbilitySpecHandle& aux = MapAbilityBindings.Find(InputAction)->Ability;
	//
	// if (!AbilityComponent->FindAbilitySpecFromHandle(aux)->IsActive())
	// {
	// 	AbilityComponent->TryActivateAbility(MapAbilityBindings.Find(InputAction)->Ability);
	// }
	
	 UAbilitySystemComponent* AbilityComponent = GetAbilitySystemComponent();
	const FAbilityInputBinding* Binding = MapAbilityBindings.Find(InputAction);
	if (Binding)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(Binding->InputID);
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("Accion presionada"));
}

void ACharacterBase::InputHeld(UInputAction* InputAction)
{

}

void ACharacterBase::InputReleased(UInputAction* InputAction)
{
	UAbilitySystemComponent* AbilityComponent = GetAbilitySystemComponent();
	const FAbilityInputBinding* Binding = MapAbilityBindings.Find(InputAction);
	if (Binding)
	{
		AbilitySystemComponent->AbilityLocalInputReleased(Binding->InputID);
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("Accion soltada"));
}

void ACharacterBase::InitializeInputs()
{
	UMiniShooterInputComponent* MyInputComponent = CastChecked<UMiniShooterInputComponent>(InputComponent);
	
	if (ensureMsgf(MyInputComponent, TEXT("Project must use EnhancedInputComponent to support InputManagerComponent")))
	{
		//Native Action Inputs
		MyInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterBase::Move);
		MyInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterBase::LookAt);
		MyInputComponent->BindAction(PauseMenuAction, ETriggerEvent::Started, Cast<AShooterPlayerController>(Controller), &AShooterPlayerController::Pause);

		const APlayerController* PlayerController = GetController<APlayerController>();

		const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		if (!LocalPlayer)
		{
			return;
		}

		if (InputMappingContext)
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMappingContext, InputPriority);
		}

		for (FGameAbilityMapping& AbilityMapping : InputsHabilidades)
		{
			FAbilityInputBinding NewBinding = FAbilityInputBinding();
			FGameplayAbilitySpec AbilitySpec(AbilityMapping.AbilityType.Get());
			AbilitySpec.InputID = NewBinding.SetIDInput();
			NewBinding.Ability = AbilitySystemComponent->GiveAbility(AbilitySpec);
			NewBinding.InputID = AbilitySpec.InputID;
		
			if (!AbilityMapping.InputAction.IsNull())
			{
				UInputAction* Action = AbilityMapping.InputAction.LoadSynchronous();
				NewBinding.OnPressedHandle = MyInputComponent->BindAction(Action, ETriggerEvent::Started, this, &ACharacterBase::InputPressed, Action).GetHandle();
				NewBinding.OnHeldHandle = MyInputComponent->BindAction(Action, ETriggerEvent::Ongoing, this, &ACharacterBase::InputHeld, Action).GetHandle();
				NewBinding.OnReleasedHandle = MyInputComponent->BindAction(Action, ETriggerEvent::Completed, this, &ACharacterBase::InputReleased, Action).GetHandle();
				MapAbilityBindings.Add(Action, NewBinding);
			}
		}
	}
}

// Sets default values
ACharacterBase::ACharacterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UShooterCharacterMovement>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GAS
	AbilitySystemComponent = CreateDefaultSubobject<UMiniShooterAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UMiniShooterAttributeSet>(TEXT("AttributeCharacterList"));

	//Capsule configuration
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetRelativeLocation(FVector(100,-3,96));


	//InputManager
	//GasEnhanceInputComp = CreateDefaultSubobject<UGASEnhancedInputCmp>(TEXT("InputManager"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		FOnGameplayAttributeValueChange& Delegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UMiniShooterAttributeSet::GetHealthAttribute());
		Delegate.AddUObject(this, &ACharacterBase::OnHealthChanged);

		if (InitTable)
		{
			AttributeSet->InitFromMetaDataTable(InitTable);

			
			//Dos casts, me china...
			const AShooterPlayerController* LocalPLayerController =  Cast<AShooterPlayerController>(GetController());
			const AMiniShooterHud* LocalHud =  Cast<AMiniShooterHud>(LocalPLayerController->MyHUD.Get());
			
			LocalHud->InitPlayerHUDValues();
		}
	}

	//if (IsValid(AbilitySystemComponent))
	//{
	//	AttributeSet = AbilitySystemComponent->GetSet<UMiniShooterAttributeSet>();
	//}
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(10, 0,FColor::Red, FString::Printf(TEXT("Health: %s"), *HUDWidget->CurrentValueHealthText->GetText().ToString()));
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InitializeInputs();

	//GasEnhanceInputComp->InitializeInputs(PlayerInputComponent);
}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		//AbilitySystemComponent->BindToInputComponent(InputComponent);
	}
}

void ACharacterBase::OnHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChange.Broadcast(Data.NewValue);
}

void ACharacterBase::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACharacterBase::LookAt(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

