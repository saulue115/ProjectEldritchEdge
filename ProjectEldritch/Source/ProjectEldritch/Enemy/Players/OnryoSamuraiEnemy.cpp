// Fill out your copyright notice in the Description page of Project Settings.


#include "OnryoSamuraiEnemy.h"
#include "AIController.h"

AOnryoSamuraiEnemy::AOnryoSamuraiEnemy()
{
	AIControllerClass = ABaseEnemyAIController::StaticClass();
}
