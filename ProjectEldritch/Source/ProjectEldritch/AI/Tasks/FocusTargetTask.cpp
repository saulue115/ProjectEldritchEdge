// Fill out your copyright notice in the Description page of Project Settings.


#include "FocusTargetTask.h"
#include "AIController.h"
#include "../../Enemy/Players/OnryoSamuraiEnemy.h"
#include "../../Player/Characters/SamuraiPlayer.h"
#include "Kismet/GameplayStatics.h"

UFocusTargetTask::UFocusTargetTask()
{
	NodeName = "Focus On Target";
}

EBTNodeResult::Type UFocusTargetTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();

	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if(!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Enemy = Cast<AOnryoSamuraiEnemy>(Controller->GetPawn());

	const auto Player = Cast<ASamuraiPlayer>(UGameplayStatics::GetActorOfClass(this, ASamuraiPlayer::StaticClass()));

	if (!Enemy || !Player) return EBTNodeResult::Failed;

	Blackboard->SetValueAsObject(FocusTargetKey.SelectedKeyName,Player);


	Controller->SetFocus(Player);


	return EBTNodeResult::Succeeded;
}
