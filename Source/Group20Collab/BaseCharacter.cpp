// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	_SpringArm->SetupAttachment(GetRootComponent());
	_SpringArm->TargetArmLength = 450.0f;
	_SpringArm->bUsePawnControlRotation = true;
	_SpringArm->SetRelativeLocation(FVector(0, 0, 50));

	_FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	_FollowCamera->SetupAttachment(_SpringArm, USpringArmComponent::SocketName);
	_FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

UInputMappingContext* ABaseCharacter::GetMappingContext_Implementation()
{
	return _MappingContext;
}

void ABaseCharacter::MoveAction_Implementation(FVector2D value)
{
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
		AddMovementInput(ForwardDirection, value.Y);
		AddMovementInput(RightDirection, value.X);
	}
}

void ABaseCharacter::LookAction_Implementation(FVector2D value)
{
	if (Controller != nullptr)
	{
		value.Y = -value.Y;
		// add yaw and pitch input to controller
		AddControllerYawInput(value.X);
		AddControllerPitchInput(value.Y);
	}
}

