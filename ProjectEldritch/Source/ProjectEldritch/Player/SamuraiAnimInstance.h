// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "./Characters/SamuraiPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SamuraiAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTELDRITCH_API USamuraiAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	USamuraiAnimInstance();

	virtual void NativeInitializeAnimation();

	UFUNCTION(BlueprintCallable, Category = SamuraiAnimation)
		void BlueprintUpdateProperties(float DeltaTime);


	ASamuraiPlayer* Player = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SamuraiAnimation)
		float Speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SamuraiAnimation)
		float Direction = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SamuraiAnimation)
		FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SamuraiAnimation)
		FRotator BaseRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SamuraiAnimation)
		uint8 bIsJumping : 1;
	
};
