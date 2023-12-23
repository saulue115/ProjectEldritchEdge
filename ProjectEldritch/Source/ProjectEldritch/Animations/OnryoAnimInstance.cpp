// Fill out your copyright notice in the Description page of Project Settings.


#include "OnryoAnimInstance.h"

UOnryoAnimInstance::UOnryoAnimInstance()
{
}

void UOnryoAnimInstance::NativeInitializeAnimation()
{
	if (Enemy == nullptr)
	{
		Enemy = Cast<AOnryoSamuraiEnemy>(TryGetPawnOwner());
	}
}

void UOnryoAnimInstance::BlueprintUpdateProperties(float DeltaTime)
{
	Enemy = Cast<AOnryoSamuraiEnemy>(TryGetPawnOwner());

	if (!Enemy) return;

	Velocity = Enemy->GetVelocity();
	Speed = Velocity.Size();

	bIsJumping = Enemy->GetCharacterMovement()->IsFalling();

	bHasSwordEquipped = Enemy->bSwordEquipped;

	//bIsInDefenseMode = Enemy->IsInDefense();

	Direction = CalculateDirection(Velocity, BaseRotation);
}
