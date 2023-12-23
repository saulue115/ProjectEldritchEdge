// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckAttackRangeDecorator.h"
#include "../../Enemy/Players/OnryoSamuraiEnemy.h"
#include "../../Player/Characters/SamuraiPlayer.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

UCheckAttackRangeDecorator::UCheckAttackRangeDecorator()
{
	NodeName = "Check Enemy Attack Distance Decorator";
}

bool UCheckAttackRangeDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();

	if (!Controller) return false;

	auto Player = Cast<ASamuraiPlayer>(UGameplayStatics::GetActorOfClass(this, ASamuraiPlayer::StaticClass()));

	auto Enemy = Cast<AOnryoSamuraiEnemy>(Controller->GetPawn());


	if (!Enemy || !Player) return false;


	float CheckDistanceBetweenEnemyAndPlayer = FVector::Distance(Enemy->GetActorLocation(), Player->GetActorLocation());


	return CheckDistanceBetweenEnemyAndPlayer <= Enemy->AttackRange ? true : false;
}
