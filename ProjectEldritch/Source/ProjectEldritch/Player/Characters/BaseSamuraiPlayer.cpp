// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSamuraiPlayer.h"

// Sets default values
ABaseSamuraiPlayer::ABaseSamuraiPlayer(const FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoomCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("Boom Camera"));
	BoomCamera->TargetArmLength = 600.0f;
	BoomCamera->bUsePawnControlRotation = true;
	BoomCamera->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camer"));
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->SetupAttachment(BoomCamera, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void ABaseSamuraiPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseSamuraiPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseSamuraiPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

