// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSamuraiPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include "Animation/AnimMontage.h"
#include "../Animations/EquipSwordAnimNotify.h"
#include "../Animations/DodgeAnimNotify.h"
#include "../Animations/AttackAnimNotify.h"
#include "SamuraiPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTELDRITCH_API ASamuraiPlayer : public ABaseSamuraiPlayer
{
	GENERATED_BODY()

public:

	ASamuraiPlayer(const FObjectInitializer& ObjectInitializer);

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	/** Input Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* EquipSwordAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* DefenseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* DodgeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		uint8 bWantsToRun : 1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		UAnimMontage* EquipSwordAnimMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		UAnimMontage* DodgeAnimMontage = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		TArray<TObjectPtr<UAnimMontage>> AttackAnimMontageArray;


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	uint8 bEquipSwordAnimInProgress : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		uint8 bDodgeAnimInProgress : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		uint8 bAttackAnimInProgress : 1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		uint8 bSwordEquipped : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		uint8 bDefenseMode : 1;

	float MovementSpeedInCombatMode = 350.0f;

protected:

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay();
	

public:


	UFUNCTION()
		void Move(const FInputActionValue& Value);

	

	UFUNCTION()
		void Look(const FInputActionValue& Value);


	UFUNCTION()
		void StartRunning();

	UFUNCTION()
		void EndRunning();
	
	UFUNCTION()
		bool IsRunning();

	UFUNCTION()
		void EquipSword();


	UFUNCTION()
		bool IsInDefense();

	UFUNCTION()
		void StartDefense();

	UFUNCTION()
		void EndDefense();


	UFUNCTION()
		void PlayDodgeMontage();


	UFUNCTION()
		void Attack();


	//Anim Notiofies
	UFUNCTION()
		void OnEquipSwordFinished(USkeletalMeshComponent* MeshComponent);

	UFUNCTION()
		void OnDodgeFinished(USkeletalMeshComponent* MeshComponent);


	UFUNCTION()
		void OnAttackFinished(USkeletalMeshComponent* MeshComponent);

	UFUNCTION()
		void InitAnimations();


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


};
