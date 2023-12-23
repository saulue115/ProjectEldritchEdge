// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ReadyToFightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UReadyToFightInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTELDRITCH_API IReadyToFightInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**A version of React To Trigger that can be implemented in C++ or Blueprint. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = TriggerReaction)
		bool ReactToTrigger();
};
