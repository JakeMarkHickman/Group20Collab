// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputMappingContextInterface.generated.h"

class UInputMappingContext;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInputMappingContextInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GROUP20COLLAB_API IInputMappingContextInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	UInputMappingContext* GetMappingContext();
};
