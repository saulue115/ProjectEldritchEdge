// Fill out your copyright notice in the Description page of Project Settings.


#include "OnryoEnemy_Attack_Task.h"
#include "../../Enemy/Players/OnryoSamuraiEnemy.h"
#include "AIController.h"

UOnryoEnemy_Attack_Task::UOnryoEnemy_Attack_Task()
{
	NodeName = "Onryo Enemy Attack Task";
}

EBTNodeResult::Type UOnryoEnemy_Attack_Task::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();

	if (!Controller) return EBTNodeResult::Failed;

	auto Enemy = Cast<AOnryoSamuraiEnemy>(Controller->GetPawn());

	if (!Enemy) return EBTNodeResult::Failed;

	Enemy->Attack();


	return EBTNodeResult::Type();
}
