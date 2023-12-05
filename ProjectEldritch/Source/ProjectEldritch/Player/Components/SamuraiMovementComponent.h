// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Characters/SamuraiPlayer.h"
#include "SamuraiMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTELDRITCH_API USamuraiMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	virtual float GetMaxSpeed() const override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Movement,meta=(ClampMin="1.5",ClampMax="10.0"))
		float RunModifier = 2.0f;
	
};
