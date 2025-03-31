// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseStatusEffect.h"
#include "StatusEffectComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatusEffectComponent_EffectAdded, TSubclassOf<class UBaseStatusEffect>, effect);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROUP20COLLAB_API UStatusEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusEffectComponent();
	
	UPROPERTY(BlueprintAssignable, Category = StatusEffect)
	FStatusEffectComponent_EffectAdded _OnStatusEffectAdded;

	UFUNCTION(BlueprintCallable)
	void AddStatusEffect(TSubclassOf<class UBaseStatusEffect> Effect);

	UFUNCTION(BlueprintCallable)
	void RemoveStatusEffects();

	UFUNCTION(BlueprintPure, Category = StatusEffect)
	TArray<UBaseStatusEffect*> GetActiveStatusEffects() { return _ActiveStatusEffects; };

	UFUNCTION()
	void StatusEffectEnded(UBaseStatusEffect* StatusEffect);

private:
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UBaseStatusEffect>> _ActiveStatusEffects;

		
};
