// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSamuraiPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerInput.h"
#include "SamuraiPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTELDRITCH_API ASamuraiPlayer : public ABaseSamuraiPlayer
{
	GENERATED_BODY()

public:

	ASamuraiPlayer(const FObjectInitializer& ObjectInitializer);

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;
	

public:


	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);


	UFUNCTION()
		void LookUp(float Rate);

	UFUNCTION()
		void Turn(float Rate);


};
