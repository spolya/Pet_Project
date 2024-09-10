// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/My_Pet_Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMy_Pet_Character::AMy_Pet_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// создаем камеру и крепим ее к капсуле
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(GetRootComponent());

	// создаем геометрию рук и крепим к камере
	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh"));
	HandsMesh->SetCastShadow(false);
	HandsMesh->SetupAttachment(Camera);

}

void AMy_Pet_Character::SetupInput()
{
	APlayerController* PlayerControl = Cast<APlayerController>(GetController());
	if (PlayerControl)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerControl->GetLocalPlayer());

		if (Subsystem)
		{
			Subsystem->AddMappingContext(PlayerInputMappingContext, 1);
		}
	}
}

void AMy_Pet_Character::IA_MovePlayer(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();
	const FRotator DirRotation(0.0f, GetControlRotation().Yaw, 0.0f);
	if (MoveVector.X != 0.0f)
	{
		const FVector MovementDirection = DirRotation.RotateVector(FVector::RightVector);
		AddMovementInput(MovementDirection, MoveVector.X);
	}
	if (MoveVector.Y != 0.0f)
	{
		const FVector MovementDirection = DirRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(MovementDirection, MoveVector.Y);
	}
}

void AMy_Pet_Character::IA_LookPlayer(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookVector.Y);
	AddControllerYawInput(LookVector.X);
}

// Called when the game starts or when spawned
void AMy_Pet_Character::BeginPlay()
{
	Super::BeginPlay();

}

void AMy_Pet_Character::BindActions(UInputMappingContext* MappingContext)
{
	if (MappingContext)
	{
		const TArray<FEnhancedActionKeyMapping>& Mappings = MappingContext->GetMappings();
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
		if (EnhancedInputComponent)
		{
			TSet<const UInputAction*> UniqueActions;
			for (const FEnhancedActionKeyMapping& Keymapping : Mappings)
			{
				UniqueActions.Add(Keymapping.Action);
			}
			for (const UInputAction* UniqueAction : UniqueActions)
			{
				EnhancedInputComponent->BindAction(UniqueAction, ETriggerEvent::Triggered, this, UniqueAction->GetFName());
			}
		}
	}
}

// Called every frame
void AMy_Pet_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMy_Pet_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->ClearActionEventBindings();
		EnhancedInputComponent->ClearActionValueBindings();
		EnhancedInputComponent->ClearDebugKeyBindings();

		BindActions(PlayerInputMappingContext);
		SetupInput();
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("requires Enhanced Input System to be activated in project settings"));
	}
}

