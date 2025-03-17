// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStatusEffect.h"

UBaseStatusEffect::UBaseStatusEffect()
{
	_Duration = 0.0f;
	_Period = 0.0f;
}

void UBaseStatusEffect::ApplyStatusEffect(AActor* Afflicted)
{
	StartStatusEffect(Afflicted);
	ResetTimers();
}

void UBaseStatusEffect::RemoveStatusEffect()
{
	clearTimers();
	EndStatusEffect();
	_OnStatusEffectEnded.Broadcast(this);
}

void UBaseStatusEffect::ResetTimers()
{
	if (_Period > 0.0f)
	{
		GetOuter()->GetWorld()->GetTimerManager().SetTimer(PeriodicTimerHandle, this, &UBaseStatusEffect::Periodic, _Period, true, 0);
	}

	if (_Duration > 0.0f)
	{
		GetOuter()->GetWorld()->GetTimerManager().SetTimer(DurationTimerHandle, this, &UBaseStatusEffect::RemoveStatusEffect, _Duration + 0.01 /*To make sure that the periodic time can run*/, false); //End Status Effect
	}
}

void UBaseStatusEffect::StartStatusEffect_Implementation(AActor* Afflicted)
{
	
}

void UBaseStatusEffect::Periodic_Implementation()
{

}

void UBaseStatusEffect::EndStatusEffect_Implementation()
{

}

void UBaseStatusEffect::clearTimers()
{
	GetOuter()->GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}
