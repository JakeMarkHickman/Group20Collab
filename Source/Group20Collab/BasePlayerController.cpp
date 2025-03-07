// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include <Kismet/KismetSystemLibrary.h>
#include "InputMappingContextInterface.h"
#include "MoveInterface.h"
#include "LookInterface.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ABasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputMappingContextInterface::StaticClass()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			subsystem->AddMappingContext(IInputMappingContextInterface::Execute_GetMappingContext(InPawn), 0);
		}
	}
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_MoveAction, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleMove);
		EIP->BindAction(_LookAction, ETriggerEvent::Triggered, this, &ABasePlayerController::HandleLook);
	}
}

void ABasePlayerController::HandleMove(const FInputActionValue& value)
{
	if (APawn* p = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(p, UMoveInterface::StaticClass()))
		{

			IMoveInterface::Execute_MoveAction(p, value.Get<FVector2D>());
		}
	}
}

void ABasePlayerController::HandleLook(const FInputActionValue& value)
{
	if (APawn* p = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(p, ULookInterface::StaticClass()))
		{

			ILookInterface::Execute_LookAction(p, value.Get<FVector2D>());
		}
	}
}
