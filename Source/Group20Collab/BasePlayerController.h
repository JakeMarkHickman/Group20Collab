// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

struct FInputActionValue;
class UInputAction;

UCLASS(ABSTRACT)
class GROUP20COLLAB_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void OnPossess(APawn* InPawn) override;

protected:
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> _MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> _JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> _LookAction;

	void HandleMove(const FInputActionValue& value);
	void HandleLook(const FInputActionValue& value);
private:
};
