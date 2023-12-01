// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSamuraiPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

protected:

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay();
	

public:


	UFUNCTION()
		void Move(const FInputActionValue& Value);

	

	UFUNCTION()
		void Look(const FInputActionValue& Value);

	


};
