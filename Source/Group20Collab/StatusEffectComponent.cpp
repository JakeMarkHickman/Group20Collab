// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectComponent.h"

// Sets default values for this component's properties
UStatusEffectComponent::UStatusEffectComponent()
{
	
}

void UStatusEffectComponent::AddStatusEffect(TSubclassOf<class UBaseStatusEffect> Effect)
{
	if (int index = _ActiveStatusEffects.ContainsByPredicate([&](UBaseStatusEffect* Status) {return Status->GetClass() == Effect; }))
	{
		UE_LOG(LogTemp, Display, TEXT("Reset Timer"));
		_ActiveStatusEffects[index - 1]->ResetTimers();
		return;
	}

	UBaseStatusEffect* EffectToAdd = NewObject<UBaseStatusEffect>(this, Effect);

	_ActiveStatusEffects.Add(EffectToAdd);
	EffectToAdd->ApplyStatusEffect(GetOwner());
	EffectToAdd->_OnStatusEffectEnded.AddDynamic(this, &UStatusEffectComponent::StatusEffectEnded);
}

void UStatusEffectComponent::RemoveStatusEffects()
{
	for (int i = _ActiveStatusEffects.Num() - 1; i >= 0; i--)
	{
		if (_ActiveStatusEffects[i] != nullptr)
		{
			_ActiveStatusEffects[i]->RemoveStatusEffect();
		}
	}
}

void UStatusEffectComponent::StatusEffectEnded(UBaseStatusEffect* StatusEffect)
{
	StatusEffect->_OnStatusEffectEnded.RemoveDynamic(this, &UStatusEffectComponent::StatusEffectEnded);
	_ActiveStatusEffects.Remove(StatusEffect);
}

