// Fill out your copyright notice in the Description page of Project Settings.


#include "SamuraiMovementComponent.h"

float USamuraiMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();

	const auto SamuraiCharacter = Cast<ASamuraiPlayer>(GetPawnOwner());

	if (!SamuraiCharacter) return 0.0f;



	return SamuraiCharacter && SamuraiCharacter->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
