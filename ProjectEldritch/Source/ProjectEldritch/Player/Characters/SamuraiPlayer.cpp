// Fill out your copyright notice in the Description page of Project Settings.


#include "SamuraiPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Components/SamuraiMovementComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"
#include "Components/InputComponent.h"


ASamuraiPlayer::ASamuraiPlayer(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer.SetDefaultSubobjectClass<USamuraiMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
}



void ASamuraiPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	InitAnimations();
}

void ASamuraiPlayer::Tick(float DeltaTime)
{
	if (bIsLock)
	{
		// Obtener el enemigo más cercano del diccionario
		AOnryoSamuraiEnemy* NearestEnemy = nullptr;
		float NearestDistance = MAX_FLT;

		for (const auto& Pair : EnemyDictionary)
		{
			AOnryoSamuraiEnemy* Enemy = Pair.Value;

			// Calcular la distancia al enemigo
			float DistanceToEnemy = FVector::Distance(GetActorLocation(), Enemy->GetActorLocation());

			// Actualizar el enemigo más cercano si es más cercano que el actual
			if (DistanceToEnemy < NearestDistance)
			{
				NearestEnemy = Enemy;
				NearestDistance = DistanceToEnemy;
			}
		}

		if (NearestEnemy)
		{
			// Calcular la dirección hacia el enemigo más cercano
			FVector DirectionToEnemy = NearestEnemy->GetActorLocation() - GetActorLocation();
			DirectionToEnemy.Normalize();

			// Calcular la rotación basada en la dirección hacia el enemigo más cercano
			FRotator NewRotation = DirectionToEnemy.Rotation();

			// Establecer la rotación del jugador
			SetActorRotation(NewRotation);

			// Aquí puedes agregar lógica adicional, como mover al jugador hacia el enemigo, etc.
			// ...
		}
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("LOCK ACTIVADOOOOOO"));
	}
}

void ASamuraiPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASamuraiPlayer::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASamuraiPlayer::Look);

		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ASamuraiPlayer::StartRunning);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::None, this, &ASamuraiPlayer::EndRunning);

		EnhancedInputComponent->BindAction(EquipSwordAction, ETriggerEvent::Triggered, this, &ASamuraiPlayer::EquipSword);

		EnhancedInputComponent->BindAction(DefenseAction, ETriggerEvent::Triggered, this, &ASamuraiPlayer::StartDefense);
		EnhancedInputComponent->BindAction(DefenseAction, ETriggerEvent::None, this, &ASamuraiPlayer::EndDefense);

		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ASamuraiPlayer::PlayDodgeMontage);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASamuraiPlayer::Attack);

		EnhancedInputComponent->BindAction(LockAction, ETriggerEvent::Completed , this, &ASamuraiPlayer::ToggleLock);
		//EnhancedInputComponent->BindAction(LockAction, ETriggerEvent::Canceled, this, &ASamuraiPlayer::UnLock);
	}
}

void ASamuraiPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}


void ASamuraiPlayer::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASamuraiPlayer::StartRunning()
{
	bWantsToRun = true;
}

void ASamuraiPlayer::EndRunning()
{
	bWantsToRun = false;
}

bool ASamuraiPlayer::IsRunning()
{
	return bWantsToRun && !GetVelocity().IsZero();
}

void ASamuraiPlayer::EquipSword()
{

	auto OwnMovementComponent = Cast<USamuraiMovementComponent>(GetCharacterMovement());

	if (!EquipSwordAnimMontage || !OwnMovementComponent) return;

	if (!bEquipSwordAnimInProgress)
	{
		PlayAnimMontage(EquipSwordAnimMontage);

		bEquipSwordAnimInProgress = true;

		bSwordEquipped = true;

		if (ReactToTrigger_Implementation())
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("INTERFACEEE LLAMADO"));
		}

		//ReadyToFight();

		//Execute_ReadyToFight(this);

		GetCharacterMovement()->MaxWalkSpeed = MovementSpeedInCombatMode;

		OwnMovementComponent->RunModifier = 2.5f;

		
	}
	

	
}



