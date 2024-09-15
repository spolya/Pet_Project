// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyPetAnimInstance.generated.h"

class AMy_Pet_Character;
/**
 * 
 */
UCLASS()
class MY_PET_PROJECT_API UMyPetAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Reference")
	AMy_Pet_Character* PetCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsAir;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsInputAccelerating;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsSprinting;
};
