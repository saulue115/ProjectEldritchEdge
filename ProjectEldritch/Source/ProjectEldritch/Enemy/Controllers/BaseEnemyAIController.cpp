// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAIController.h"
#include "../Players/OnryoSamuraiEnemy.h"

ABaseEnemyAIController::ABaseEnemyAIController()
{
}

void ABaseEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto Enemy = Cast<AOnryoSamuraiEnemy>(InPawn);

	if (!Enemy) return;
}
