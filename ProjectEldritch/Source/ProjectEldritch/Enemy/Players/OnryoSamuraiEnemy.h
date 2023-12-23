// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "../Controllers/BaseEnemyAIController.h"
#include "../../Player/Animations/EquipSwordAnimNotify.h"
#include "../../Player/Animations/DodgeAnimNotify.h"
#include "../../Player/Animations/AttackAnimNotify.h"
#include "Animation/AnimMontage.h"
#include "../../Utils/ReadyToFightInterface.h"
#include "OnryoSamuraiEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTELDRITCH_API AOnryoSamuraiEnemy : public ABaseEnemy,public IReadyToFightInterface
{
	GENERATED_BODY()

public:

	AOnryoSamuraiEnemy();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aniamtion)
	TObjectPtr<UAnimMontage> EquipSwordAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aniamtion)
		TArray<TObjectPtr<UAnimMontage>> AttackAnimMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	uint8 bEquipSwordAnimInProgress : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	uint8 bAttackAnimInProgress : 1;


	//Attack Atts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		float AttackRange = 200.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		uint8 bEnemyCanAttack : 1;


	// Implementa la función ReadyToFight de la interfaz
	bool ReactToTrigger_Implementation() override;


	UFUNCTION()
		void OnEquipSwordFinished(USkeletalMeshComponent* MeshComponent);

	UFUNCTION()
		void OnAttackFinished(USkeletalMeshComponent* MeshComponent);

	UFUNCTION()
		void InitAnimations();


	//Attack Functions
	UFUNCTION()
		void Attack();

	UFUNCTION()
		void ResetAttack();


	//anim notify template
	template<typename T>
	TArray<T*> FindNotifiesByClass(UAnimSequenceBase* Animation)
	{
		TArray<T*> FoundNotifies;

		if (!Animation) return FoundNotifies;

		const auto NotifyEvents = Animation->Notifies;

		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);

			if (AnimNotify) FoundNotifies.Add(AnimNotify);
		}

		return FoundNotifies;
	}

	template<typename T>
	T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		//TArray<T*> FoundNotifies;

		if (!Animation) return nullptr;

		const auto NotifyEvents = Animation->Notifies;

		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);

			if (AnimNotify) return AnimNotify;
		}

		return nullptr;
	}

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