void ASamuraiPlayer::InitAnimations()
{


	if (!EquipSwordAnimMontage || !DodgeAnimMontage || AttackAnimMontageArray.Num() == 0) return;

	auto EquipSwordAnimation = FindNotifyByClass<UEquipSwordAnimNotify>(EquipSwordAnimMontage);

	auto DodgeAnimation = FindNotifyByClass<UDodgeAnimNotify>(DodgeAnimMontage);

	//auto AttackAnimations = FindNotifiesByClass<UAttackAnimNotify>(AttackAnimMontageArray[0]);

	if (EquipSwordAnimation)
	{
		EquipSwordAnimation->OnNotified.AddUObject(this, &ASamuraiPlayer::OnEquipSwordFinished);
	}

	if (DodgeAnimation)
	{
		DodgeAnimation->OnNotified.AddUObject(this, &ASamuraiPlayer::OnDodgeFinished);
	}

	/*if (AttackAnimations)
	{
		AttackAnimations->OnNotified.AddUObject(this, &ASamuraiPlayer::OnAttackFinished);
	}*/

	// Para AttackAnimMontageArray
	for (auto AttackAnimMontage : AttackAnimMontageArray)
	{
		auto AttackNotifies = FindNotifiesByClass<UAttackAnimNotify>(AttackAnimMontage);

		for (auto AttackNotify : AttackNotifies)
		{
			AttackNotify->OnNotified.AddUObject(this, &ASamuraiPlayer::OnAttackFinished);
		}
	}
}

bool ASamuraiPlayer::ReactToTrigger_Implementation()
{
	return true;
}




void ASamuraiPlayer::OnEquipSwordFinished(USkeletalMeshComponent* MeshComponent)
{
	if (GetMesh() != MeshComponent) return;

	bEquipSwordAnimInProgress = false;

	bDefenseMode = false;

	bIsInCombat = true;
	
}

void ASamuraiPlayer::OnDodgeFinished(USkeletalMeshComponent* MeshComponent)
{
	if (GetMesh() != MeshComponent) return;

	bDodgeAnimInProgress = false;
}


void ASamuraiPlayer::OnAttackFinished(USkeletalMeshComponent* MeshComponent)
{
	if (GetMesh() != MeshComponent) return;

	bAttackAnimInProgress = false;
}


bool ASamuraiPlayer::IsInDefense()
{
	
	return bDefenseMode && bSwordEquipped && bIsInCombat;
}

void ASamuraiPlayer::StartDefense()
{
	if (bIsInCombat)
	{
		bWantsToRun = false;

		bDefenseMode = true;
	}

	

}

void ASamuraiPlayer::EndDefense()
{
	bDefenseMode = false;
}

void ASamuraiPlayer::PlayDodgeMontage()
{
	if (!DodgeAnimMontage) return;


	if (!bDodgeAnimInProgress && !GetVelocity().IsZero() && bIsInCombat)
	{
		PlayAnimMontage(DodgeAnimMontage, 1.2f);

		bDodgeAnimInProgress = true;
	}
	
}

void ASamuraiPlayer::Attack()
{
	if (!bIsInCombat || !bSwordEquipped || bEquipSwordAnimInProgress || bDodgeAnimInProgress || AttackAnimMontageArray.Num() == 0) return;


	int32 CurrentAttackInt = 0;

	int32 NumAttackMontages = AttackAnimMontageArray.Num();

	int32 AttackInt = FMath::RandRange(0, NumAttackMontages - 1);

	if (!bAttackAnimInProgress)
	{
		
	
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
		//
		//while (AttackInt == CurrentAttackInt)
		//{
		//	AttackInt = FMath::RandRange(0, NumAttackMontages - 1);
		//}

		//CurrentAttackInt = AttackInt;

		//if (!bAttackAnimInProgress)
		//{
		//	// Reproducir la animación
		//	PlayAnimMontage(AttackAnimMontageArray[CurrentAttackInt]);

		//	bAttackAnimInProgress = true;
		//}

		
	}
	


}

void ASamuraiPlayer::ToggleLock()
{
	bIsLock = !bIsLock;  // Alterna entre true y false

	if (bIsLock)
	{
		Lock();  // Llamada a la función Lock si se activa el bloqueo
	}
	else
	{
		UnLock();  // Llamada a la función Unlock si se desactiva el bloqueo
	}
}

void ASamuraiPlayer::Lock()
{
	//if (!bIsLock) return;

	bIsLock = true;

	TArray<AActor*> FoundEnemies;


	UGameplayStatics::GetAllActorsOfClass(this,AOnryoSamuraiEnemy::StaticClass(),FoundEnemies);

	EnemyDictionary.Empty();

	// Llenar el diccionario usando un identificador único
	for (AActor* Actor : FoundEnemies)
	{
		AOnryoSamuraiEnemy* Enemy = Cast<AOnryoSamuraiEnemy>(Actor);
		if (Enemy)
		{
			//FString EnemyIdentifier = Enemy->GetUniqueIdentifier();  // Debes implementar una función GetUniqueIdentifier en tu clase
			float DistanceToEnemy = FVector::Distance(GetActorLocation(), Enemy->GetActorLocation());
			EnemyDictionary.Add(DistanceToEnemy, Enemy);
			
		}

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("LOCK ON ENEMYYYYYY"));
		

		
		
	}


	
}


void ASamuraiPlayer::IsLock()
{
	bIsLock = true;
}

void ASamuraiPlayer::UnLock()
{
	bIsLock = false;
}
