// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values for this component's properties
UHealthComponent::UHealthComponent(): _MaxHealth(100.f), _IsDead(false)
{
	
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	_CurrentHealth = _MaxHealth;
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* causer)
{
	if (_IsDead)
	{
		return;
	}

	float preHealth = _CurrentHealth;
	SetCurrentHealth(_CurrentHealth - damage, instigator);
	_OnHealthChanged.Broadcast(_CurrentHealth, damage, instigator);
}

void UHealthComponent::SetCurrentHealth(float value, AController* Instigator)
{
	if (_IsDead)
	{
		return;
	}

	float updatedValue = UKismetMathLibrary::FClamp(value, 0.0f, _MaxHealth);

	_CurrentHealth = updatedValue;

	if(_CurrentHealth <= 0)
	{
		_IsDead = true;
		_OnDeath.Broadcast(Instigator);
	}
}

void UHealthComponent::SetMaxHealth(float value, AController* Instigator)
{
	if (_IsDead)
	{
		return;
	}

	float HealthPercent = _CurrentHealth / _MaxHealth;
	_OnMaxHealthChanged.Broadcast(value, _MaxHealth - value, Instigator);
	
	_MaxHealth = value;

	SetCurrentHealth(HealthPercent * _MaxHealth, Instigator);
}

