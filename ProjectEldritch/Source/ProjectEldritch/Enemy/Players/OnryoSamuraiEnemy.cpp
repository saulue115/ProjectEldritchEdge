// Fill out your copyright notice in the Description page of Project Settings.


#include "OnryoSamuraiEnemy.h"
#include "AIController.h"
#include "Engine/Engine.h"

AOnryoSamuraiEnemy::AOnryoSamuraiEnemy()
{
	AIControllerClass = ABaseEnemyAIController::StaticClass();
}

void AOnryoSamuraiEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAnimations();

	//PlayAnimMontage(EquipSwordAnimMontage);

	//bSwordEquipped = true;
	if (!bEquipSwordAnimInProgress)
	{
		PlayAnimMontage(EquipSwordAnimMontage);

		bEquipSwordAnimInProgress = true;

		bSwordEquipped = true;
	}

	
	
}

void AOnryoSamuraiEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	/*if (bSwordEquipped)
	{
		PlayAnimMontage(EquipSwordAnimMontage);
	}*/
	/*if (ReactToTrigger())
	{
		bSwordEquipped = true;
	}*/

	

	//PlayAnimMontage(EquipSwordAnimMontage);

	//Attack();
}





bool AOnryoSamuraiEnemy::ReactToTrigger_Implementation()
{
	return true;
}

void AOnryoSamuraiEnemy::OnEquipSwordFinished(USkeletalMeshComponent* MeshComponent)
{
	if (GetMesh() != MeshComponent) return;

	bEquipSwordAnimInProgress = false;

	bDefenseMode = false;

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, TEXT("EQUIP SWORD ON ENEMYYYYYYY"));
}


void AOnryoSamuraiEnemy::InitAnimations()
{
	if (!EquipSwordAnimMontage || AttackAnimMontageArray.Num() == 0) return;

	auto EquipSwordAnimation = FindNotifyByClass<UEquipSwordAnimNotify>(EquipSwordAnimMontage);

	//auto AttackAnimation = FindNotifyByClass<UAttackAnimNotify>(AttackAnimMontage);

	if (EquipSwordAnimation)
	{
		//bSwordEquipped = true;
		EquipSwordAnimation->OnNotified.AddUObject(this, &AOnryoSamuraiEnemy::OnEquipSwordFinished);
	}


	/*if (AttackAnimation)
	{
		AttackAnimation->OnNotified.AddUObject(this, &AOnryoSamuraiEnemy::OnAttackFinished);
	}*/

	for (auto AttackAnimMontage : AttackAnimMontageArray)
	{
		auto AttackNotifies = FindNotifiesByClass<UAttackAnimNotify>(AttackAnimMontage);

		for (auto AttackNotify : AttackNotifies)
		{
			AttackNotify->OnNotified.AddUObject(this, &AOnryoSamuraiEnemy::OnAttackFinished);
		}
	}
}

void AOnryoSamuraiEnemy::Attack()
{
	if (AttackAnimMontageArray.Num() == 0) return;

	int32 CurrentAttackInt = 0;

	int32 NumAttackMontages = AttackAnimMontageArray.Num();

	int32 AttackInt = FMath::RandRange(0, NumAttackMontages - 1);

	if (bEnemyCanAttack && !bAttackAnimInProgress)
	{
		//bEnemyCanAttack = true;

		//bAttackAnimInProgress = true;

		//PlayAnimMontage(AttackAnimMontage);

		if (AttackInt == CurrentAttackInt)
		{
			// Incrementar o decrementar el índice de ataque para evitar la repetición
			if (AttackInt == 0)
			{
				AttackInt++;
			}
			else
			{
				AttackInt--;
			}

			CurrentAttackInt = AttackInt;

			// Reproducir la animación
			PlayAnimMontage(AttackAnimMontageArray[CurrentAttackInt]);

			bAttackAnimInProgress = true;
		}
		else {
			CurrentAttackInt = AttackInt;


			// Reproducir la animación
			PlayAnimMontage(AttackAnimMontageArray[CurrentAttackInt]);

			bAttackAnimInProgress = true;
		}
	}
}

void AOnryoSamuraiEnemy::ResetAttack()
{
	bEnemyCanAttack = false;
}


void AOnryoSamuraiEnemy::OnAttackFinished(USkeletalMeshComponent* MeshComponent)
{
	if (GetMesh() != MeshComponent) return;

	bAttackAnimInProgress = false;
}

