// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_GetRandomLocationTask.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "../../Enemy/Players/OnryoSamuraiEnemy.h"

UEnemy_GetRandomLocationTask::UEnemy_GetRandomLocationTask()
{
	NodeName = "Get Random Location";
	
}

EBTNodeResult::Type UEnemy_GetRandomLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();

	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	Enemy = Cast<AOnryoSamuraiEnemy>(Controller->GetPawn());

	if (!Enemy) return EBTNodeResult::Failed;

	const auto NavSys = UNavigationSystemV1::GetCurrent(Enemy);

	if (!NavSys) return EBTNodeResult::Failed;

	FNavLocation NavLocation;

	auto Found = NavSys->GetRandomPointInNavigableRadius(Enemy->GetActorLocation(), Radius, NavLocation);


	if(!Found) return EBTNodeResult::Failed;


	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);


	return EBTNodeResult::Succeeded;
}
