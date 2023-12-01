// Fill out your copyright notice in the Description page of Project Settings.


#include "SamuraiAnimInstance.h"

USamuraiAnimInstance::USamuraiAnimInstance()
{
}

void USamuraiAnimInstance::NativeInitializeAnimation()
{
	if (Player == nullptr)
	{
		Player = Cast<ASamuraiPlayer>(TryGetPawnOwner());
	}
}

void USamuraiAnimInstance::BlueprintUpdateProperties(float DeltaTime)
{
	Player = Cast<ASamuraiPlayer>(TryGetPawnOwner());

	if (!Player) return;

	Velocity = Player->GetVelocity();
	Speed = Velocity.Size();

	bIsJumping = Player->GetCharacterMovement()->IsFalling();

	Direction = CalculateDirection(Velocity, BaseRotation);
}
