// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CheckAttackRangeDecorator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTELDRITCH_API UCheckAttackRangeDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:

	UCheckAttackRangeDecorator();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


	//AOnryoSamuraiEnemy* Enemy = nullptr;
	
};
