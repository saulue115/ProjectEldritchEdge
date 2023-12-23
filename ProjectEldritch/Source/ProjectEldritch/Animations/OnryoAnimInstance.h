// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Enemy/Players/OnryoSamuraiEnemy.h"
#include "OnryoAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTELDRITCH_API UOnryoAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UOnryoAnimInstance();
	

	virtual void NativeInitializeAnimation();

	UFUNCTION(BlueprintCallable, Category = SamuraiAnimation)
		void BlueprintUpdateProperties(float DeltaTime);


	AOnryoSamuraiEnemy* Enemy = nullptr;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SamuraiAnimation)
		uint8 bHasSwordEquipped : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SamuraiAnimation)
		uint8 bIsInDefenseMode : 1;

};
