// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "OnryoEnemy_Attack_Task.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTELDRITCH_API UOnryoEnemy_Attack_Task : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UOnryoEnemy_Attack_Task();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
