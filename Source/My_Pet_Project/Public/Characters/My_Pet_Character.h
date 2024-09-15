// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "My_Pet_Character.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class UInputMappingContext;

UCLASS(HideCategories = ("Rendering", "Replication", "Input", "Actor", "ActorTick", "ComponentReplication", "Variable", "LOD", "Cooking",
	"HLOD", "Mobile", "Lighting", "TextureStreaming", "Tags", "Activation", "AssetUserData",
	"Collision", "Physics", "Navigation", "AI", "PlanarReflection", "Sprite", "Optimization", "DetailMode",
	"Volume", "Components"))
class MY_PET_PROJECT_API AMy_Pet_Character : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> HandsMesh;

public:
	// Sets default values for this character's properties
	AMy_Pet_Character();

	UPROPERTY(Category = "Inputs", EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> PlayerInputMappingContext;

protected:
	UFUNCTION()
	void SetupInput();

	// обработчики Input Action должны соответсвовать названиям файлов, особенность биндинга инпутов 
	UFUNCTION()
	void IA_MovePlayer(const FInputActionValue& Value);

	UFUNCTION()
	void IA_LookPlayer(const FInputActionValue& Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BindActions(UInputMappingContext* MappingContext);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
