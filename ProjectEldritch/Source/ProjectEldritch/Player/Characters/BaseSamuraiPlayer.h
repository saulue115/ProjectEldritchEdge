// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BaseSamuraiPlayer.generated.h"

UCLASS()
class PROJECTELDRITCH_API ABaseSamuraiPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseSamuraiPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		TObjectPtr<UCameraComponent> FollowCamera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		TObjectPtr<USpringArmComponent> BoomCamera = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
