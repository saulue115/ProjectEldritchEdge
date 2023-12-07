// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy_GetRandomLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTELDRITCH_API UEnemy_GetRandomLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UEnemy_GetRandomLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float Radius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	FBlackboardKeySelector AimLocationKey;


	class AOnryoSamuraiEnemy* Enemy;
	
};
