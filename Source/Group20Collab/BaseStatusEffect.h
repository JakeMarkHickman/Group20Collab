// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseStatusEffect.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatusEffect_StatusEndedSignature, UBaseStatusEffect*, RefToSelf);

UCLASS(Blueprintable, BlueprintType)
class GROUP20COLLAB_API UBaseStatusEffect : public UObject
{
	GENERATED_BODY()
	
public:
	UBaseStatusEffect();

	UPROPERTY(BlueprintAssignable, Category = StatusEffect)
	FStatusEffect_StatusEndedSignature _OnStatusEffectEnded;

	UFUNCTION(BlueprintCallable, Category = StatusEffect)
	void ApplyStatusEffect(AActor* Afflicted);

	UFUNCTION(BlueprintCallable, Category = StatusEffect)
	void RemoveStatusEffect();

	void ResetTimers();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = StatusEffect)
	float _Duration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = StatusEffect)
	float _Period;

	UFUNCTION(BlueprintNativeEvent, Category = StatusEffect)
	void StartStatusEffect(AActor* Afflicted);

	UFUNCTION(BlueprintNativeEvent, Category = StatusEffect)
	void Periodic();

	UFUNCTION(BlueprintNativeEvent, Category = StatusEffect)
	void EndStatusEffect();

	void clearTimers();

	FTimerHandle PeriodicTimerHandle;
	FTimerHandle DurationTimerHandle;
};
