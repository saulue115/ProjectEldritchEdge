// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FocusTargetTask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTELDRITCH_API UFocusTargetTask : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UFocusTargetTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FBlackboardKeySelector FocusTargetKey;
	
};
