// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContextInterface.h"
#include "MoveInterface.h"
#include "LookInterface.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS(ABSTRACT)
class GROUP20COLLAB_API ABaseCharacter : public ACharacter, public IInputMappingContextInterface, public IMoveInterface, public ILookInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	
	virtual UInputMappingContext* GetMappingContext_Implementation() override;

protected:
	/* Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> _SpringArm;

	/* Follow camera */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> _FollowCamera;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = MappingContext)
	TObjectPtr<UInputMappingContext> _MappingContext;

public:	
	virtual void MoveAction_Implementation(FVector2D value) override;
	virtual void LookAction_Implementation(FVector2D value) override;
};
