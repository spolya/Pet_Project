// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyPetAnimInstance.h"
#include "Characters/My_Pet_Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyPetAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PetCharacter = Cast<AMy_Pet_Character>(TryGetPawnOwner());
}

void UMyPetAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (PetCharacter == nullptr) return;

	FVector Velocity = PetCharacter->GetVelocity();
	Speed = Velocity.Size();

	bIsAir = PetCharacter->GetCharacterMovement()->IsFalling();
}
